#ifndef VOUT_H_INCLUDED
#define VOUT_H_INCLUDED

#include <thread>

#include <iostream>
#include <sstream>

#include "LoggingType.h"

namespace Vesper {

class Vout {

    public:

        Vout();
        ~Vout();

        static int init();

    private:

        static bool thread_running = false;
        static std::thread


}; /* class Vout */

}; /* namespace Vesper */


#endif /* VOUT_H_INCLUDED */
