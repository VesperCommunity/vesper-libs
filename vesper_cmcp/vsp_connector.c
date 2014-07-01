/**
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_cmcp.h"

#if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
  /* define "inline" keyword for pre-C99 C standard */
  #define inline
#endif
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <stdlib.h>
#include <vesper_error/vsp_error.h>

/** vsp_cmcp_connector finite state machine flag. */
typedef enum {
    /** Sockets are not initialized and not connected. */
    VSP_CMCP_UNINITIALIZED,
    /** Sockets are initialized and connected. */
    VSP_CMCP_INITIALIZED
} vsp_cmcp_state;

/** State and other data used for network connection. */
struct vsp_cmcp_connector {
    /** Finite state machine flag. */
    vsp_cmcp_state state;
    /** nanomsg socket number to publish messages. */
    int publish_socket;
    /** nanomsg socket number to receive messages. */
    int subscribe_socket;
    /** Flag for reception thread (1 if running, 0 otherwise). */
    int receiving;
};

vsp_cmcp_connector* vsp_cmcp_connector_create(void)
{
    vsp_cmcp_connector *net_conn;
    /* allocate memory */
    VSP_ALLOC(net_conn, vsp_cmcp_connector, return NULL);
    /* initialize struct data */
    net_conn->state = VSP_CMCP_UNINITIALIZED;
    net_conn->publish_socket = -1;
    net_conn->subscribe_socket = -1;
    /* return struct pointer */
    return net_conn;
}

int vsp_cmcp_connect(vsp_cmcp_connector *net_conn,
    const char *publish_address, const char *subscribe_address)
{
    int ret;

    if (net_conn == NULL || publish_address == NULL
        || subscribe_address == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    if (net_conn->state != VSP_CMCP_UNINITIALIZED) {
        /* sockets already initialized */
        vsp_error_set_num(EALREADY);
        return -1;
    }
    /* initialize sockets */
    net_conn->publish_socket = nn_socket(AF_SP, NN_PUB);
    net_conn->subscribe_socket = nn_socket(AF_SP, NN_SUB);
    /* connect sockets */
    ret = nn_connect(net_conn->publish_socket, publish_address);
    if (ret < 0) {
        /* errno set by nanomsg */
        return -1;
    }
    ret = nn_connect(net_conn->subscribe_socket, subscribe_address);
    if (ret < 0) {
        /* errno set by nanomsg */
        return -1;
    }
    /* set state */
    net_conn->state = VSP_CMCP_INITIALIZED;
    /* sockets successfully connected */
    return 0;
}

int vsp_cmcp_disconnect(vsp_cmcp_connector *net_conn)
{
    int ret;

    if (net_conn == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    if (net_conn->state == VSP_CMCP_UNINITIALIZED) {
        /* sockets not connected */
        vsp_error_set_num(ENOTCONN);
        return -1;
    }

    /* disconnect sockets */
    ret = nn_close(net_conn->publish_socket);
    if (ret < 0) {
        /* errno set by nanomsg */
        return -1;
    }
    ret = nn_close(net_conn->subscribe_socket);
    if (ret < 0) {
        /* errno set by nanomsg */
        return -1;
    }
    /* deinitialize sockets */
    net_conn->publish_socket = -1;
    net_conn->subscribe_socket = -1;
    /* set state */
    net_conn->state = VSP_CMCP_UNINITIALIZED;
    /* sockets successfully disconnected */
    return 0;
}

int vsp_cmcp_reception_thread_run(vsp_cmcp_connector *net_conn)
{
    if (net_conn == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }

    net_conn->receiving = 1;
    /* reception loop */
    while (net_conn->receiving) {

    }
    /* success */
    return 0;
}

int vsp_cmcp_reception_thread_stop(vsp_cmcp_connector *net_conn)
{
    if (net_conn == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    /* stop reception */
    net_conn->receiving = 0;
    /* success */
    return 0;
}

int vsp_cmcp_connector_free(vsp_cmcp_connector *net_conn)
{
    int ret;
    int success;

    success = 0;

    if (net_conn == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    if (net_conn->state != VSP_CMCP_UNINITIALIZED) {
        /* close publish socket */
        ret = nn_close(net_conn->publish_socket);
        if (ret != 0) {
            /* errno set by nanomsg */
            success = -1;
        }
        /* close subscribe socket */
        ret = nn_close(net_conn->subscribe_socket);
        if (ret != 0) {
            /* errno set by nanomsg */
            success = -1;
        }
    }
    /* free memory */
    VSP_FREE(net_conn);
    return success;
}
