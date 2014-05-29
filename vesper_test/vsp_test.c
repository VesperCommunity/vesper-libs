/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"

#include <vesper_sphtp/vsp_sphtp.h>

MU_TEST(vesper_sphtp_allocation)
{
    vsp_network_connector_ptr net_conn;
    int ret;
    /* test allocation */
    net_conn = vsp_network_connector_new();
    mu_check(net_conn != NULL);
    /* test deallocation */
    ret = vsp_network_connector_close(net_conn);
    mu_check(ret == 0);
}

MU_TEST(vesper_sphtp_connection)
{
    vsp_network_connector_ptr net_conn;
    int ret;
    /* test allocation */
    net_conn = vsp_network_connector_new();
    mu_check(net_conn != NULL);
    /* test connection */
    ret = vsp_establish_connection(net_conn, "tcp://127.0.0.1:7571",
        "tcp://127.0.0.1:7572");
    mu_check(ret == 0);
    /* test deallocation */
    ret = vsp_network_connector_close(net_conn);
    mu_check(ret == 0);
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
