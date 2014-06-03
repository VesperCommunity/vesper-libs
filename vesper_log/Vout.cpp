#include "Vout.h"

using namespace Vesper;

Vout::Vout() {
    if (!threadRunning)
        std::cout << "[logclass] warning: creating object from Vout class while "
                     "thread isn't running" << std::endl;
}

Vout::~Vout() {
    std::cout << "[logclass] note: cleaning up ..." << std::endl;

    LoggingType::ScanDataType type;
    void *dataToDelete;
    while (!this->pop(&type, dataToDelete)) {
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
                delete (void**) dataToDelete; //idk if this is right
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

    push(LoggingType::t_int, (void*) temp);
}

void Vout::operator<<(bool toWrite) {
}

void Vout::operator<<(char toWrite) {
}

void Vout::operator<<(char toWrite[]) {
}

void Vout::operator<<(std::string  toWrite) {
}

void Vout::operator<<(void *toWrite) {
}

void Vout::operator<<(LoggingType::LoggingFlags flag) {
}

//Vout::
