/**
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_cmcp_datalist.h"

#include <vesper_util/vsp_error.h>
#include <vesper_util/vsp_util.h>
#include <stdlib.h>

#define VSP_CMCP_DATALIST_MAX_ITEMS 16

/** State and other data used for network connection. */
struct vsp_cmcp_datalist {
    /** Data list item IDs. */
    int data_ids[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Data list item lengths. */
    int data_lengths[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Data list item data pointers. */
    void *data_pointers[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Number of stored data list items. */
    int data_item_count;
};

/** Search for a specific data list item by its ID.
 * Returns item index if found and -1 else. */
int _vsp_cmcp_datalist_find_item(vsp_cmcp_datalist *cmcp_datalist, int data_id);

vsp_cmcp_datalist *vsp_cmcp_datalist_create(void)
{
    vsp_cmcp_datalist *cmcp_datalist;
    /* allocate memory */
    VSP_ALLOC(cmcp_datalist, vsp_cmcp_datalist, return NULL);
    /* initialize struct data: set number of list items to zero */
    cmcp_datalist->data_item_count = 0;
    /* return struct pointer */
    return cmcp_datalist;
}

int vsp_cmcp_datalist_free(vsp_cmcp_datalist *cmcp_datalist)
{
    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return -1);

    /* free memory */
    VSP_FREE(cmcp_datalist);
    return 0;
}

int vsp_cmcp_datalist_add_item(vsp_cmcp_datalist *cmcp_datalist,
    int data_id, int data_length, void *data_pointer)
{
    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return -1);

    /* check data list item count */
    VSP_ASSERT(cmcp_datalist->data_item_count < VSP_CMCP_DATALIST_MAX_ITEMS,
        vsp_error_set_num(ENOMEM); return -1);

    /* check data list item was not added yet */
    VSP_ASSERT(_vsp_cmcp_datalist_find_item(cmcp_datalist, data_id) == -1,
        vsp_error_set_num(EALREADY); return -1);

    /* add data list item */
    cmcp_datalist->data_ids[cmcp_datalist->data_item_count] = data_id;
    cmcp_datalist->data_lengths[cmcp_datalist->data_item_count] = data_length;
    cmcp_datalist->data_pointers[cmcp_datalist->data_item_count] = data_pointer;
    ++cmcp_datalist->data_item_count;

    /* success */
    return 0;
}

int _vsp_cmcp_datalist_find_item(vsp_cmcp_datalist *cmcp_datalist, int data_id)
{
    int index;

    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return -1);

    for (index = 0; index < cmcp_datalist->data_item_count; ++index) {
        if (cmcp_datalist->data_ids[index] == data_id) {
            /* data ID found */
            return index;
        }
    }

    /* data ID not found */
    return -1;
}
