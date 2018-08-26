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
	CArgs args(argc, argv);
    args.Parse();

	return 0;
}



