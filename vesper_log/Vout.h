#ifndef VOUT_H_INCLUDED
#define VOUT_H_INCLUDED

#include <thread>
#include <mutex>

#include <iostream>
#include <sstream>
#include <string>

#include "LoggingType.h"

namespace Vesper {

class Vout {

    public:

        Vout();
        ~Vout();

        static int init();

        void operator<<(int  toWrite);
        void operator<<(bool toWrite);
        void operator<<(char toWrite);
        void operator<<(char toWrite[]);
        void operator<<(std::string toWrite);
        void operator<<(void *toWrite); //write mem Adress
        void operator<<(LoggingType::LoggingFlags flag);
        void flush();

        ///pop() used by thread to get at FIFOfirst
        ///pop() returns 1 if pipe is empty
        int pop(LoggingType::ScanDataType *typetg, void *datatg);
        std::mutex mPopMutex;
        LoggingType::MessagePipe *mFIFOfirst;

    private:

        ///push() used by operators to add at FIFOlast
        void push(LoggingType::ScanDataType typets, void *datats);
        std::mutex mPushMutex;
        LoggingType::MessagePipe *mFIFOlast;

        /**
         * When a LoggingPipe reaches LogginType::eom the message is complete
         * and will be pushed to lFIFO (logging FIFO)
         * lFIFO will be written by the pipiFunction.
         */

        static LoggingType::LoggingPipe *lFIFOfirst;
        static std::mutex lMutexFirst;

        static LoggingType::LoggingPipe *lFIFOlast;
        static std::mutex lMutexLast;

        static bool threadRunning; // = false; //does not work ;-(
        static std::thread *pipeThread; // = 0; //iso undso

        static void pipeFunction();

}; /* class Vout */

}; /* namespace Vesper */


#endif /* VOUT_H_INCLUDED */
