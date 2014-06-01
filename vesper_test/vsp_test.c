/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"

#include <vesper_error/vsp_error.h>
#include <vesper_sphtp/vsp_sphtp.h>

MU_TEST(vesper_sphtp_allocation)
{
    vsp_sphtp_network_connector *net_conn;
    int ret;
    /* test allocation */
    net_conn = vsp_sphtp_network_connector_create();
    mu_assert(net_conn != NULL, vsp_error_str(vsp_error_num()));
    /* test deallocation */
    ret = vsp_sphtp_network_connector_free(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

MU_TEST(vesper_sphtp_connection)
{
    vsp_sphtp_network_connector *net_conn;
    int ret;
    /* test allocation */
    net_conn = vsp_sphtp_network_connector_create();
    mu_assert(net_conn != NULL, vsp_error_str(vsp_error_num()));
    /* test connection */
    ret = vsp_sphtp_connect(net_conn, "tcp://127.0.0.1:7571",
        "tcp://127.0.0.1:7572");
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
    /* test deallocation */
    ret = vsp_sphtp_network_connector_free(net_conn);
    mu_assert(ret == 0, vsp_error_str(vsp_error_num()));
}

/* test SphTP implementation */
MU_TEST_SUITE(vesper_sphtp)
{
    MU_RUN_TEST(vesper_sphtp_allocation);
    MU_RUN_TEST(vesper_sphtp_connection);
}

int main(void)
{
    MU_RUN_SUITE(vesper_sphtp);
    MU_REPORT();
    return 0;
}
