/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_network_connector.h"

#include <stdlib.h>

/** vsp_network_connector state machine flag. */
enum vsp_connector_state {
    UNINITIALIZED
};

/** State and other data used for network connection. */
struct vsp_network_connector {
    enum vsp_connector_state state;
};

struct vsp_network_connector* vsp_network_connector_new(void)
{
    struct vsp_network_connector *net_conn;
    /* allocate memory */
    net_conn = malloc(sizeof(struct vsp_network_connector));
    if (net_conn == NULL) {
        /* allocation failed */
        return NULL;
    }
    /* initialize struct data */
    net_conn->state = UNINITIALIZED;
    return net_conn;
}

int vsp_network_connector_close(struct vsp_network_connector *net_conn)
{
    if (net_conn == NULL) {
        /* invalid parameter */
        return -1;
    }
    free(net_conn);
    /* success */
    return 0;
}
