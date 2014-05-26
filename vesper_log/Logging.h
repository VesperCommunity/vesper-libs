#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include "Vout.h"

#include <iostream>
#include <sstream>
#include <thread>

namespace Vesper {

/**
 * The namespace LoggingTypes will contain enums, structs
 * and other things, that are needed by the Logging class
 * We use a namespace to avoid Name-conflicts
 * --> for example use this: LoggingType.client
 * --> avoid using the LoggingType namespace
 */
namespace LoggingType {

enum LoggingClientType {
    client, // the logging client is a client
    server  // the logging client is a server
};

enum ScanDataType {
    error,   //an error occured
    unknown, //unknown escape sequence
    eos,     //*E*nd *O*f *S*tring
    t_int,   //integer
    t_bool,  //boolean
    t_char,  //character
    t_cstr,  //char[] array aka cstring
    t_stdstr,//std::string
    t_void   //void* pointer aka mem adress (--> hexadecimal)    
};

}; /* namespace LoggingType*/

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

        void logStart(char *text, ...);
        void logDebug(char *text, ...);
        void logNeutral(char *text, ...);
        void logWarning(char *text, ...);
        void logError(char *text, ...);

    protected:
    private:

        static void printString(std::thread **source, Logging *who, std::stringstream *toPrint);

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

        /* We may need this ...
        void print(char *data);
        void printLn(char *data);
        void printLnEnd();*/

        /**
         * This function print a c-style escape sequence
         * *data is a pointer to the data given by va_args
         * *toPrint is the Begine of the Escape Sequence ('%')
         * It returns 0 if success!
         */
        char *getCharFromEscSequence(char *toPrint, void *data);

};

}; /* namespace Vesper */

#endif /* LOGGING_H_INCLUDED */
