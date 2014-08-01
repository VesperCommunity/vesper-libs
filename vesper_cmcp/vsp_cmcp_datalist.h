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
 * Add a data list item to the data list.
 * The data will not be copied and only a pointer to it is stored, so the data
 * has to be accessible until vsp_cmcp_datalist_free() is called.
 * Returns non-zero and sets vsp_error_num() if failed.
 */
VSP_API int vsp_cmcp_datalist_add_item(vsp_cmcp_datalist *cmcp_datalist,
    int data_id, int data_length, void *data_pointer);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_CMCP_DATALIST_H_INCLUDED */
