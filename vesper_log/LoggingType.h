#ifndef LOGGINGTYPE_H_INCLUDED
#define LOGGINGTYPE_H_INCLUDED

/**
 * The namespace LoggingTypes will contain enums, structs
 * and other things, that are needed by the Logging class
 * We use a namespace to avoid Name-conflicts
 * --> for example use this: LoggingType.client
 * --> avoid using the LoggingType namespace
 */
namespace LoggingType {

class Vout;

enum ScanDataType {
    error,   //an error occured
    unknown, //unknown escape sequence
    //eos,     //*E*nd *O*f *S*tring
    t_int,   //integer
    t_bool,  //boolean
    t_char,  //character
    t_cstr,  //char[] array aka cstring
    t_stdstr,//std::string
    t_void   //use this for pointer aka mem adress (--> hexadecimal)
};

enum LoggingFlags {
    eom //EndOfMessage
};

enum LoggingLevel {
    l_start,    //startup sequence
    l_debug,    //debug messages
    l_neutral,  //white
    l_warning,  //warnings
    l_error     //errors
};

enum LoggingClientType {
    client, // the logging client is a client
    server  // the logging client is a server
};

struct MessagePipe { //FIFO
    MessagePipe *older;
    MessagePipe *newer;

    ScanDataType type;
    void        *data;
};

struct LoggingPipe {
    LoggingPipe *older;
    LoggingPipe *newer;

    MessagePipe *messageSource;
};

}; /* namespace LoggingType*/

#endif /* LOGGINGTYPE_H_INCLUDED */
