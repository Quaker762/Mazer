#include <iostream>
#include "log.hpp"

int main(int argc, char** argv)
{
    std::cout << "Hello, World!\n" << std::endl;

    Log(LogLevel::INFO, "%d\n", sizeof(std::string));
    return 0;
}
