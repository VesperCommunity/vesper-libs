#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include "Vout.hpp"

#include <iostream>
#include <sstream>

#include "LoggingType.hpp"

namespace Vesper {

class Logging {
    public:

        /**
         * Invoke the default constructor only once
         * It will initialize the garbageCollector
         * in general and start the thread
         */
        Logging();
        Logging(LoggingType::LoggingClientType typets);
        ~Logging();

        int getID();
        LoggingType::LoggingClientType getType();

        void operator<<(int  toWrite);
        void operator<<(bool toWrite);
        void operator<<(char toWrite);
        void operator<<(char toWrite[]);
        void operator<<(std::string toWrite);
        void operator<<(void *toWrite); //write mem Adress
        void operator<<(LoggingType::LoggingFlags flag);
        void flush();

        /**
         * C-Style logging functions
         * will be added later
         * --> away-commented
         */
        /*void log(LoggingType::LoggingLevel level);
        void logStart(char *text, ...);
        void logDebug(char *text, ...);
        void logNeutral(char *text, ...);
        void logWarning(char *text, ...);
        void logError(char *text, ...);*/

    protected:
    private:

        Vout out;

        LoggingType::LoggingClientType clientType;

        /**
         * The unique identification that will be
         * given to the next client
         */
        static int nextID;

        /**
         * The unique identification
         * the uID 0 is the garbageCollector class
         * itself
         */
        int uniqueID;

        /**
         * This function print a c-style escape sequence
         * *data is a pointer to the data given by va_args
         * *toPrint is the Begine of the Escape Sequence ('%')
         * It returns 0 if success!
         */
        /*char *getCharFromEscSequence(char *toPrint, void *data);*/

};

}; /* namespace Vesper */

#endif /* LOGGING_H_INCLUDED */
