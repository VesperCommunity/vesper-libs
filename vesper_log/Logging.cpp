/**
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Logging.hpp"

#include "Vout.hpp"

using namespace Vesper;

int Logging::nextID = 1;

Logging::Logging(LoggingTypes::LoggingClientType typets)
{
    clientType = typets;

    uniqueID = nextID;
    nextID++;
}

void Logging::operator<<(LoggingTypes::LoggingFlags flag)
{
    switch (flag) {
        case LoggingTypes::eom:
            flush();
          break;

        default:
            //unknown flag
          break;
    }
}

void Logging::flush()
{
    // copy and clear current message string
    std::string messageStr = message.str();
    message.str(std::string());
    // push message string
    Vout::pushMessage(messageStr, clientType, uniqueID);
}
