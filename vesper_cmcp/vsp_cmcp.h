/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_CMCP_H_INCLUDED
#define VSP_CMCP_H_INCLUDED

#include <vesper_util/vsp_api.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** State and other data used for (network) connection. */
struct vsp_cmcp_connector;

/** Define type vsp_cmcp_connector to avoid 'struct' keyword. */
typedef struct vsp_cmcp_connector vsp_cmcp_connector;

/**
 * Create new vsp_cmcp_connector object.
 * Returned pointer should be freed with vsp_cmcp_connector_free().
 * Returns NULL and sets vsp_error_num() if failed.
 */
VSP_API vsp_cmcp_connector*
    vsp_cmcp_connector_create(void);

/**
 * Free vsp_cmcp_connector object.
 * Object should be created with vsp_cmcp_connector_create().
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_connector_free(
    vsp_cmcp_connector* net_conn);

/**
 * Initialize and connect sockets.
 * Returns non-zero and sets vsp_error_num() if failed.
 * \see vsp_cmcp_disconnect
 */
VSP_API int vsp_cmcp_connect(vsp_cmcp_connector *net_conn,
    const char *publish_address, const char *subscribe_address);

/**
 * Disconnect and deinitialize sockets.
 * Sockets have to be connected with vsp_cmcp_connect() first.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_disconnect(vsp_cmcp_connector *net_conn);

/**
 * Run event loop for message reception. Should run in its own thread.
 * Terminates when vsp_cmcp_reception_thread_stop() is called.
 * Returns non-zero and sets vsp_error_num() if interrupted or failed.
 */
VSP_API int vsp_cmcp_reception_thread_run(
    vsp_cmcp_connector *net_conn);

/**
 * Stop event loop for message reception.
 * Does not wait until vsp_cmcp_reception_thread_run() has finished.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_reception_thread_stop(
    vsp_cmcp_connector *net_conn);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_H_INCLUDED */
