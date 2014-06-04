#include "Vout.hpp"

#include "Logging.hpp"

#include <iomanip>

using namespace Vesper;

Vout::Vout(Logging *parentts) {
    if (!threadRunning)
        std::cout << "[logclass] warning: creating object from Vout class while "
                     "thread isn't running" << std::endl;

    parent = parentts;
}

Vout::~Vout() {
    std::cout << "[logclass] note: cleaning up ..." << std::endl;

    LoggingType::ScanDataType type;
    void *dataToDelete;
    while (!this->popM(&type, &dataToDelete)) {
        switch (type) {
            case LoggingType::t_int:
                delete (int*) dataToDelete;
                break;
            case LoggingType::t_bool:
                delete (bool*) dataToDelete;
                break;
            case LoggingType::t_char:
                delete (char*) dataToDelete;
                break;
            case LoggingType::t_cstr:
                delete (char**) dataToDelete;
                break;
            case LoggingType::t_stdstr:
                delete (std::string*) dataToDelete;
                break;
            case LoggingType::t_void:
                delete (void*) dataToDelete; //idk if this is right
                break;
            case LoggingType::t_flag:
                delete (LoggingType::LoggingFlags*) dataToDelete;
                break;
            default:
                //this will be a mem leak
                break;
        }
    }
    std::cout << "                 done!" << std::endl;
}

int Vout::init() {
    if (threadRunning)
        return 1;

    pipeThread = new std::thread(Vout::pipeFunction);

    return 0;
}

void Vout::operator<<(int toWrite) {

    int *temp = new int;
    *temp = toWrite;

    pushM(LoggingType::t_int, (void*) temp);
}

void Vout::operator<<(bool toWrite) {

    bool *temp = new bool;
    *temp = toWrite;

    pushM(LoggingType::t_bool, (void*) temp);
}

void Vout::operator<<(char toWrite) {

    char *temp = new char;
    *temp = toWrite;

    pushM(LoggingType::t_char, (void*) temp);
}

void Vout::operator<<(char toWrite[]) {

    char **temp = new char*;
    *temp = toWrite;

    pushM(LoggingType::t_cstr, (void*) temp);
}

void Vout::operator<<(std::string  toWrite) {

    std::string *temp = new std::string;
    *temp = toWrite;

    pushM(LoggingType::t_stdstr, (void*) temp);
}

void Vout::operator<<(void *toWrite) {

    void **temp = new void*;
    *temp = toWrite;

    pushM(LoggingType::t_void, (void*) temp);
}

void Vout::operator<<(LoggingType::LoggingFlags flag) {
    switch (flag){
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

void Vout::flush() {

    this->mMutex.lock();

    ///now we have to attach 'this' to our lFIFO, which is printed by the thread

    bool stackIsEmpty = false;

    LoggingType::LoggingPipe *tempPipe = new LoggingType::LoggingPipe;
    tempPipe->messageSource = this->mFIFOfirst;
    tempPipe->src = this->parent;

    mFIFOfirst = 0;
    mFIFOlast = 0;

    this->mMutex.unlock();

    this->lMutex.lock();
    if (!lFIFOlast) { //nothing in the FIFO
        tempPipe->newer = 0;
        tempPipe->older = 0;

        lFIFOfirst = tempPipe;
        lFIFOlast = tempPipe;
        lMutex.unlock();

        return;
    }
    else {
        tempPipe->newer = 0;
        tempPipe->older = lFIFOlast;

        lFIFOlast = tempPipe;
        lMutex.unlock();

        return;
    }

}

int Vout::popM(LoggingType::ScanDataType *typetg, void **datatg){
    if (!mFIFOfirst)
        return 1;

    LoggingType::MessagePipe *tempPipe;

    mMutex.lock();

        tempPipe = mFIFOlast;
        mFIFOlast = tempPipe->newer;

    mMutex.unlock();

    *typetg = tempPipe->type;
    *datatg = tempPipe->data;

    delete tempPipe;

    return 0;
}

void Vout::pushM(LoggingType::ScanDataType typets, void *datats) {

    LoggingType::MessagePipe *tempMsg = new LoggingType::MessagePipe;

    tempMsg->data = datats;
    tempMsg->type = typets;

    mMutex.lock();

    if (!mFIFOfirst) {
        mFIFOfirst = tempMsg;
        mFIFOlast = tempMsg;

        mMutex.unlock();

        return;
    }
    else {
        tempMsg->older = mFIFOlast;
        mFIFOlast = tempMsg;

        mMutex.unlock();

        return;
    }

}

std::mutex                Vout::lMutex;
LoggingType::LoggingPipe  Vout::*lFIFOfirst = 0;
LoggingType::LoggingPipe  Vout::*lFIFOlast  = 0;

bool         Vout::threadRunning = false; //does not work ;-(
std::thread  Vout::*pipeThread   = 0;

void Vout::pipeFunction() {
    threadRunning = true;
    while (threadRunning) {

        lMutex.lock();

        while(lFIFOfirst) {

            LoggingType::LoggingPipe *lPipeToDelete;

            LoggingType::MessagePipe *messageToDelete;
            LoggingType::MessagePipe *nextMessage = new LoggingType::MessagePipe;
            nextMessage = lFIFOfirst->messageSource;

            //print the header:
            std::cout << std::setw(8);
            switch (nextMessage->type) {
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

            //we start with the output and delete / pop the lstack later
            while (nextMessage) {
                switch(nextMessage->type){
                    case LoggingType::t_int:
                        std::cout << *((int*) nextMessage->data);
                        delete (int*) nextMessage->data;
                        break;
                    case LoggingType::t_bool:
                        std::cout << *((bool*) nextMessage->data);
                        delete (int*) nextMessage->data;
                        break;
                    case LoggingType::t_char:
                        std::cout << *((char*) nextMessage->data);
                        break;
                    case LoggingType::t_cstr:
                        std::cout << *((char**) nextMessage->data);
                        break;
                    case LoggingType::t_stdstr:
                        std::cout << *((std::string*) nextMessage->data);
                        break;
                    case LoggingType::t_void:
                        std::cout << *((void**) nextMessage->data);
                        break;
                    case LoggingType::t_flag:
                        //We got a flag!

                        LoggingType::LoggingFlags tempFlag;
                        tempFlag = *((LoggingType::LoggingFlags*)nextMessage->data);

                        switch(tempFlag) {
                            case LoggingType::endl:
                                std::cout << std::endl;
                                break;
                            default:
                                ///TODO: add exception or similiar
                                break;
                        }

                        break;
                    default:
                        //not recognized ... maybe throw an error
                        break;
                }

                messageToDelete = nextMessage;
                nextMessage = nextMessage->newer;

                delete messageToDelete;
            }

            lPipeToDelete = lFIFOfirst;
            lFIFOfirst = lFIFOfirst->newer;

            delete lPipeToDelete;
        }

        lMutex.unlock();
    }
    std::cout << "[logclass] note: thread stopped!" << std::endl;

    return;
}
