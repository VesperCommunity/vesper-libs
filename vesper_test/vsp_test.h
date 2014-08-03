/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_TEST_H_INCLUDED
#define VSP_TEST_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** Server publish socket address. */
#define SERVER_PUBLISH_ADDRESS "tcp://127.0.0.1:7571"
/** Server subscribe socket address. */
#define SERVER_SUBSCRIBE_ADDRESS "tcp://127.0.0.1:7572"


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


/** Test CMCP implementation. */
MU_TEST_SUITE(vsp_test_cmcp_connection);
/** Test data list implementation. */
MU_TEST_SUITE(vsp_test_cmcp_datalist);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_TEST_H_INCLUDED */
