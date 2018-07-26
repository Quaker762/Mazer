/**
 *  Implementation of log.hpp
 */
#include "log.hpp"

#include <string>
#include <fstream>
#include <cstdarg>
#include <cstdio>

static constexpr bool LOG_FILE = false; // Should all of this be logged to a log.txt??

void Log(LogLevel logType, const std::string& str, ...)
{
    std::string     msg;
    std::va_list    args;

    switch(logType)
    {
    case LogLevel::INFO:
        msg += "[INFO] ";
        break;
    case LogLevel::WARNING:
        msg += "[WARN] ";
        break;
    case LogLevel::ERROR:
        msg += "[ERROR] ";
        break;
    case LogLevel::FATAL:
        msg += "[FATAL] ";
        break;
    case LogLevel::DEBUG:
        msg += "[DEBUG] ";
        break;
    default:
    case LogLevel::NONE:
        break;
    }

    std::string tmp;
    tmp.resize(512); // Allocate 512-bytes for storing the message

    va_start(args, str);
    vsprintf(const_cast<char*>(tmp.c_str()), str.c_str(), args);
    msg += tmp;

    std::fprintf(stderr, msg.c_str()); // Don't buffer this, print it straight to the console.
    if(LOG_FILE)
    {
        std::ofstream logFile;
        logFile.open("log.txt", std::ofstream::out | std::ofstream::app);

        logFile << msg;
        logFile.close();
    } 
}
