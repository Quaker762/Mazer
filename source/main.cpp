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
	CArgs CArgs(argc, argv);

	//CMaze maze(256, 256);

	//maze.GenerateMaze(std::time(nullptr));

    return 0;
}

CArgs::CArgs(int argc, char** argv)
{

	for(int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	if(args[1] == LOAD_BIN)
	{
		CMaze maze(args[2]); //loads maze from filename

		if(args[3] == SAVE_BIN)
		{
			//save bin here
		}
		
		else if(args[3] == SAVE_SVG)
		{
			maze.WriteSVG(args[4]);
		}
	}

	if(args[1] == GEN_SEED)
	{
		CMaze maze;

		std::uint32_t seed;

		int iSeed = std::stoi(args[2], &seed);

		maze.GenerateMaze(static_cast<std::uint32_t>(iSeed)); //generate maze from seed

		if(args[3] == SAVE_BIN)
		{
			//save bin here

			if(args[5] == SAVE_SVG)
			{
				maze.WriteSVG(args[6]);
			}
		}

		else if(args[3] == SAVE_SVG)
		{
			maze.WriteSVG(args[4]);
		}

		else
		{
			std::size_t width;
			std::size_t height;

			int iWidth = std::stoi(args[3], &width);
			int iHeight = std::stoi(args[4], &height);

			CMaze maze(iWidth, iHeight);
		}

	}
	else
	{
		std::cout << ARGV_FAIL << std::endl;
	}

}


