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
#define _DEBUG_

#include "maze.hpp"
#include "log.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstdlib>

#undef _DEBUG_

static constexpr Mazer::cell INVALID_CELL = Mazer::cell{-1, -1};

static std::mt19937 rng;

Mazer::CMaze::CMaze(const int& _width, const int& _height, const std::uint32_t _seed) : width(_width), height(_height), seed(_seed), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    cells.resize(width * height);
    std::fill(cells.begin(), cells.end(), false);
    rng.seed(seed);
}

Mazer::CMaze::CMaze(const std::string& path) : width(0), height(0), seed(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    LoadBinary(path);
}

Mazer::CMaze::~CMaze()
{
}

void Mazer::CMaze::SetWidth(const int _width)
{
    width = _width;
}

void Mazer::CMaze::SetHeight(const int _height)
{
    height = _height;
}

void Mazer::CMaze::SetSeed(const int _seed)
{
    seed = _seed;
}

const int& Mazer::CMaze::GetHeight() const
{
    return height;
}

const int& Mazer::CMaze::GetWidth() const
{
    return width;
}

const std::uint32_t& Mazer::CMaze::GetSeed() const
{
    return seed;
}

int Mazer::CMaze::Pos2Offset(const int& x, const int& y) const
{
    return (y * width) + x;
}

int Mazer::CMaze::Pos2Offset(const Mazer::cell& c) const
{
	return (c.y * width) + c.x;
}

std::vector<Mazer::cell> Mazer::CMaze::GetNeighbours(const Mazer::cell& c) const
{
    std::vector<Mazer::cell> list;

    if(c.x > 0)
        list.push_back(Mazer::cell{c.x-1, c.y}); // Left neighbour
    if(c.x + 1 < width)
        list.push_back(Mazer::cell{c.x+1, c.y}); // Right neighbour
    if(c.y + 1 < height)
        list.push_back(Mazer::cell{c.x, c.y+1}); // Top neighbour
    if(c.y > 0)
        list.push_back(Mazer::cell{c.x, c.y-1}); // Bottom neighbour

    return list;
}

std::vector<Mazer::cell> Mazer::CMaze::GetNeighbours(const int& x, const int& y) const
{
    std::vector<Mazer::cell> list;

    if(x > 0)
        list.push_back(Mazer::cell{x-1, y}); // Left neighbour
    if(x + 1 < width)
        list.push_back(Mazer::cell{x+1, y}); // Right neighbour
    if(y + 1 < height)
        list.push_back(Mazer::cell{x, y+1}); // Top neighbour
    if(y > 0)
        list.push_back(Mazer::cell{x, y-1}); // Bottom neighbour

    return list;
}

void Mazer::CMaze::WriteBinary(const std::string& path)
{
    std::ofstream mapFile;

    mapFile.open(path, std::ios::binary | std::ios::out);
    if(!mapFile.is_open())
    {
        status = LoadStatus::IO_ERROR;
        return;
    }

    std::uint32_t sz = edges.size();
    mapFile.write(reinterpret_cast<char*>(&width), sizeof(std::uint32_t));
    mapFile.write(reinterpret_cast<char*>(&height), sizeof(std::uint32_t));
    mapFile.write(reinterpret_cast<char*>(&sz), sizeof(std::uint32_t));

    for(std::list<Mazer::edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        Mazer::edge e = *it;

        mapFile.write(reinterpret_cast<char*>(&e.c_A.x), sizeof(std::uint32_t));
        mapFile.write(reinterpret_cast<char*>(&e.c_A.y), sizeof(std::uint32_t));
        mapFile.write(reinterpret_cast<char*>(&e.c_B.x), sizeof(std::uint32_t));
        mapFile.write(reinterpret_cast<char*>(&e.c_B.y), sizeof(std::uint32_t));
    }
}

