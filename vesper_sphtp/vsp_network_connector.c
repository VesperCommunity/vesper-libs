/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_sphtp.h"

#if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
  /* define "inline" keyword for pre-C99 C standard */
  #define inline
#endif
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <stdlib.h>
#include <vesper_error/vsp_error.h>

/** vsp_network_connector state machine flag. */
typedef enum {
    /** sockets are not initialized and not connected */
    VSP_SOCK_UNINITIALIZED,
    /** sockets are initialized and connected */
    VSP_SOCK_INITIALIZED
} vsp_connector_state;

/** State and other data used for network connection. */
struct vsp_network_connector {
    vsp_connector_state state;
    int publish_socket;
    int subscribe_socket;
};

vsp_network_connector_ptr vsp_network_connector_new(void)
{
    vsp_network_connector_ptr net_conn;
    /* allocate memory */
    net_conn = malloc(sizeof(struct vsp_network_connector));
    if (net_conn == NULL) {
        /* allocation failed */
        vsp_error_set_num(ENOMEM);
        return NULL;
    }
    /* initialize struct data */
    net_conn->state = VSP_SOCK_UNINITIALIZED;
    net_conn->publish_socket = 0;
    net_conn->subscribe_socket = 0;
    /* return struct pointer */
    return net_conn;
}

int vsp_establish_connection(vsp_network_connector_ptr net_conn,
    const char *publish_address, const char *subscribe_address)
{
    int ret;

    if (net_conn == NULL || publish_address == NULL
        || subscribe_address == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    if(net_conn->state != VSP_SOCK_UNINITIALIZED) {
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
    net_conn->state = VSP_SOCK_INITIALIZED;
    /* sockets successfully connected */
    return 0;
}

int vsp_network_connector_close(vsp_network_connector_ptr net_conn)
{
    int ret;
    int success;

    success = 0;

    if (net_conn == NULL) {
        /* invalid parameter */
        vsp_error_set_num(EINVAL);
        return -1;
    }
    if (net_conn->state != VSP_SOCK_UNINITIALIZED) {
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
    free(net_conn);
    return success;
}
