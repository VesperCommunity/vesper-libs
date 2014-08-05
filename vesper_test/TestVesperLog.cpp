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

#include <vesper_log/Logging.hpp>
#include <vesper_log/Vout.hpp>

/** Print messages using vesper_log module. */
MU_TEST(vsp_test_vesper_log_test);

MU_TEST(vsp_test_vesper_log_test)
{
    Vesper::Logging logger(Vesper::LoggingTypes::server);
    logger << "Testing vesper_log module, logging as server.";
    logger << Vesper::LoggingTypes::eom;
    logger << "Some numbers: " << 1 << ", " << 2.0 << ", " << '3';
    logger << Vesper::LoggingTypes::eom;
}

MU_TEST_SUITE(vsp_test_vesper_log)
{
    MU_RUN_TEST(vsp_test_vesper_log_test);
}
