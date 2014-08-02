/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"
#include "vsp_test.h"

#include <vesper_cmcp/vsp_cmcp_datalist.h>
#include <vesper_util/vsp_error.h>
#include <vesper_util/vsp_util.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/** First data list item id */
#define DATALIST_ITEM1_ID 32349
/** Second data list item id */
#define DATALIST_ITEM2_ID 9273

/** First data list item length */
#define DATALIST_ITEM1_LENGTH 6
/** Second data list item length */
#define DATALIST_ITEM2_LENGTH 7

/** First data list item data */
#define DATALIST_ITEM1_DATA "Hello"
/** Second data list item data */
#define DATALIST_ITEM2_DATA "World!"

/** Create data list and test adding and reading items. */
MU_TEST(vsp_test_cmcp_datalist_test);

MU_TEST(vsp_test_cmcp_datalist_test)
{
    vsp_cmcp_datalist *cmcp_datalist1, *cmcp_datalist2;
    int ret;
    uint16_t data_length;
    void *data_pointer;
    void *data_item_pointer;

    /* allocation */
    cmcp_datalist1 = vsp_cmcp_datalist_create();
    mu_assert(cmcp_datalist1 != NULL, vsp_error_str(vsp_error_num()));

    /* insert data list items */
    ret = vsp_cmcp_datalist_add_item(cmcp_datalist1, DATALIST_ITEM1_ID,
        DATALIST_ITEM1_LENGTH, DATALIST_ITEM1_DATA);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));

    ret = vsp_cmcp_datalist_add_item(cmcp_datalist1, DATALIST_ITEM2_ID,
        DATALIST_ITEM2_LENGTH, DATALIST_ITEM2_DATA);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));

    /* get binary data array */
    ret = vsp_cmcp_datalist_get_data(cmcp_datalist1, &data_length,
        &data_pointer);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));

    /* construct second data list using binary data array */
    cmcp_datalist2 = vsp_cmcp_datalist_create_parse(data_length, data_pointer);
    mu_assert(cmcp_datalist2 != NULL, vsp_error_str(vsp_error_num()));

    /* insert data ID a second time and check for rejection */
    ret = vsp_cmcp_datalist_add_item(cmcp_datalist2, DATALIST_ITEM1_ID,
        DATALIST_ITEM1_LENGTH, DATALIST_ITEM1_DATA);
    mu_assert(ret != 0, vsp_error_str(EINVAL));

    /* get back data list item and verify data */
    data_item_pointer = vsp_cmcp_datalist_get_data_item(cmcp_datalist2,
        DATALIST_ITEM1_ID, DATALIST_ITEM1_LENGTH);
    mu_assert(data_item_pointer != NULL, vsp_error_str(vsp_error_num()));
    mu_assert(memcmp(data_item_pointer, DATALIST_ITEM1_DATA,
        DATALIST_ITEM1_LENGTH) == 0, vsp_error_str(EINVAL));

    data_item_pointer = vsp_cmcp_datalist_get_data_item(cmcp_datalist2,
        DATALIST_ITEM2_ID, DATALIST_ITEM2_LENGTH);
    mu_assert(data_item_pointer != NULL, vsp_error_str(vsp_error_num()));
    mu_assert(memcmp(data_item_pointer, DATALIST_ITEM2_DATA,
        DATALIST_ITEM2_LENGTH) == 0, vsp_error_str(EINVAL));

    /* get back item data with wrong length and check for failure */
    data_item_pointer = vsp_cmcp_datalist_get_data_item(cmcp_datalist2,
        DATALIST_ITEM1_ID, DATALIST_ITEM1_LENGTH + 1);
    mu_assert(data_item_pointer == NULL, vsp_error_str(EINVAL));

    /* get back item data for unknown item ID and check for failure */
    data_item_pointer = vsp_cmcp_datalist_get_data_item(cmcp_datalist2,
        DATALIST_ITEM2_ID + 1, DATALIST_ITEM2_LENGTH);
    mu_assert(data_item_pointer == NULL, vsp_error_str(EINVAL));

    /* deallocation */
    VSP_FREE(data_pointer);
    ret = vsp_cmcp_datalist_free(cmcp_datalist1);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    ret = vsp_cmcp_datalist_free(cmcp_datalist2);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST_SUITE(vsp_test_cmcp_datalist)
{
    MU_RUN_TEST(vsp_test_cmcp_datalist_test);
}
