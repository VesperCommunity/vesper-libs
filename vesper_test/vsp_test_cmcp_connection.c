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

#include <vesper_cmcp/vsp_cmcp_client.h>
#include <vesper_cmcp/vsp_cmcp_server.h>
#include <vesper_util/vsp_error.h>
#include <stddef.h>
#include <stdio.h>

/** Server publish socket address. */
#define SERVER_PUBLISH_ADDRESS "tcp://127.0.0.1:7571"
/** Server subscribe socket address. */
#define SERVER_SUBSCRIBE_ADDRESS "tcp://127.0.0.1:7572"

/** Global CMCP server object. */
vsp_cmcp_server *global_cmcp_server;

/** Global CMCP client object. */
vsp_cmcp_client *global_cmcp_client;

/** Create global global_cmcp_server and global_cmcp_client objects. */
void vsp_test_cmcp_connection_setup(void);

/** Free global global_cmcp_server and global_cmcp_client objects. */
void vsp_test_cmcp_connection_teardown(void);

/** Test vsp_cmcp_server_create() and vsp_cmcp_server_free(). */
MU_TEST(vsp_test_cmcp_server_allocation);

/** Test vsp_cmcp_client_create() and vsp_cmcp_client_free(). */
MU_TEST(vsp_test_cmcp_client_allocation);

/** Test connection between vsp_cmcp_server and vsp_cmcp_client. */
MU_TEST(vsp_test_cmcp_connection_test);

void vsp_test_cmcp_connection_setup(void)
{
    global_cmcp_server = vsp_cmcp_server_create();
    global_cmcp_client = vsp_cmcp_client_create();
}

void vsp_test_cmcp_connection_teardown(void)
{
    vsp_cmcp_client_free(global_cmcp_client);
    vsp_cmcp_server_free(global_cmcp_server);
}

MU_TEST(vsp_test_cmcp_server_allocation)
{
    vsp_cmcp_server *local_global_cmcp_server;
    int ret;
    /* allocation */
    local_global_cmcp_server = vsp_cmcp_server_create();
    mu_assert(local_global_cmcp_server != NULL, vsp_error_str(vsp_error_num()));
    /* deallocation */
    ret = vsp_cmcp_server_free(local_global_cmcp_server);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST(vsp_test_cmcp_client_allocation)
{
    vsp_cmcp_client *local_global_cmcp_client;
    int ret;
    /* allocation */
    local_global_cmcp_client = vsp_cmcp_client_create();
    mu_assert(local_global_cmcp_client != NULL, vsp_error_str(vsp_error_num()));
    /* deallocation */
    ret = vsp_cmcp_client_free(local_global_cmcp_client);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST(vsp_test_cmcp_connection_test)
{
    int ret;
    /* bind */
    ret = vsp_cmcp_server_bind(global_cmcp_server, SERVER_PUBLISH_ADDRESS,
        SERVER_SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* connect */
    ret = vsp_cmcp_client_connect(global_cmcp_client, SERVER_SUBSCRIBE_ADDRESS,
        SERVER_PUBLISH_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* start server */
    ret = vsp_cmcp_server_start(global_cmcp_server);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* start client */
    ret = vsp_cmcp_client_start(global_cmcp_client);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* stop client */
    ret = vsp_cmcp_client_stop(global_cmcp_client);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* stop server */
    ret = vsp_cmcp_server_stop(global_cmcp_server);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnect */
    ret = vsp_cmcp_client_disconnect(global_cmcp_client);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* unbind */
    ret = vsp_cmcp_server_unbind(global_cmcp_server);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST_SUITE(vsp_test_cmcp_connection)
{
    MU_RUN_TEST(vsp_test_cmcp_server_allocation);
    MU_RUN_TEST(vsp_test_cmcp_client_allocation);
    MU_SUITE_CONFIGURE(&vsp_test_cmcp_connection_setup,
        &vsp_test_cmcp_connection_teardown);
    MU_RUN_TEST(vsp_test_cmcp_connection_test);
}
