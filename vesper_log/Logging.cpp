#include "Logging.h"

using namespace Vesper;

int Logging::nextID = 1;

//initialize the garbageCollector
Logging::garbageCollectorDataStruct Logging::garbageCollectorData =
{
    new std::mutex(),
    0,
    false
};

Logging::Logging()
{
    garbageCollectorData.threadRunning = true;
    garbageCollectorData.gStack = 0;

    uniqueID = 0;

    //start the thread:
    garbageCollectorThread = new std::thread(Logging::startGarbageCollector, this);
}

Logging::Logging(LoggingType::LoggingClientType typets)
{
    clientType = typets;
}

Logging::~Logging()
{

}

int Logging::getID()
{
    return uniqueID;
}

LoggingType::LoggingClientType Logging::getType()
{
    return clientType;
}

void Logging::logStart(char *text, ...)
{
}

void Logging::logDebug(char *text, ...)
{
}

void Logging::logNeutral(char *text, ...)
{
    char *logString;
    logString = new char[2048];

        

    std::thread **p;
    p = 0;
    std::thread  *t = new std::thread(Logging::printString, p, this, text);
    p = &t;
}

void Logging::logWarning(char *text, ...)
{
}

void Logging::logError(char *text, ...)
{
}

void Logging::startGarbageCollector(Logging *toStart)
{
    toStart->garbageCollector();
}

void Logging::garbageCollector()
{
    logNeutral("Garbage Collector for Logging started!");
    while (garbageCollectorData.threadRunning)
    {
        //we are now collecting garbage, so please don't disturb us!
        garbageCollectorData.locker->lock();

        while (garbageCollectorData.gStack)
        {//pop the threads from stack
            LoggingType::garbageStackItem *structToDelete = garbageCollectorData.gStack;
            delete(structToDelete->toDelete);
            garbageCollectorData.gStack = structToDelete->next;
            delete(structToDelete);
        }

        //unlock the Struct:
        garbageCollectorData.locker->unlock();
        sleep(1); // don't take too much CPU!
    }
}

void Logging::stopGarbageCollector()
{
    garbageCollectorData.threadRunning = false;
}

void Logging::printString(std::thread **source, Logging *who, char *toPrint)
{

    if (who->getType() == LoggingType::client)
    {
        std::cout << "client|";
    }
    else
    {
        std::cout << "server|";
    }

    std::cout << who->getID() << ":";
    std::cout << toPrint << std::endl;

    while (!source){} //wait for the source to be 0
    deleteThread(*source); //delete this thread
}

void Logging::deleteThread(std::thread *toDelete)
{
    //we are now deleting a thread so please don't disturb us!
    garbageCollectorData.locker->lock();

    LoggingType::garbageStackItem *oldTop;
    oldTop = garbageCollectorData.gStack;

    //create our new Item:
    garbageCollectorData.gStack = new LoggingType::garbageStackItem
                                      {
                                      toDelete,
                                      oldTop
                                      };

    //unlock the Struct:
    garbageCollectorData.locker->unlock();
}

