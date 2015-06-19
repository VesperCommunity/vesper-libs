/**
 * \file
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef LOGGING_HPP_INCLUDED
#define LOGGING_HPP_INCLUDED

#include <sstream>

#include "LoggingTypes.hpp"

namespace Vesper {

class Logging {
    public:

        /**
         * Invoke the default constructor only once
         * It will initialize the garbageCollector
         * in general and start the thread
         */
        Logging(LoggingTypes::LoggingClientType typets);

        /** Append data to current logging message. */
        template <class T>
        Logging &operator<<(const T &toWrite)
        {
            message << toWrite;
            return *this;
        }

        /** Modify current logging message.
         * When parameter is LoggingFlags::eom,
         * flush() is called. */
        void operator<<(LoggingTypes::LoggingFlags flag);

        /** Finish and enqueue current message in logging system. */
        void flush();

    protected:
    private:

        LoggingTypes::LoggingClientType clientType;

        /** Current message string, continuously appending elements. */
        std::ostringstream message;

        /**
         * The unique identification that will be
         * given to the next client
         */
        volatile static int nextID;

        /**
         * The unique identification
         * the uID 0 is the garbageCollector class
         * itself
         */
        int uniqueID;

};

}; /* namespace Vesper */

#endif /* LOGGING_HPP_INCLUDED */
