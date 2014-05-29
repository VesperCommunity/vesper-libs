/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "minunit.h"

#include <vsp_network_connector.h>

MU_TEST(vesper_sphtp_allocation)
{
    struct vsp_network_connector *net_conn;
    int ret;
    /* test allocation */
    net_conn = vsp_network_connector_new();
    mu_check(net_conn != NULL);
    /* test deallocation */
    ret = vsp_network_connector_close(net_conn);
    mu_check(ret == 0);
}

/* test SphTP implementation */
MU_TEST_SUITE(vesper_sphtp)
{
    MU_RUN_TEST(vesper_sphtp_allocation);
}

int main(void)
{
    MU_RUN_SUITE(vesper_sphtp);
    MU_REPORT();
    return 0;
}
