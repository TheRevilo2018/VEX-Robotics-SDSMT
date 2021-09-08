#ifndef _LOGGER
#define _LOGGER

#include "api.h"
#include <string>
#include <sstream>

class Logger
{
    std::string name;
    std::stringstream log;
    std::string saveLoc;

public:
    Logger(std::string name);
    ~Logger();

    void logString(std::string);

};



#endif
