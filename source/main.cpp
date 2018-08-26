#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <stdexcept>
#include "maze.hpp"
#include "args.hpp"

using namespace Mazer;

int main(int argc, char** argv)
{
	//CArgs CArgs(argc, argv);

	CMaze maze(32, 32);

	maze.GenerateMaze();

	maze.WriteSVG("maze.svg");

	return 0;
}



