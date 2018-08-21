#include <iostream>
#include <ctime>
#include "maze.hpp"

int main(int argc, char** argv)
{
    Mazer::CMaze maze(256, 256);
    
    
    maze.GenerateMaze(std::time(nullptr));

    return 0;
}
