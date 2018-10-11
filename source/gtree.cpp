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
#include "gtree.hpp"
#include "log.hpp"

#include <iostream>
#include <algorithm>

Mazer::CGrowingTree::CGrowingTree(const int& width, const int& height, const std::uint32_t& seed)
    : maze(width, height, seed), cellList(0), rng(seed) 
{
    Mazer::Log(Mazer::LogLevel::INFO, "Constructing base class CGrowingTree!\n");    
    Mazer::Log(Mazer::LogLevel::INFO, "Maze Size: [%d, %d]\n", width, height);
    Mazer::Log(Mazer::LogLevel::INFO, "Maze seed: 0x%x\n", seed);
}

/**
 *  Okay, so here's a quick rundown on how this actually works...:
 *
 *  1. cellList is a list of cells that's empty. We add one cell to this in the beginning at random
 *  2. We choose a cell from the list, cellList, and we carve a passage to that cell (all the while adding
 *  edges to our edgelist[???]). If there are no unvisited neighbours, that cell gets removed from cellList.
 *  3. We repeat this until cellList is empty.
 */
void Mazer::CGrowingTree::GenerateMaze()
{
    cell c;
    std::uniform_int_distribution<int> xrange(0, maze.GetWidth());
    std::uniform_int_distribution<int> yrange(0, maze.GetHeight());
    std::vector<cell> directions;
    // Yikes...
    directions.push_back(maze.dirVals[0]);
    directions.push_back(maze.dirVals[1]);
    directions.push_back(maze.dirVals[2]);
    directions.push_back(maze.dirVals[3]);

    Mazer::Log(Mazer::LogLevel::INFO, "Generating Maze...\n");

    // Pick a random x,y value for the first cell!
    c.x = xrange(rng);
    c.y = yrange(rng);
    Mazer::Log(Mazer::LogLevel::INFO, "First random cell at (%d, %d)\n", c.x, c.y);

    cellList.push_back(c); // Add a random cell to the cell List..

    // Keep going until we're outta cells!
    
    while(!cellList.empty())
    {
        int     cellIndex = GetNextCellIndex();
        cell    c = cellList.at(cellIndex);

        // Now get all of the cells neighbours
        std::vector<cell> neighbours = maze.GetNeighbours(c); // Hehe, I knew this function would come in handy!

        // Try out each direction
        for(int i = 0; i < 4; i++)
        {
            cell newCell = c;
            std::shuffle(directions.begin(), directions.end(), rng);
            
            newCell.x += directions.at(0).x;
            newCell.y += directions.at(0).y;
            
            // This is an unvisited neighbour!
            if(newCell.x >= 0 && newCell.y >= 0 && newCell.x < maze.GetWidth() 
                && newCell.y < maze.GetHeight() 
                && !maze.IsCellVisited(newCell))
            {
                // Create an edge and add it to the edge list!
                maze.VisitCell(c);
                maze.VisitCell(newCell);

                edge e;
                e.c_A = c;
                e.c_B = newCell;

                // Add this cell to the cellList (???)
                cellList.push_back(newCell);
                cellIndex = 0;
            }

            if(cellIndex == 0)
                break;
        }
        
        // If we haven't found a valid cell, remove it from cellList and try again!
        if(cellIndex != 0)
            cellList.erase(cellList.begin() + cellIndex);
    }
}


