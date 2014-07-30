/**
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_cmcp_server.h"

#include <vesper_util/vsp_error.h>
#include <vesper_util/vsp_util.h>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <pthread.h>
#include <stdlib.h>

/** vsp_cmcp_server finite state machine flag. */
typedef enum {
    /** Sockets are not initialized and not bound. */
    VSP_CMCP_SERVER_UNINITIALIZED,
    /** Sockets are initialized and bound. */
    VSP_CMCP_SERVER_INITIALIZED,
    /** Message reception thread was started. */
    VSP_CMCP_SERVER_STARTING,
    /** Message reception thread is running. */
    VSP_CMCP_SERVER_RUNNING,
    /** Message reception thread was stopped. */
    VSP_CMCP_SERVER_STOPPING
} vsp_cmcp_server_state;

/** State and other data used for network connection. */
struct vsp_cmcp_server {
    /** Finite state machine flag. */
    vsp_cmcp_server_state state;
    /** nanomsg socket number to publish messages. */
    int publish_socket;
    /** nanomsg socket number to receive messages. */
    int subscribe_socket;
    /** Reception thread. */
    pthread_t thread;
};

/** Event loop for message reception running in its own thread. */
static void *_vsp_cmcp_server_run(void *param);

vsp_cmcp_server* vsp_cmcp_server_create(void)
{
    vsp_cmcp_server *cmcp_server;
    /* allocate memory */
    VSP_ALLOC(cmcp_server, vsp_cmcp_server, return NULL);
    /* initialize struct data */
    cmcp_server->state = VSP_CMCP_SERVER_UNINITIALIZED;
    cmcp_server->publish_socket = -1;
    cmcp_server->subscribe_socket = -1;
    /* return struct pointer */
    return cmcp_server;
}

int vsp_cmcp_server_free(vsp_cmcp_server *cmcp_server)
{
    int ret;
    int success;

    success = 0;

    /* check parameter */
    VSP_ASSERT(cmcp_server != NULL, vsp_error_set_num(EINVAL); return -1);

    if (cmcp_server->state != VSP_CMCP_SERVER_UNINITIALIZED) {
        /* close publish socket */
        ret = nn_close(cmcp_server->publish_socket);
        /* check error set by nanomsg */
        VSP_ASSERT(ret == 0, success = -1);

        /* close subscribe socket */
        ret = nn_close(cmcp_server->subscribe_socket);
        /* check error set by nanomsg */
        VSP_ASSERT(ret == 0, success = -1);
    }
    /* free memory */
    VSP_FREE(cmcp_server);
    return success;
}

int vsp_cmcp_server_bind(vsp_cmcp_server *cmcp_server,
    const char *publish_address, const char *subscribe_address)
{
    int ret;

    /* check parameters */
    VSP_ASSERT(cmcp_server != NULL && publish_address != NULL
        && subscribe_address != NULL, vsp_error_set_num(EINVAL); return -1);
    /* check sockets not yet initialized */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_UNINITIALIZED,
        vsp_error_set_num(EALREADY); return -1);

    /* initialize sockets */
    cmcp_server->publish_socket = nn_socket(AF_SP, NN_PUB);
    cmcp_server->subscribe_socket = nn_socket(AF_SP, NN_SUB);

    /* bind sockets */
    ret = nn_bind(cmcp_server->publish_socket, publish_address);
    /* check error set by nanomsg */
    VSP_ASSERT(ret >= 0, return -1);

    ret = nn_bind(cmcp_server->subscribe_socket, subscribe_address);
    /* check error set by nanomsg */
    VSP_ASSERT(ret >= 0, return -1);

    /* set state */
    cmcp_server->state = VSP_CMCP_SERVER_INITIALIZED;
    /* sockets successfully bound */
    return 0;
}

int vsp_cmcp_server_unbind(vsp_cmcp_server *cmcp_server)
{
    int ret;

    /* check parameter */
    VSP_ASSERT(cmcp_server != NULL, vsp_error_set_num(EINVAL); return -1);

    /* check sockets already initialized */
    VSP_ASSERT(cmcp_server->state != VSP_CMCP_SERVER_UNINITIALIZED,
        vsp_error_set_num(ENOTCONN); return -1);

    /* unbind sockets */
    ret = nn_close(cmcp_server->publish_socket);
    /* check error set by nanomsg */
    VSP_ASSERT(ret == 0, return -1);

    ret = nn_close(cmcp_server->subscribe_socket);
    /* check error set by nanomsg */
    VSP_ASSERT(ret == 0, return -1);

    /* deinitialize sockets */
    cmcp_server->publish_socket = -1;
    cmcp_server->subscribe_socket = -1;

    /* set state */
    cmcp_server->state = VSP_CMCP_SERVER_UNINITIALIZED;
    /* sockets successfully unbound */
    return 0;
}

int vsp_cmcp_server_start(vsp_cmcp_server *cmcp_server)
{
    int ret;

    /* check parameter */
    VSP_ASSERT(cmcp_server != NULL, vsp_error_set_num(EINVAL); return -1);

    /* check sockets are initialized and thread is not running */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_INITIALIZED,
        vsp_error_set_num(EINVAL); return -1);

    /* mark thread as starting */
    cmcp_server->state = VSP_CMCP_SERVER_STARTING;

    /* start reception thread */
    ret = pthread_create(&cmcp_server->thread, NULL, _vsp_cmcp_server_run,
        (void*) cmcp_server);

    /* check for pthread errors */
    VSP_ASSERT(ret == 0, vsp_error_set_num(ret); return -1);

    /* success */
    return 0;
}

int vsp_cmcp_server_stop(vsp_cmcp_server *cmcp_server)
{
    int ret;

    /* check parameter */
    VSP_ASSERT(cmcp_server != NULL, vsp_error_set_num(EINVAL); return -1);

    /* wait until thread has started */
    while (cmcp_server->state == VSP_CMCP_SERVER_STARTING) {
        /* do nothing */
    }

    /* check thread is running */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_RUNNING,
        vsp_error_set_num(EINVAL); return -1);

    /* stop reception thread */
    cmcp_server->state = VSP_CMCP_SERVER_STOPPING;

    /* wait for thread to join */
    ret = pthread_join(cmcp_server->thread, NULL);

    /* check thread has successfully stopped */
    VSP_ASSERT(ret == 0, vsp_error_set_num(EINTR); return -1);

    /* check state */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_INITIALIZED,
        vsp_error_set_num(EINTR); return -1);

    /* success */
    return 0;
}

void *_vsp_cmcp_server_run(void *param)
{
    vsp_cmcp_server *cmcp_server;

    /* check parameter */
    VSP_ASSERT(param != NULL, vsp_error_set_num(EINVAL); return (void*) -1);

    cmcp_server = (vsp_cmcp_server*) param;

    /* check sockets are initialized and thread was started */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_STARTING,
        vsp_error_set_num(EINVAL); return (void*) -1);

    /* mark thread as running */
    cmcp_server->state = VSP_CMCP_SERVER_RUNNING;

    /* reception loop */
    while (cmcp_server->state == VSP_CMCP_SERVER_RUNNING) {

    }

    /* check thread was requested to stop */
    VSP_ASSERT(cmcp_server->state == VSP_CMCP_SERVER_STOPPING,
        vsp_error_set_num(EINTR); return (void*) -1);

    /* signal that thread has stopped */
    cmcp_server->state = VSP_CMCP_SERVER_INITIALIZED;

    /* success */
    return (void*) 0;
}
