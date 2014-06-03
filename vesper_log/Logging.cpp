#include "Logging.h"

//we need this for variable argument lists
//C-Style, I don't wanna mess with template and/or vector classes ;-)
#include <cstdarg>

using namespace Vesper;

int Logging::nextID = 1;

Logging::Logging() {

    uniqueID = 0;
}

Logging::Logging(LoggingType::LoggingClientType typets) {
    clientType = typets;
}

Logging::~Logging() {

}

int Logging::getID() {
    return uniqueID;
}

LoggingType::LoggingClientType Logging::getType() {
    return clientType;
}

void Logging::logStart(char *text, ...) {
}

void Logging::logDebug(char *text, ...) {
}

void Logging::logNeutral(char *text, ...) {
    std::stringstream *logString = new std::stringstream;

    va_list args;

    va_start(args, *text);

    char *buffer;
    char *tempP;

    int textPos=0;

    do {

        for (; text[textPos] != '%'; textPos++)
            *logString << text[textPos];

        tempP = &text[textPos];

        //Now we got an escape sequence at text[textPos]!
        //buffer = getCharFromEscSequence(tempP, (void*) &va_arg(args, int));
        //adjust int to depend on %* commands in the string
        *logString << buffer;

        delete(buffer);

        textPos += 2; //increase pointer with length of escape sequence
    }while(true);
    va_end(args);

    std::thread **p;
    p = 0;
    std::thread  *t = new std::thread(Logging::printString, p, this, logString);
    p = &t;
}

void Logging::logWarning(char *text, ...) {
}

void Logging::logError(char *text, ...) {
}

void Logging::printString(std::thread **source, Logging *who, std::stringstream *toPrint) {

}

char *Logging::getCharFromEscSequence(char *toPrint, void *data) {
    char retString;

    //

}
