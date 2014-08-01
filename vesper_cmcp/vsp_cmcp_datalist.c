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
