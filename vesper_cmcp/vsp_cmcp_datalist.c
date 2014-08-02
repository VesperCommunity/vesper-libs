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
    uint16_t data_item_ids[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Data list item lengths. */
    uint16_t data_item_lengths[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Data list item data pointers. */
    void *data_item_pointers[VSP_CMCP_DATALIST_MAX_ITEMS];
    /** Number of stored data list items. */
    uint16_t data_item_count;
};

/** Search for a specific data list item by its ID.
 * Returns item index if found and -1 else. */
static int _vsp_cmcp_datalist_find_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id);

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

vsp_cmcp_datalist *vsp_cmcp_datalist_create_parse(uint16_t data_length,
    void *data_pointer)
{
    uint16_t data_item_id;
    uint16_t data_item_length;
    void *data_item_pointer;
    /* using byte pointer for safe pointer arithmetic */
    uint8_t *current_data_pointer;

    vsp_cmcp_datalist *cmcp_datalist;
    /* allocate memory */
    VSP_ALLOC(cmcp_datalist, vsp_cmcp_datalist, return NULL);
    /* initialize struct data: set number of list items to zero */
    cmcp_datalist->data_item_count = 0;
    /* add data list items */
    current_data_pointer = data_pointer;
    while (data_length >= 4) {
        data_item_id = *(uint16_t*) current_data_pointer;
        current_data_pointer += 2;
        data_length -= 2;

        data_item_length = *(uint16_t*) current_data_pointer;
        current_data_pointer += 2;
        data_length -= 2;

        data_item_pointer = current_data_pointer;
        current_data_pointer += data_length;
        data_length -= data_item_length;

        /* add data list item; failures are silently ignored */
        vsp_cmcp_datalist_add_item(cmcp_datalist, data_item_id,
            data_item_length, data_item_pointer);
    }
    /* return struct pointer */
    return cmcp_datalist;
}

int vsp_cmcp_datalist_add_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id, uint16_t data_item_length, void *data_item_pointer)
{
    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return -1);

    /* check data list item count */
    VSP_ASSERT(cmcp_datalist->data_item_count < VSP_CMCP_DATALIST_MAX_ITEMS,
        vsp_error_set_num(ENOMEM); return -1);

    /* check data list item was not added yet */
    VSP_CHECK(_vsp_cmcp_datalist_find_item(cmcp_datalist, data_item_id) == -1,
        vsp_error_set_num(EALREADY); return -1);

    /* add data list item */
    cmcp_datalist->data_item_ids[cmcp_datalist->data_item_count] = data_item_id;
    cmcp_datalist->data_item_lengths[cmcp_datalist->data_item_count] =
        data_item_length;
    cmcp_datalist->data_item_pointers[cmcp_datalist->data_item_count] =
        data_item_pointer;
    ++cmcp_datalist->data_item_count;

    /* success */
    return 0;
}

void *vsp_cmcp_datalist_get_data_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id, uint16_t data_item_length)
{
    int index;

    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return NULL);

    /* search for data ID */
    index = _vsp_cmcp_datalist_find_item(cmcp_datalist, data_item_id);

    /* check data list item index */
    VSP_CHECK(index != -1, vsp_error_set_num(EINVAL); return NULL);

    /* check data list item length */
    VSP_CHECK(cmcp_datalist->data_item_lengths[index] == data_item_length,
        vsp_error_set_num(EINVAL); return NULL);

    /* return data pointer */
    return cmcp_datalist->data_item_pointers[index];
}

int _vsp_cmcp_datalist_find_item(vsp_cmcp_datalist *cmcp_datalist,
    uint16_t data_item_id)
{
    int index;

    /* check parameter */
    VSP_ASSERT(cmcp_datalist != NULL, vsp_error_set_num(EINVAL); return -1);

    for (index = 0; index < cmcp_datalist->data_item_count; ++index) {
        if (cmcp_datalist->data_item_ids[index] == data_item_id) {
            /* data ID found */
            return index;
        }
    }

    /* data ID not found */
    return -1;
}
