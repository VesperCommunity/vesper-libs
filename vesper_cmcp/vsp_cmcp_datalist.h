/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_CMCP_DATALIST_H_INCLUDED
#define VSP_CMCP_DATALIST_H_INCLUDED

#include <vesper_util/vsp_api.h>
#include <stdint.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/**
 * Data list storing any number of data list items.
 * A data list item consists of an ID, a length and the data itself.
 */
struct vsp_cmcp_datalist;

/** Define type vsp_cmcp_datalist to avoid 'struct' keyword. */
typedef struct vsp_cmcp_datalist vsp_cmcp_datalist;

/**
 * Create new vsp_cmcp_datalist object.
 * Returned pointer should be freed with vsp_cmcp_datalist_free().
 * Returns NULL and sets vsp_error_num() if failed.
 */
VSP_API vsp_cmcp_datalist *vsp_cmcp_datalist_create(void);

/**
 * Free vsp_cmcp_datalist object.
 * Object should be created with vsp_cmcp_datalist_create().
 * This function does not free data stored in the data list.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_datalist_free(vsp_cmcp_datalist *cmcp_datalist);

/**
 * Create new vsp_cmcp_datalist object of binary data.
 * The data will not be copied and only pointers to it are stored, so the data
 * has to be accessible until vsp_cmcp_datalist_free() is called.
 * Returned pointer should be freed with vsp_cmcp_datalist_free().
 * Returns NULL and sets vsp_error_num() if failed.
 */
VSP_API vsp_cmcp_datalist *vsp_cmcp_datalist_create_parse(uint16_t data_length,
    void *data_pointer);

/**
 * Calculate necessary length of a binary data array storing all list items.
 * Returns negative value and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_datalist_get_data_length(vsp_cmcp_datalist *cmcp_datalist);

/**
 * Copy list content to specified binary data array.
 * The specified array has to be at least as long as the number of bytes
 * vsp_cmcp_datalist_get_data_length() returns.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_datalist_get_data(vsp_cmcp_datalist *cmcp_datalist,
    void *data_pointer);

/**
 * Add a data list item to the data list.
 * The data will not be copied and only a pointer to it is stored, so the data
 * has to be accessible until vsp_cmcp_datalist_free() is called.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_datalist_add_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id, uint16_t data_item_length, void *data_item_pointer);

/**
 * Get pointer to data stored in the data list.
 * The data should be immediately copied for further use, as no accessibility of
 * the data can be guaranteed after vsp_cmcp_datalist_free() was called.
 * Returns NULL and sets vsp_error_num() if failed or length does not match.
 */
VSP_API void *vsp_cmcp_datalist_get_data_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id, uint16_t data_item_length);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_DATALIST_H_INCLUDED */
