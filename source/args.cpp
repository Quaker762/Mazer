/**
 *  Copyright (c) 2018 Jesse Buhagiar and Timothy Davis
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
#include "args.hpp"
#include "maze.hpp"
#include "log.hpp"

#include <algorithm>
#include <cstdint>
#include <cctype>
#include <iostream>

static Mazer::CMaze maze;

/**
 *  Returns non-zero if value is a valid number/hex number
 */
static bool IsNumber(const std::string& arg)
{
    return !arg.empty() && std::find_if(arg.begin(), arg.end(), [](char c){return !std::isxdigit(c); }) == arg.end();
}

Mazer::CArgs::CArgs(int _argc, char** argv) : argc(_argc), args(), ops(false) 
{
    args.reserve(argc); // Reserve 'argc' number of strings in our vector
    args.assign(argv, argv + argc); // Copy all of the data from argv into a more friendly string vector
    ops.resize(3);
}

// 
void Mazer::CArgs::Parse()
{
    // Walk the arguments list
    for(std::size_t i = 0; i < args.size(); i++)
    {
        std::string arg = args.at(i); // Get current argument
        
        if(arg == AGEN_SEED)
        {
            ops.at(Operations::GENERATE) = true;
            //if(IsNumber(args.at(i+1)))
                //maze.SetSeed(std::stoi(args.at(i+1)));
        }
    }
}

///// THIS SHOULD PROBABLY BE IN SOME FUNCTION, NOT THE CONSTRUCTOR!!! :^)
    /**
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

        std::size_t seed;

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
    **/
