/**
 *  Logging function for debug
 */
#ifndef _LOG_HPP_INCLUDED
#define _LOG_HPP_INCLUDED

#include <string>

namespace Mazer{

/**
 *  Log message severuty
 */
enum class LogLevel
{
    INFO,
    WARNING,
    ERROR,
    FATAL,
    DEBUG,
    NONE
};

/**
 *  Log a string to the terminal (to alert the user, give debug information etc)
 */
void Log(LogLevel logType, const std::string& str, ...);

}


#endif
