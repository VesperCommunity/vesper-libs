/**
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Logging.hpp"

using namespace Vesper;

int Logging::nextID = 1;

Logging::Logging() :
    out(this)
{
    uniqueID = 0;
}

Logging::Logging(LoggingTypes::LoggingClientType typets) :
    out(this)
{
    clientType = typets;

    uniqueID = nextID;
    nextID++;
}

Logging::~Logging()
{

}

int Logging::getID()
{
    return uniqueID;
}

LoggingTypes::LoggingClientType Logging::getType()
{
    return clientType;
}

void Logging::flush()
{
    out.flush();
}
