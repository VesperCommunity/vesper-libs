/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_network_connector.h"

#if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
  /* define "inline" keyword for pre-C99 C standard */
  #define inline
#endif
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <stdlib.h>

/** vsp_network_connector state machine flag. */
typedef enum {
    UNINITIALIZED
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
        return NULL;
    }
    /* initialize struct data */
    net_conn->state = UNINITIALIZED;
    net_conn->publish_socket = 0;
    net_conn->subscribe_socket = 0;
    /* return struct pointer */
    return net_conn;
}

int vsp_network_connector_close(vsp_network_connector_ptr net_conn)
{
    if (net_conn == NULL) {
        /* invalid parameter */
        return -1;
    }
    free(net_conn);
    /* success */
    return 0;
}
