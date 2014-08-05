#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include "Vout.hpp"

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

        template <class T>
        Logging &operator<<(const T &toWrite)
        {
            out << toWrite;
            return *this;
        }

        void flush();

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

};

}; /* namespace Vesper */

#endif /* LOGGING_H_INCLUDED */