// TODO: Refactor me to be void and store LoadStatus inside the class!!!!
void Mazer::CMaze::LoadBinary(const std::string& path)
{
    std::ifstream mapFile;
    std::size_t edgeCount = 0;
    std::size_t i = 0;

    // Open a handle to the map file
    mapFile.open(path, std::ios::binary);
    if(!mapFile.is_open()) // There was an issue opening a handle to the file
    {
        status = LoadStatus::IO_ERROR;
        return;
    }

    // We can now actually read the binary file into our class
    mapFile.read(reinterpret_cast<char*>(&width), sizeof(std::uint32_t));            // Map width
    mapFile.read(reinterpret_cast<char*>(&height), sizeof(std::uint32_t));           // Map height
    mapFile.read(reinterpret_cast<char*>(&edgeCount), sizeof(std::uint32_t));        // Count of edges in map

    for(i = 0; i < edgeCount; i++)
    {
        Mazer::edge e;

        mapFile.read(reinterpret_cast<char*>(&e.c_A.x), sizeof(std::uint32_t));
        mapFile.read(reinterpret_cast<char*>(&e.c_A.y), sizeof(std::uint32_t));
        mapFile.read(reinterpret_cast<char*>(&e.c_B.x), sizeof(std::uint32_t));
        mapFile.read(reinterpret_cast<char*>(&e.c_B.y), sizeof(std::uint32_t));

        if(e.c_A.x < 0 || e.c_A.y < 0 || e.c_A.x > width || e.c_A.y > height)
        {
            Mazer::Log(Mazer::LogLevel::FATAL, "Dimension outside boundary!\n");
            std::cout << "\te.c_A.x: " << e.c_A.x << std::endl;
            std::cout << "\te.c_A.y: " << e.c_A.y << std::endl;
            std::cout << "\te.c_B.x: " << e.c_B.x << std::endl;
            std::cout << "\te.c_B.y: " << e.c_B.y << std::endl;
        }

        edges.push_back(e);
    }

    // We didn't read enough edges! This file is probably corrupt!
    if(i != edgeCount)
    {
        Mazer::Log(Mazer::LogLevel::FATAL, "edgesRead < edgeCount! Aborting...\n");
        status = LoadStatus::INVALID_MAZE;
        std::abort();
    }

    mapFile.close();

    status = LoadStatus::SUCCESS;
}

/**
Mazer::cell Mazer::CMaze::Walk(const int& x, const int& y)
{
    static int count = 0;

    Mazer::cell         c = Mazer::cell{x, y};
    std::vector<int>    dirs;
    //std::mt19937        rng;
    //////////////////////////////////////////////////////////
    
    // Fill dirs vector
    dirs.reserve(4);
    for(unsigned int i = 0; i < 4; i++)
    {
        dirs.push_back(i);
    }

    #ifdef _DEBUG_
    std::cout << "walking..." << std::endl;
    #endif
    if(x >= width || y >= height)
        std::cout << "What the fuck?!?!" << x << " " << y << std::endl;
    
    cells.at(Pos2Offset(x, y)) = true;
    do
    {
        int offset = 0;
        std::shuffle(dirs.begin(), dirs.end(), rng);
        int rd = dirs.at(0);
        Mazer::cell cn = {c.x + dirVals[rd].x, c.y + dirVals[rd].y};
        
        // Definitely out of bounds, no segfault/outofrange for us, thanks! :^)
        if(cn.x < 0 || cn.x >= width || cn.y < 0 || cn.y >= height)
        {
            cn = {x, y}; // This could be some kind of operator overloading of '=', but this is much cleaner, and keeps cn as a pure struct.
            dirs.erase(dirs.begin());
            continue;
        }

        offset = Pos2Offset(cn.x, cn.y);
        if(cells.at(offset) != true)
        {
            Mazer::edge e;
            #ifdef _DEBUG_
            std::cout << "found a cell at (" << cn.x << " " << cn.y << ")" << std::endl;
            #endif
            cells.at(offset) = true;

            e.c_A = c;
            e.c_B = cn;
            
            #ifdef _DEBUG_
                //std::cout << "Creating an edge between (" << e.c_A.x << ", " << e.c_A.y << ") and " << e.c_B.x << ", " << e.c_B.y << ")" << std::endl;
            #endif

            edges.push_back(e);
            c = cn;
            //count = 0;

            // New cell, so we refill the dirs vector
            dirs.resize(4);
            for(unsigned int i = 0; i < 4; i++)
                dirs.at(i) = i;

            continue;
        }
        else
        {
            dirs.erase(dirs.begin());
        }
    }while(!dirs.empty());



    #ifdef _DEBUG_
    std::cout << "done!" << std::endl;
    #endif

    count++;

    return c; // This is a cell that is completely boxed in
}


Mazer::cell Mazer::CMaze::Hunt(void)
{
    Mazer::cell c = INVALID_CELL;
    //std::mt19937 rng;
    int off = 0;

    #ifdef _DEBUG_
    std::cout << "Hunting..." << std::endl;
    #endif
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            off = Pos2Offset(x, y);
            if(cells.at(off) == true) 
            {
               continue;
            }
            else
            {    
                std::vector<Mazer::cell> cellList = GetNeighbours(x, y);
                
                // Try this for all neighbours
                for(std::size_t i = 0; i < cellList.size(); i++)
                {
                    std::uniform_int_distribution<std::mt19937::result_type> rnd(0, cellList.size() - 1);
                    int r = rnd(rng);
                
                    c = cellList.at(r);
                    if(c.x >= width || c.y >= height) // No exceptions in THIS dojo!
                        continue;
                    
                    int o = Pos2Offset(c.x, c.y);
                    if(cells.at(o) == true) // This cell has a visited neighbour! We'll go there next walk
                    {
                        c.x = x;
                        c.y = y;
                        goto end;
                    }
                }
            }
        }
    }

end:
    #ifdef _DEBUG_
    std::cout << "Finished hunting! Found a cell at " << c.x << " " << c.y << std::endl;
    #endif

    std::vector<Mazer::cell> neighbours = GetNeighbours(c);
    for(;;)
    {
        std::shuffle(neighbours.begin(), neighbours.end(), rng);
        Mazer::cell cj = neighbours.at(0);

        if(c.x == -1 || c.y == -1)
            break;
        
        if(cells.at(Pos2Offset(cj.x, cj.y)) == true)
        {
            #ifdef _DEBUG_
            std::cout << "HACK HACK! Creating edge on hunt!" << std::endl;
            #endif

            Mazer::edge e;
            e.c_A = c;
            e.c_B = neighbours.at(0);
            edges.push_back(e);
            break;
        }
    }

    return c;
}

void Mazer::CMaze::GenerateMaze()
{
    #ifdef _DEBUG_
    Mazer::Log(Mazer::LogLevel::INFO, "generation seed: 0x%x\n", seed);
    #endif
    
    //std::mt19937 rng;
    Mazer::cell c;
    std::uniform_int_distribution<std::mt19937::result_type> x_rng(0, width - 1);
    std::uniform_int_distribution<std::mt19937::result_type> y_rng(0, height - 1);

    // First, we need to start at a random point in the maze.
    int startx = x_rng(rng);
    int starty = y_rng(rng);

    #ifdef _DEBUG_
    std::cout << "random x start: " << startx << std::endl;
    std::cout << "random y start: " << starty << std::endl;
    #endif

    int start = Pos2Offset(startx, starty);
    cells.at(start) = true; // This cell has been visited.. OBVIOUSLY!
    
    c.x = startx;
    c.y = starty;
    std::vector<Mazer::cell> nei;
    while(c.x != -1 && c.y != -1)
    {
        Walk(c.x, c.y);
        c = Hunt();
    }

    
    Mazer::Log(Mazer::LogLevel::INFO, "Done Generating maze! Post check, please wait...\n");
    for(std::size_t i = 0; i < cells.size(); i++)
    {
        if((i % 8) == 0)
        {
            std::cout << "." << "" << std::flush;  
        }

        if(cells.at(i) == false)
        {
            Mazer::Log(Mazer::LogLevel::FATAL, "FATAL! Unvisited cell at : \n");
            break;
        }
    }
    std::cout << std::endl;
    //Mazer::Log(Mazer::LogLevel::INFO, "Done!\n");
}
**/

