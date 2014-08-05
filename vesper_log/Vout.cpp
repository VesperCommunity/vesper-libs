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

void Vout::operator<<(LoggingType::LoggingFlags flag)
{
    switch (flag) {
        case LoggingType::eom:
            flush();
          break;

        case LoggingType::endl:
            flush();
          break;

        default:
            //unknown flag
          break;
    }
}

void Vout::flush()
{

    ///now we have to attach 'this' to our lFIFO, which is printed by the thread

    // copy and clear current message string
    std::string messageStr = message.str();
    message.str(std::string());

    LoggingType::LoggingPipe *tempPipe = new LoggingType::LoggingPipe;
    tempPipe->message = messageStr;
    tempPipe->src = this->parent;

    this->lMutex.lock();
    if (!lFIFOlast) { //nothing in the FIFO
        tempPipe->newer = 0;
        tempPipe->older = 0;

        lFIFOfirst = tempPipe;
        lFIFOlast = tempPipe;
        lMutex.unlock();

        return;
    } else {
        lFIFOlast->newer = tempPipe;
        lFIFOlast = tempPipe;

        tempPipe->newer = 0;

        lMutex.unlock();

        return;
    }

}

std::mutex Vout::lMutex;
LoggingType::LoggingPipe *Vout::lFIFOfirst=0;
LoggingType::LoggingPipe *Vout::lFIFOlast=0;

bool Vout::threadRunning = false; //does not work ;-(
std::thread  *Vout::pipeThread=0;

void Vout::pipeFunction()
{
    threadRunning = true;

    std::cout << "[logclass] pipeThread: started!" << std::endl;

    while (threadRunning) {

        lMutex.lock();

        while (lFIFOfirst) {

            LoggingType::LoggingPipe *lPipeToDelete;

            //print the header:
            std::cout << std::setw(8);
            switch (lFIFOfirst->src->getType()) {
                case LoggingType::client:
                    std::cout << "[client ";
                  break;
                case LoggingType::server:
                    std::cout << "[server ";
                  break;
                default:
                    std::cout << "[###### ";
                  break;
            }
            std::cout << "|" << std::setw(5);
            std::cout << lFIFOfirst->src->getID() << "] ";
            std::cout << lFIFOfirst->message << std::endl;

            lPipeToDelete = lFIFOfirst;
            lFIFOfirst = lFIFOfirst->newer;

            delete lPipeToDelete;
        }

        lFIFOlast = 0;

        lMutex.unlock();
    }
    std::cout << "[logclass] pipeThread: stopped!" << std::endl;
    return;
}
