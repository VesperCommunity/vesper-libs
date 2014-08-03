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
#include <vesper_cmcp/vsp_cmcp_message.h>
#include <vesper_util/vsp_error.h>
#include <vesper_util/vsp_util.h>
#include <stdio.h>
#include <string.h>

/** Create message and test creating binary data and parse it. */
MU_TEST(vsp_test_cmcp_message_test);

MU_TEST(vsp_test_cmcp_message_test)
{
    vsp_cmcp_datalist *cmcp_datalist1, *cmcp_datalist2;
    vsp_cmcp_message *cmcp_message1, *cmcp_message2;
    int ret;
    int data_length;
    void *data_pointer;
    void *data_item_pointer;
    uint16_t message_id;

    /* allocate data list */
    cmcp_datalist1 = vsp_cmcp_datalist_create();
    mu_assert(cmcp_datalist1 != NULL, vsp_error_str(vsp_error_num()));
    /* insert data list items */
    ret = vsp_cmcp_datalist_add_item(cmcp_datalist1, DATALIST_ITEM1_ID,
        DATALIST_ITEM1_LENGTH, DATALIST_ITEM1_DATA);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    ret = vsp_cmcp_datalist_add_item(cmcp_datalist1, DATALIST_ITEM2_ID,
        DATALIST_ITEM2_LENGTH, DATALIST_ITEM2_DATA);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));

    /* allocate message */
    cmcp_message1 = vsp_cmcp_message_create(MESSAGE_TOPIC_ID, MESSAGE_SENDER_ID,
        MESSAGE_COMMAND_ID, cmcp_datalist1);

    /* get binary data array length */
    data_length = vsp_cmcp_message_get_data_length(cmcp_message1);
    /* fixed message header length 6 has to be updated if
     * VSP_CMCP_MESSAGE_HEADER_LENGTH is changed */
    mu_assert(data_length ==
        (DATALIST_ITEM1_LENGTH + DATALIST_ITEM2_LENGTH + 8 + 6),
        vsp_error_str(EINVAL));
    /* allocate array */
    data_pointer = malloc(data_length);
    mu_assert(data_pointer != NULL, vsp_error_str(ENOMEM));
    /* get binary data */
    ret = vsp_cmcp_message_get_data(cmcp_message1, data_pointer);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));

    /* construct second message using binary data array */
    cmcp_message2 = vsp_cmcp_message_create_parse(data_length, data_pointer);
    mu_assert(cmcp_message2 != NULL, vsp_error_str(vsp_error_num()));

    /* get back and verify message IDs */
    ret = vsp_cmcp_message_get_id(cmcp_message2, VSP_CMCP_MESSAGE_TOPIC_ID,
        &message_id);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    mu_assert(message_id == MESSAGE_TOPIC_ID, vsp_error_str(EINVAL));
    ret = vsp_cmcp_message_get_id(cmcp_message2, VSP_CMCP_MESSAGE_SENDER_ID,
        &message_id);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    mu_assert(message_id == MESSAGE_SENDER_ID, vsp_error_str(EINVAL));
    ret = vsp_cmcp_message_get_id(cmcp_message2, VSP_CMCP_MESSAGE_COMMAND_ID,
        &message_id);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    mu_assert(message_id == MESSAGE_COMMAND_ID, vsp_error_str(EINVAL));

    /* get data list from second message */
    cmcp_datalist2 = vsp_cmcp_message_get_datalist(cmcp_message2);
    mu_assert(cmcp_datalist2 != NULL, vsp_error_str(vsp_error_num()));

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

    /* deallocation; cmcp_datalist2 will be freed by cmcp_message2 */
    VSP_FREE(data_pointer);
    ret = vsp_cmcp_datalist_free(cmcp_datalist1);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    ret = vsp_cmcp_message_free(cmcp_message1);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    ret = vsp_cmcp_message_free(cmcp_message2);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST_SUITE(vsp_test_cmcp_message)
{
    MU_RUN_TEST(vsp_test_cmcp_message_test);
}
