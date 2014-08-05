/**
 * \file
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef VOUT_HPP_INCLUDED
#define VOUT_HPP_INCLUDED

#include <thread>
#include <mutex>

#include <sstream>
#include <string>

#include "LoggingTypes.hpp"

namespace Vesper {

class Logging;

class Vout {

    public:

        Vout(Logging *parentts);
        ~Vout();

        static int init();

        /** Append data to current logging message. */
        template <class T>
        Vout &operator<<(const T &toWrite)
        {
            message << toWrite;
            return *this;
        }

        /** Modify current logging message.
         * When parameter is LoggingFlags::eom or LoggingFlags::endl,
         * flush() is called. */
        void operator<<(LoggingTypes::LoggingFlags flag);

        /** Finish and print current logging message. */
        void flush();

    private:

        Logging *parent;

        std::ostringstream message;

        /**
         * When a LoggingPipe reaches LogginType::eom the message is complete
         * and will be pushed to lFIFO (logging FIFO)
         * lFIFO will be written by the pipeFunction.
         */

        static std::mutex lMutex;
        static LoggingTypes::LoggingPipe *lFIFOfirst;
        static LoggingTypes::LoggingPipe *lFIFOlast;

        static bool threadRunning;
        static std::thread *pipeThread;

        static void pipeFunction();

}; /* class Vout */

}; /* namespace Vesper */


#endif /* VOUT_HPP_INCLUDED */
