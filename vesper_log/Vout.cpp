/**
 * \authors Simon Michalke, Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Vout.hpp"

#include "Logging.hpp"

#include <iomanip>
#include <iostream>

namespace Vesper {

struct LoggingMessage {
    std::string message;
    LoggingTypes::LoggingClientType type;
    int id;
};

}; /* namespace Vesper */

using namespace Vesper;

Vout Vout::staticInstance = {};

Vout::Vout() : loggingThread(), threadRunning(false), lMutex(), messages()
{
    std::cout << "[ logclass      ] starting: starting thread..." << std::endl;
    loggingThread = std::thread(&Vout::threadFunction, this);
    while (!threadRunning);
}

Vout::~Vout()
{
    threadRunning = false;
    loggingThread.join();
    std::cout << "[ logclass      ] stopping: logging finished successfully!";
    std::cout << std::endl;
}

void Vout::pushMessage(std::string messageStr,
    LoggingTypes::LoggingClientType type, int id)
{
    // thread-safe add message to queue
    staticInstance.lMutex.lock();
    staticInstance.messages.push(new LoggingMessage{messageStr, type, id});
    staticInstance.lMutex.unlock();
}

void Vout::threadFunction()
{
    threadRunning = true;

    std::cout << "[ logclass      ] loggingThread: started!" << std::endl;

    while (threadRunning || (messages.empty() == false)) {
        // thread-safe pop message from queue
        lMutex.lock();
        if (messages.empty()) {
            lMutex.unlock();
            continue;
        }

        LoggingMessage *loggingMessage = messages.front();
        messages.pop();
        lMutex.unlock();

        //print the header:
        if (loggingMessage->type == LoggingTypes::client) {
            std::cout << "[ client ";
        } else {
            std::cout << "[ server ";
        }
        std::cout << "|" << std::setw(5);
        std::cout << loggingMessage->id << " ] ";
        std::cout << loggingMessage->message << '\n';
    }
    std::cout << "[ logclass      ] loggingThread: stopped!" << std::endl;
    return;
}
