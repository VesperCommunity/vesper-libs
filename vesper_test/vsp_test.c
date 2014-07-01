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
#include <vesper_cmcp/vsp_cmcp.h>

/** Publish socket address. */
#define PUBLISH_ADDRESS "tcp://127.0.0.1:7571"
/** Subscribe socket address. */
#define SUBSCRIBE_ADDRESS "tcp://127.0.0.1:7572"

/** Global testing object. */
static vsp_cmcp_connector *net_conn;

/** Create global net_conn object. \see net_conn */
void vsp_cmcp_setup(void);
/** Free global net_conn object. \see net_conn */
void vsp_cmcp_teardown(void);

void vsp_cmcp_setup(void)
{
    net_conn = vsp_cmcp_connector_create();
}

void vsp_cmcp_teardown(void)
{
    vsp_cmcp_connector_free(net_conn);
}

/** Test vsp_cmcp_connector_create() and
 * vsp_cmcp_connector_free(). */
MU_TEST(vsp_cmcp_allocation)
{
    vsp_cmcp_connector *local_net_conn;
    int ret;
    /* allocation */
    local_net_conn = vsp_cmcp_connector_create();
    mu_assert(local_net_conn != NULL, vsp_error_str(vsp_error_num()));
    /* deallocation */
    ret = vsp_cmcp_connector_free(local_net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_cmcp_connect(). */
MU_TEST(vsp_cmcp_connection)
{
    int ret;
    /* connection */
    ret = vsp_cmcp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_cmcp_disconnect(). */
MU_TEST(vsp_cmcp_disconnection)
{
    int ret;
    /* connection */
    ret = vsp_cmcp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnection */
    ret = vsp_cmcp_disconnect(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_cmcp_connect() and subsequent vsp_cmcp_disconnect(). */
MU_TEST(vsp_cmcp_reconnection)
{
    int ret;
    /* connection */
    ret = vsp_cmcp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnection */
    ret = vsp_cmcp_disconnect(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* reconnection */
    ret = vsp_cmcp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test CMCP implementation. */
MU_TEST_SUITE(vesper_cmcp)
{
    MU_SUITE_CONFIGURE(&vsp_cmcp_setup, &vsp_cmcp_teardown);
    MU_RUN_TEST(vsp_cmcp_connection);
    MU_RUN_TEST(vsp_cmcp_disconnection);
    MU_RUN_TEST(vsp_cmcp_reconnection);
}

/** Run all module tests. */
int main(void)
{
    MU_RUN_TEST(vsp_cmcp_allocation);
    MU_RUN_SUITE(vesper_cmcp);
    MU_REPORT();
    return 0;
}
