/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"

#include <vesper_util/vsp_error.h>
#include <vesper_cmcp/vsp_cmcp_client.h>

/** Publish socket address. */
#define PUBLISH_ADDRESS "tcp://127.0.0.1:7571"
/** Subscribe socket address. */
#define SUBSCRIBE_ADDRESS "tcp://127.0.0.1:7572"

/** Global CMCP client object. */
static vsp_cmcp_client *global_cmcp_client;

/** Create global global_cmcp_client object. \see global_cmcp_client */
void vsp_cmcp_client_setup(void);
/** Free global global_cmcp_client object. \see global_cmcp_client */
void vsp_cmcp_client_teardown(void);

void vsp_cmcp_client_setup(void)
{
    global_cmcp_client = vsp_cmcp_client_create();
}

void vsp_cmcp_client_teardown(void)
{
    vsp_cmcp_client_free(global_cmcp_client);
}

/** Test vsp_cmcp_client_create() and
 * vsp_cmcp_client_free(). */
MU_TEST(vsp_cmcp_client_allocation)
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

/** Test vsp_cmcp_client_connect() and subsequent
 * vsp_cmcp_client_disconnect(). */
MU_TEST(vsp_cmcp_client_reconnection)
{
    int ret;
    /* connection */
    ret = vsp_cmcp_client_connect(global_cmcp_client, PUBLISH_ADDRESS,
        SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnection */
    ret = vsp_cmcp_client_disconnect(global_cmcp_client);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* reconnection */
    ret = vsp_cmcp_client_connect(global_cmcp_client, PUBLISH_ADDRESS,
        SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test CMCP implementation. */
MU_TEST_SUITE(vesper_cmcp_client)
{
    MU_SUITE_CONFIGURE(&vsp_cmcp_client_setup, &vsp_cmcp_client_teardown);
    MU_RUN_TEST(vsp_cmcp_client_reconnection);
}

/** Run all module tests. */
int main(void)
{
    MU_RUN_TEST(vsp_cmcp_client_allocation);
    MU_RUN_SUITE(vesper_cmcp_client);
    MU_REPORT();
    return 0;
}