void Mazer::CMaze::WriteSVG(const std::string& path)
{
    std::ofstream mapFile;

    // Open a handle to the map file
    mapFile.open(path);

    if(!mapFile.is_open()) // There was an issue opening a handle to the file
    {
        status = LoadStatus::IO_ERROR;
        return;
    }

    mapFile << "<svg viewBox='0 0 " << width << " " << height << "'" << " width='500' height='500' xmlns='http://www.w3.org/2000/svg'>\n";
    mapFile << "\t<rect width='" << width << "'" << " height='"<< height << "' style='fill: black' />\n";

    for(std::list<Mazer::edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        Mazer::edge e = *it;

        mapFile << "\t<line stroke='white' stroke-width='0.5' "; 

        mapFile << "x1='"; 
        mapFile << static_cast<double>(e.c_A.x + 0.5);

        mapFile << "' y1='"; 
        mapFile << static_cast<double>(e.c_A.y + 0.5); 

        mapFile << "' x2='";
        mapFile << static_cast<double>(e.c_B.x + 0.5);

        mapFile << "' y2='"; 
        mapFile << static_cast<double>(e.c_B.y + 0.5);

        mapFile<< "'/>\n";
    }

    //mapFile << "</svg>";

    mapFile.close();

    status = LoadStatus::SUCCESS;
}

void Mazer::CMaze::VisitCell(const int& x, const int& y)
{
    int off = Pos2Offset(x, y);
    cells.at(off) = true;
}

void Mazer::CMaze::VisitCell(const Mazer::cell& c)
{
    int off = Pos2Offset(c);
    cells.at(off) = true;
}

bool Mazer::CMaze::IsCellVisited(const int& x, const int& y) const
{
    int off = Pos2Offset(x, y);
    
    return cells.at(off);
}

bool Mazer::CMaze::IsCellVisited(const Mazer::cell& c) const
{
    int off = Pos2Offset(c);

    return cells.at(off);
}

void Mazer::CMaze::AddEdge(Mazer::edge& e)
{
    edges.push_back(e);
}

const std::string Mazer::CMaze::GetError() const
{
    switch(status)
    {
    case LoadStatus::SUCCESS:
        return "MAP_OK";
    case LoadStatus::INVALID_MAZE:
        return "INVALID_MAZE";
    case LoadStatus::IO_ERROR:
        return "IO_ERROR";
    default:
        break;
    }

    return "";
}
