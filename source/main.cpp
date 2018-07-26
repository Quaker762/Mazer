#include <iostream>
#include "log.hpp"

int main(int argc, char** argv)
{
    std::cout << "Hello, World!\n" << std::endl;

    Log(LogLevel::INFO, "Hello, World %d %d!\n", 5, 10);
    return 0;
}
