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

/** Message ID types. */
typedef enum {
    /** Message topic or receiver ID. */
    VSP_CMCP_MESSAGE_TOPIC_ID,
    /** Message sender ID. */
    VSP_CMCP_MESSAGE_SENDER_ID,
    /** Message command ID. */
    VSP_CMCP_MESSAGE_COMMAND_ID
} vsp_cmcp_message_id_type;

/** Message data sent over (network) connection. */
struct vsp_cmcp_message;

/** Define type vsp_cmcp_message to avoid 'struct' keyword. */
typedef struct vsp_cmcp_message vsp_cmcp_message;

/**
 * Create new vsp_cmcp_message object to send message data.
 * Returned pointer should be freed with vsp_cmcp_message_free().
 * The specified vsp_cmcp_datalist object must not be NULL.
 * The vsp_cmcp_message will not free the vsp_cmcp_datalist object and it has
 * to be accessible until vsp_cmcp_message_free() is called.
 * Returns NULL and sets vsp_error_num() if failed.
 */
vsp_cmcp_message *vsp_cmcp_message_create(uint16_t topic_id,
    uint16_t sender_id, uint16_t command_id, vsp_cmcp_datalist *cmcp_datalist);

/**
 * Free vsp_cmcp_message object.
 * Object should be created with vsp_cmcp_message_create() or
 * vsp_cmcp_message_create_parse().
 * Frees internal vsp_cmcp_datalist object when created with
 * vsp_cmcp_message_create_parse().
 * Returns non-zero and sets vsp_error_num() if failed.
 */
int vsp_cmcp_message_free(vsp_cmcp_message *cmcp_message);

/**
 * Create new vsp_cmcp_message object from received binary data.
 * The data will be copied partially and pointers to it are stored, so the data
 * has to be accessible until vsp_cmcp_message_free() is called.
 * This function creates an internal object of type vsp_cmcp_datalist.
 * Returned pointer should be freed with vsp_cmcp_message_free().
 * Returns NULL and sets vsp_error_num() if failed.
 */
vsp_cmcp_message *vsp_cmcp_message_create_parse(uint16_t data_length,
    void *data_pointer);

/**
 * Calculate necessary length of a binary data array storing the message data.
 * This function should only be called for messages created with
 * vsp_cmcp_message_create().
 * Returns negative value and sets vsp_error_num() if failed.
 */
int vsp_cmcp_message_get_data_length(vsp_cmcp_message *cmcp_message);

/**
 * Copy message data to specified binary data array.
 * The specified array has to be at least as long as the number of bytes
 * vsp_cmcp_message_get_data_length() returns.
 * This function should only be called for messages created with
 * vsp_cmcp_message_create().
 * Returns non-zero and sets vsp_error_num() if failed.
 */
int vsp_cmcp_message_get_data(vsp_cmcp_message *cmcp_message,
    void *data_pointer);

/**
 * Get specified ID and copy to specified address.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
int vsp_cmcp_message_get_id(vsp_cmcp_message *cmcp_message,
    vsp_cmcp_message_id_type id_type, uint16_t *id_pointer);

/**
 * Get data list parsed by this message object.
 * This function should only be called for messages created with
 * vsp_cmcp_message_create_parse().
 * Returns NULL and sets vsp_error_num() if failed.
 */
vsp_cmcp_datalist *vsp_cmcp_message_get_datalist(
    vsp_cmcp_message *cmcp_message);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_MESSAGE_H_INCLUDED */
