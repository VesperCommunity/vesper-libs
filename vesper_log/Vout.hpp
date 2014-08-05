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

#include <queue>
#include <sstream>
#include <string>

#include "LoggingTypes.hpp"

namespace Vesper {

class Logging;
class LoggingMessage;

class Vout {

    public:

        Vout(Logging *parentts);
        ~Vout();

        static int init();

        void pushMessage(std::string message);

    private:

        Logging *parent;

        /** Mutex for thread-safe access to message queue. */
        static std::mutex lMutex;
        static std::queue<LoggingMessage*> messages;

        static bool threadRunning;
        static std::thread *pipeThread;

        static void pipeFunction();

}; /* class Vout */

}; /* namespace Vesper */


#endif /* VOUT_HPP_INCLUDED */
