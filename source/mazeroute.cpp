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
#include "mazeroute.hpp"
#include "log.hpp"
#include "cell.hpp"

#include <fstream>
#include <iostream>

Mazer::CMazeRouter::CMazeRouter(const Mazer::CMaze& _maze)
    : CSolvingAlgorithm(_maze), heap()
{
    Mazer::Log(Mazer::LogLevel::INFO, "Using Maze Routing Algorithm\n");

}

int ManhattanDistance(Mazer::cell c1, Mazer::cell c2)
{
    return std::abs(c1.x - c2.x) + std::abs(c1.y - c2.y);
}

void Mazer::CMazeRouter::SolveMaze(const std::string& fname)
{
    using namespace Mazer;

    cell src;       // Source node (which is [0,0])
    cell dst;       // Our destination (which is [width - 1, height - 1])
    cell cur;       // Our current node
    int  md_best;   // Stores the closest md we ever had to dst

    src.x = 0;
    src.y = 0;
    
    // Now, I could technically have 1
    cur.x = 1;
    cur.y = 1;
    cellList.push_back(src);

    dst.x = maze.GetWidth() - 1;
    dst.y = maze.GetHeight() - 1;
    
    
    std::ofstream f;
    f.open(fname, std::ios_base::ate | std::ios_base::app);

    /**
    for(int i = 0; i < cur.neighbours.size(); i ++)
    {
        f << "\t<line stroke='red' stroke-width='0.5' ";
        f << "x1 ='" << static_cast<double>(cur.x + 0.5);
        f << "' y1='" << static_cast<double>(cur.y + 0.5);
        f << "' x2='" << static_cast<double>(cur.neighbours.at(i).x + 0.5);
        f << "' y2='" << static_cast<double>(cur.neighbours.at(i).y + 0.5);
        f << "' />" << std::endl;
    }
    */

    f << "</svg>";
    f.close();
}
