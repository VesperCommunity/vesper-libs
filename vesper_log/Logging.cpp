#include "Logging.hpp"

using namespace Vesper;

int Logging::nextID = 1;

Logging::Logging() :
    out(this)
{
    uniqueID = 0;
}

Logging::Logging(LoggingType::LoggingClientType typets) :
    out(this)
{
    clientType = typets;

    uniqueID = nextID;
    nextID++;
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

void Logging::flush()
{
    out.flush();
}
