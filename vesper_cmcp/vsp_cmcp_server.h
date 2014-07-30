/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_CMCP_SERVER_H_INCLUDED
#define VSP_CMCP_SERVER_H_INCLUDED

#include <vesper_util/vsp_api.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** State and other data used for (network) connection. */
struct vsp_cmcp_server;

/** Define type vsp_cmcp_server to avoid 'struct' keyword. */
typedef struct vsp_cmcp_server vsp_cmcp_server;

/**
 * Create new vsp_cmcp_server object.
 * Returned pointer should be freed with vsp_cmcp_server_free().
 * Returns NULL and sets vsp_error_num() if failed.
 */
VSP_API vsp_cmcp_server *vsp_cmcp_server_create(void);

/**
 * Free vsp_cmcp_server object.
 * Object should be created with vsp_cmcp_server_create().
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_server_free(vsp_cmcp_server *cmcp_server);

/**
 * Initialize and bind sockets.
 * Returns non-zero and sets vsp_error_num() if failed.
 * \see vsp_cmcp_server_unbind
 */
VSP_API int vsp_cmcp_server_bind(vsp_cmcp_server *cmcp_server,
    const char *publish_address, const char *subscribe_address);

/**
 * Unbind and deinitialize sockets.
 * Sockets have to be bound with vsp_cmcp_server_bind() first.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_server_unbind(vsp_cmcp_server *cmcp_server);

/**
 * Start message reception thread and return immediately.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_server_start(vsp_cmcp_server *cmcp_server);

/**
 * Stop message reception thread and wait until thread has finished and joined.
 * Returns non-zero and sets vsp_error_num() if thread or this method failed.
 */
VSP_API int vsp_cmcp_server_stop(vsp_cmcp_server *cmcp_server);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_SERVER_H_INCLUDED */
