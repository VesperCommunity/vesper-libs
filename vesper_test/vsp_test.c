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

#include <stddef.h>
#include <stdio.h>

/** Run all module tests. */
int main(void)
{
    MU_RUN_SUITE(vsp_test_cmcp_connection);
    MU_RUN_SUITE(vsp_test_cmcp_datalist);
    MU_REPORT();
    return 0;
}
