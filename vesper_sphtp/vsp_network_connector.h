/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_NETWORK_CONNECTOR_H_INCLUDED
#define VSP_NETWORK_CONNECTOR_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/* only export API functions prefixed with SPHTP_API */
#if defined _WIN32
  #if defined SPHTP_BUILD_API
    /* build dll */
    #define SPHTP_API __declspec(dllexport)
  #else
    /* use dll */
    #define SPHTP_API __declspec(dllimport)
  #endif /* defined SPHTP_BUILD_API*/
#else
  #if __GNUC__ >= 4
    #define SPHTP_API __attribute__((visibility("default")))
  #else
    #define SPHTP_API
  #endif
#endif /* defined _WIN32 */

/** State and other data used for network connection. */
struct vsp_network_connector;

/**
 * Create new vsp_network_connector object. Returns NULL if failed.
 * Returned pointer should be freed with vsp_network_connector_close.
 */
SPHTP_API struct vsp_network_connector* vsp_network_connector_new(void);

/** Free vsp_network_connector object. Returns non-zero if failed. */
SPHTP_API int vsp_network_connector_close(
    struct vsp_network_connector *net_conn);

#undef SPHTP_API

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_NETWORK_CONNECTOR_H_INCLUDED */
