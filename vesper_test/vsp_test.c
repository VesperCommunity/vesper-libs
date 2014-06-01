/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"

#include <vesper_error/vsp_error.h>
#include <vesper_sphtp/vsp_sphtp.h>

/** Publish socket address. */
#define PUBLISH_ADDRESS "tcp://127.0.0.1:7571"
/** Subscribe socket address. */
#define SUBSCRIBE_ADDRESS "tcp://127.0.0.1:7572"

/** Global testing object. */
static vsp_sphtp_network_connector *net_conn;

/** Create global net_conn object. \see net_conn */
void vesper_sphtp_setup(void);
/** Free global net_conn object. \see net_conn */
void vesper_sphtp_teardown(void);

void vesper_sphtp_setup(void)
{
    net_conn = vsp_sphtp_network_connector_create();
}

void vesper_sphtp_teardown(void)
{
    vsp_sphtp_network_connector_free(net_conn);
}

/** Test vsp_sphtp_network_connector_create() and
 * vsp_sphtp_network_connector_free(). */
MU_TEST(vesper_sphtp_allocation)
{
    vsp_sphtp_network_connector *local_net_conn;
    int ret;
    /* allocation */
    local_net_conn = vsp_sphtp_network_connector_create();
    mu_assert(local_net_conn != NULL, vsp_error_str(vsp_error_num()));
    /* deallocation */
    ret = vsp_sphtp_network_connector_free(local_net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_sphtp_connect(). */
MU_TEST(vesper_sphtp_connection)
{
    int ret;
    /* connection */
    ret = vsp_sphtp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_sphtp_disconnect(). */
MU_TEST(vesper_sphtp_disconnection)
{
    int ret;
    /* connection */
    ret = vsp_sphtp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnection */
    ret = vsp_sphtp_disconnect(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test vsp_sphtp_connect() and subsequent vsp_sphtp_disconnect(). */
MU_TEST(vesper_sphtp_reconnection)
{
    int ret;
    /* connection */
    ret = vsp_sphtp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* disconnection */
    ret = vsp_sphtp_disconnect(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* reconnection */
    ret = vsp_sphtp_connect(net_conn, PUBLISH_ADDRESS, SUBSCRIBE_ADDRESS);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/** Test SphTP implementation. */
MU_TEST_SUITE(vesper_sphtp)
{
    MU_SUITE_CONFIGURE(&vesper_sphtp_setup, &vesper_sphtp_teardown);
    MU_RUN_TEST(vesper_sphtp_connection);
    MU_RUN_TEST(vesper_sphtp_disconnection);
    MU_RUN_TEST(vesper_sphtp_reconnection);
}

/** Run all module tests. */
int main(void)
{
    MU_RUN_TEST(vesper_sphtp_allocation);
    MU_RUN_SUITE(vesper_sphtp);
    MU_REPORT();
    return 0;
}
