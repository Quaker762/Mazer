/**
 *  Copyright (c) 2018 Jesse Buhagiar
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 **/
#include "log.hpp"

#include <string>
#include <fstream>
#include <cstdarg>
#include <cstdio>

static constexpr bool LOG_FILE = false; // Should all of this be logged to a log.txt??

void Mazer::Log(LogLevel logType, const std::string& str, ...)
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
