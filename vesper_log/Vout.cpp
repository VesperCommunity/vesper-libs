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

using namespace Vesper;

Vout::Vout(Logging *parentts)
{
    if (!threadRunning) {
        std::cout << "[logclass] warning: creating object from Vout class "
            "while thread isn't running" << std::endl;
    }

    parent = parentts;
}

Vout::~Vout()
{
    std::cout << "[logclass] note: cleaning up ..." << std::endl;
    std::cout << "                 done!" << std::endl;
}

int Vout::init()
{
    if (threadRunning)
        return 1;

    std::cout << "[logclass] starting: starting thread" << std::endl;

    pipeThread = new std::thread(Vout::pipeFunction);
    pipeThread->detach(); //execute the thread independently

    std::cout << "[logclass] starting: done!" << std::endl;

    //while (!threadRunning);

    lMutex.unlock(); //unlock to start!

    return 0;
}

void Vout::operator<<(LoggingTypes::LoggingFlags flag)
{
    switch (flag) {
        case LoggingTypes::eom:
            flush();
          break;

        case LoggingTypes::endl:
            flush();
          break;

        default:
            //unknown flag
          break;
    }
}

void Vout::flush()
{
    // copy and clear current message string
    std::string messageStr = message.str();
    message.str(std::string());

    // thread-safe add message to queue
    lMutex.lock();
    messages.push(new LoggingTypes::LoggingMessage{parent, messageStr});
    lMutex.unlock();
}

std::mutex Vout::lMutex;
std::queue<LoggingTypes::LoggingMessage*> Vout::messages;

bool Vout::threadRunning = false; //does not work ;-(
std::thread *Vout::pipeThread = 0;

void Vout::pipeFunction()
{
    threadRunning = true;

    std::cout << "[logclass] pipeThread: started!" << std::endl;

    while (threadRunning || (messages.empty() == false)) {
        // thread-safe pop message from queue
        lMutex.lock();
        if (messages.empty()) {
            lMutex.unlock();
            continue;
        }

        LoggingTypes::LoggingMessage *loggingMessage = messages.front();
        messages.pop();
        lMutex.unlock();

        //print the header:
        std::cout << std::setw(8);
        switch (loggingMessage->src->getType()) {
            case LoggingTypes::client:
                std::cout << "[client ";
              break;
            case LoggingTypes::server:
                std::cout << "[server ";
              break;
            default:
                std::cout << "[###### ";
              break;
        }
        std::cout << "|" << std::setw(5);
        std::cout << loggingMessage->src->getID() << "] ";
        std::cout << loggingMessage->message << std::endl;
    }
    std::cout << "[logclass] pipeThread: stopped!" << std::endl;
    return;
}
