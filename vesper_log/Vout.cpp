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
    std::cout << "[logclass    ] starting: starting thread..." << std::endl;
    loggingThread = std::thread(&Vout::threadFunction, this);
    while (!threadRunning);
}

Vout::~Vout()
{
    threadRunning = false;
    staticInstance.condVariable.notify_one();
    loggingThread.join();
    std::cout << "[logclass    ] stopping: logging finished successfully!";
    std::cout << std::endl;
}

void Vout::pushMessage(std::string messageStr,
    LoggingTypes::LoggingClientType type, int id)
{
    // thread-safe add message to queue
    std::unique_lock<std::mutex> lock(staticInstance.lMutex);
    staticInstance.messages.push(new LoggingMessage{messageStr, type, id});
    lock.unlock();
    staticInstance.condVariable.notify_one();
}

void Vout::threadFunction()
{
    threadRunning = true;

    std::cout << "[logclass    ] loggingThread: started!" << std::endl;

    while (threadRunning || (messages.empty() == false)) {
        // thread-safe pop message from queue
        std::unique_lock<std::mutex> lock(lMutex);
        // while loop only necessary in case of spurious wakeups
        while (threadRunning && messages.empty()) {
            // waiting for messages
            condVariable.wait(lock);
        }
        if (!threadRunning && messages.empty()) {
            break;
        }

        LoggingMessage *loggingMessage = messages.front();
        messages.pop();
        lock.unlock();

        // generate the prefix:
        std::ostringstream prefix;
        if (loggingMessage->type == LoggingTypes::client) {
            prefix << "[client";
        } else {
            prefix << "[server";
        }
        prefix << "|" << std::setw(5);
        prefix << loggingMessage->id << "] ";
        std::string prefixStr = prefix.str();

        std::string message = loggingMessage->message;

        // print message and add prefix to newlines:
        std::string::size_type pos, pos2 = -1;
        do {
            pos = pos2 + 1;
            pos2 = message.find('\n', pos);
            std::cout << prefixStr;
            if (pos2 == std::string::npos)
                std::cout << message.substr(pos);
            else
                std::cout << message.substr(pos, pos2-pos);
            std::cout << '\n';
        } while (pos2 != std::string::npos);
    }
    std::cout << "[logclass    ] loggingThread: stopped!" << std::endl;
    return;
}
