/**
 * \file
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef LOGGINGTYPE_HPP_INCLUDED
#define LOGGINGTYPE_HPP_INCLUDED

#include <string>

/**
 * The namespace LoggingTypes will contain enums, structs
 * and other things, that are needed by the Logging class
 * We use a namespace to avoid Name-conflicts
 * --> for example use this: LoggingTypes.client
 * --> avoid using the LoggingTypes namespace
 */
namespace Vesper {

class Logging;

namespace LoggingTypes {

enum LoggingFlags {
    endl, //end of line
    eom  //EndOfMessage
};

enum LoggingLevel {
    l_start,    //startup sequence
    l_debug,    //debug messages
    l_neutral,  //white
    l_warning,  //warnings
    l_error     //errors
};

enum LoggingClientType {
    client, // the logging client is a client
    server  // the logging client is a server
};

struct LoggingMessage {
    Logging *src;
    std::string message;
};

}; /* namespace LoggingTypes */
}; /* namespace Vesper */

#endif /* LOGGINGTYPE_HPP_INCLUDED */
