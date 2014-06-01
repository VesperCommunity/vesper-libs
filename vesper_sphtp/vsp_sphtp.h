/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_SPHTP_H_INCLUDED
#define VSP_SPHTP_H_INCLUDED

#include <vesper_util/vsp_util.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** State and other data used for network connection. */
struct vsp_network_connector;

/** Pointer type used to expose vsp_network_connector data. */
typedef struct vsp_network_connector* vsp_network_connector_ptr;

/**
 * Create new vsp_network_connector object and get a pointer to it.
 * Returned pointer should be freed with vsp_network_connector_close.
 * Returns NULL and sets vsp_error_num if failed.
 */
VESPER_API vsp_network_connector_ptr vsp_network_connector_new(void);

/**
 * Initialize and connect sockets.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_establish_connection(vsp_network_connector_ptr net_conn,
    const char *publish_address, const char *subscribe_address);

/**
 * Free vsp_network_connector object.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_network_connector_close(vsp_network_connector_ptr net_conn);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_SPHTP_H_INCLUDED */
