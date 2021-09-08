#include "logger.h"

using namespace std;

Logger::Logger(string inputName)
{
    name = inputName;
    saveLoc = "/usd/" + name + "Log.txt";
}

Logger::~Logger()
{
    FILE* usd_file_write = fopen(saveLoc.c_str(), "w");

    fputs(log.str().c_str(), usd_file_write);

    fclose(usd_file_write);
}

void Logger::logString(string logVal)
{
    log << name << ":" << pros::millis() << ":   " <<  logVal << endl;
}
