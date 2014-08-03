/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_CMCP_MESSAGE_H_INCLUDED
#define VSP_CMCP_MESSAGE_H_INCLUDED

#include "vsp_cmcp_datalist.h"

#include <vesper_util/vsp_api.h>
#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** Size of message headers in bytes:
 * 2 bytes topic ID, 2 bytes sender ID, 2 bytes command ID. */
#define VSP_CMCP_MESSAGE_HEADER_LENGTH 6

/** Message data sent over (network) connection. */
struct vsp_cmcp_message;

/** Define type vsp_cmcp_message to avoid 'struct' keyword. */
typedef struct vsp_cmcp_message vsp_cmcp_message;

/**
 * Create new vsp_cmcp_message object.
 * Returned pointer should be freed with vsp_cmcp_message_free().
 * The vsp_cmcp_message will not free the vsp_cmcp_datalist object and it has
 * to be accessible until vsp_cmcp_message_free() is called.
 * Returns NULL and sets vsp_error_num() if failed.
 */
VSP_API vsp_cmcp_message *vsp_cmcp_message_create(uint16_t topic_id,
    uint16_t sender_id, uint16_t command_id, vsp_cmcp_datalist *cmcp_datalist);

/**
 * Free vsp_cmcp_message object.
 * Object should be created with vsp_cmcp_message_create().
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_message_free(vsp_cmcp_message *cmcp_message);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_MESSAGE_H_INCLUDED */
