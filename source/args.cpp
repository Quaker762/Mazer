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
#include "gtree.hpp"
#include "prims.hpp"
#include "recback.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <memory>
#include <chrono>

bool usePrims = false; // HAHAHAHAHAHAHAHA

/**
 *  Returns non-zero if value is a valid number/hex number
 */
static bool IsNumber(const std::string& arg)
{
    return !arg.empty() && std::find_if(arg.begin(), arg.end(), [](char c){return !std::isxdigit(c); }) == arg.end();
}

Mazer::CArgs::CArgs(int _argc, char** argv) : argc(_argc), args(), binPath(""), svgPath(""), ops(false),
width(0), height(0), 
seed(0), genNoArgs(false)
{
    auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    seed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    args.reserve(argc); // Reserve 'argc' number of strings in our vector
    args.assign(argv, argv + argc); // Copy all of the data from argv into a more friendly string vector
    ops.resize(4);
}

void Mazer::CArgs::Parse()
{
    using namespace Mazer;

    if(argc <= 1)
    {
        std::cout << "Mazer! By Jesse Buhagiar and Timothy Davis" << std::endl << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << " mazer --g [seed] [width height] --sb [path] --sv [path] --lb [path]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "--gr\t\tGenerate maze using the Recursive Backtracking Algorithm" << std::endl;
        std::cout << "--gp\t\tGenerate maze using Prim's Algorithm" << std::endl;
        std::cout << "--sb\t\tSave generated maze to .maze binary file" << std::endl;
        std::cout << "--sv\t\tSave generated maze to a .svg file" << std::endl;
        std::cout << "--lb\t\tLoad pre-generated binary file from disk" << std::endl;
        std::exit(0);
    }

    // Walk the arguments list
    for(std::size_t i = 0; i < args.size(); i++)
    {
        std::string arg = args.at(i); // Get current argument
        
        if(arg == AGEN_PRIM || arg == AGEN_RECB)
        {
            ops.at(Operations::GENERATE) = true;
            
            // ewww
            if(arg.c_str()[3] == 'p')
                usePrims = true;

            if(args.size() <= 4)
            {
                std::cout << "You can't just generate without doing anything!" << std::endl;
                std::exit(-1);
            }
            else
            {
                if(!IsNumber(args.at(i+1)) && !IsNumber(args.at(i+2)) && !IsNumber(args.at(i+3)))
                {
                    genNoArgs = true;
                }

                if(!IsNumber(args.at(i+3))) // User didn't pass seed to program
                {
                    width = std::stoi(args.at(i+1));
                    height = std::stoi(args.at(i+2));
                }
                else
                {
                    seed = std::stol(args.at(i+1), nullptr, 16);
                    width = std::stol(args.at(i+2));
                    height = std::stol(args.at(i+3));
                }
            }
        }
        else if(arg == ALOAD_BIN)
        {
            ops.at(Operations::LOAD_BIN) = true;
            binPath = args.at(i+1);
            continue;
        }
        else if(arg == ASAVE_BIN)
        {
            if(ops.at(Operations::GENERATE) != true)
            {
                Log(LogLevel::FATAL, "Error: You didn't specify maze generation first!\n");
                std::exit(-1);
            }

            ops.at(Operations::SAVE_BIN) = true;
            binPath = args.at(i+1);
        }
        else if(arg == ASAVE_SVG)
        {
            ops.at(Operations::SAVE_SVG) = true;
            svgPath = args.at(i+1);
        }
    }

    // Do some checks to make sure the user hasn't done anything stupid!
    if(ops.at(Operations::LOAD_BIN) == true && ops.at(Operations::SAVE_BIN) == true)
    {
        Log(LogLevel::FATAL, "You can't save and load a binary at the same time!!!\n");
        std::exit(-1);
    }

    if(ops.at(Operations::LOAD_BIN) == true && ops.at(Operations::SAVE_SVG) == false)
    {
        Log(LogLevel::FATAL, "You can't load a binary file without saving it!!\n");
        std::exit(-1);
    }

    if(ops.at(Operations::GENERATE) == true && ops.at(Operations::LOAD_BIN) == true)
    {
        Log(LogLevel::FATAL, "You can't generate and load a maze at the same time!!!\n");
        std::exit(-1);
    }

    Dispatch();
}


//TODO: Refactor me to accept Prims Generation and Recursive Generation!
void Mazer::CArgs::Dispatch() const
{
    using namespace Mazer;

    // Nice hack to use different constructors ;)
    std::unique_ptr<CGrowingTree> genmaze;
    std::unique_ptr<CMaze> maze;

    if(ops.at(Operations::GENERATE))
    {
        std::cout << "Generating Maze..." << std::endl;
        std::flush(std::cout);
        if(seed == 0)
        {
            Mazer::Log(LogLevel::WARNING, "No seed provided! Using default: 0x%x\n", seed);
        }

        if(usePrims)
        {
            genmaze = std::make_unique<CPrimsGenerator>(width, height, seed);
        }
        else
        {
            genmaze = std::make_unique<CRecursiveGenerator>(width, height, seed);
        }
        
        // Time the generation
        auto t1 = std::chrono::high_resolution_clock::now();
        genmaze.get()->GenerateMaze();
        auto t2 = std::chrono::high_resolution_clock::now();

        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        Log(LogLevel::INFO, "Done! Generation time = %dms\n", dt);

        if(ops.at(Operations::SAVE_BIN))
        {
            Log(LogLevel::INFO, "Writing maze to disk...\n");
            std::flush(std::cout);
            genmaze.get()->GetMaze().WriteBinary(binPath);
            Log(LogLevel::INFO, "Done!\n");
        }

        if(ops.at(Operations::SAVE_SVG))
        {
            Log(Mazer::LogLevel::INFO, "Writing svg to disk...\n");
            genmaze.get()->GetMaze().WriteSVG(svgPath);

            if(genmaze.get()->GetMaze().GetStatus() != CMaze::LoadStatus::SUCCESS)
            {
                std::string err = maze.get()->GetError();
                Log(LogLevel::FATAL, "Unable to write SVG! Reason: %s\n", err.c_str());
                std::exit(-1);
            }
            else
            {
                Log(LogLevel::INFO, "Done!\n");
            }
        }
    }

    if(ops.at(Operations::LOAD_BIN))
    {
        Log(LogLevel::INFO, "Loading maze from disk...\n");
        maze = std::make_unique<CMaze>(binPath);
        if(maze.get()->GetStatus() != CMaze::LoadStatus::SUCCESS)
        {
            std::string err = maze.get()->GetError();
            Log(LogLevel::FATAL, "Unable to read binary file! Reason: %s\n", err.c_str());
            std::exit(-1);
        }
        else
        {
            Log(LogLevel::INFO, "Done!\n");
        }

        if(ops.at(Operations::SAVE_SVG))
        {
            Log(LogLevel::INFO, "Writing svg to disk...\n");
            maze.get()->WriteSVG(svgPath);
            if(maze.get()->GetStatus() != CMaze::LoadStatus::SUCCESS)
            {
                std::string err = maze.get()->GetError();
                Log(LogLevel::FATAL, "Unable to write SVG! Reason: %s\n", err.c_str());
                std::exit(-1);
            }
            else
            {
                Log(LogLevel::INFO, "Done!\n");
            }
        }
    }
}
