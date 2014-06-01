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
struct vsp_sphtp_network_connector;

/** Define type vsp_sphtp_network_connector to avoid 'struct' keyword. */
typedef struct vsp_sphtp_network_connector vsp_sphtp_network_connector;

/**
 * Create new vsp_sphtp_network_connector object and get a pointer to it.
 * Returned pointer should be freed with vsp_sphtp_network_connector_free.
 * Returns NULL and sets vsp_error_num if failed.
 */
VESPER_API vsp_sphtp_network_connector*
    vsp_sphtp_network_connector_create(void);

/**
 * Initialize and connect sockets.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_sphtp_connect(vsp_sphtp_network_connector *net_conn,
    const char *publish_address, const char *subscribe_address);

/**
 * Disconnect and deinitialize sockets.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_sphtp_disconnect(vsp_sphtp_network_connector *net_conn);

/**
 * Run event loop for message reception. Should run in its own thread.
 * Terminates when vsp_sphtp_reception_thread_stop is called.
 * Returns non-zero and sets vsp_error_num if suddenly interrupted or failed.
 */
VESPER_API int vsp_sphtp_reception_thread_run(
    vsp_sphtp_network_connector *net_conn);

/**
 * Stop event loop for message reception.
 * Does not wait until vsp_sphtp_reception_thread_run has finished.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_sphtp_reception_thread_stop(
    vsp_sphtp_network_connector *net_conn);

/**
 * Free vsp_sphtp_network_connector object.
 * Returns non-zero and sets vsp_error_num if failed.
 */
VESPER_API int vsp_sphtp_network_connector_free(
    vsp_sphtp_network_connector* net_conn);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_SPHTP_H_INCLUDED */
