/**
 *  Implementation of Maze.hpp
 */
#include "maze.hpp"
#include "log.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

#define _DEBUG_

static constexpr Mazer::cell INVALID_CELL = Mazer::cell{-1, -1};

Mazer::CMaze::CMaze() : width(0), height(0), edgeCount(0), seed(DEFAULT_SEED), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{

}

Mazer::CMaze::CMaze(const int& _width, const int& _height, const std::uint32_t _seed) : width(_width), height(_height), edgeCount(0), seed(_seed), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    cells.resize(width * height);
    std::fill(cells.begin(), cells.end(), false);
}

Mazer::CMaze::CMaze(const std::string& path) : width(0), height(0), edgeCount(0), seed(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    Load(path);
}

Mazer::CMaze::~CMaze()
{
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

// TODO: Refactor me to be void and store LoadStatus inside the class!!!!
void Mazer::CMaze::Load(const std::string& path)
{
    std::ifstream mapFile;

    // Open a handle to the map file
    mapFile.open(path, std::ios::binary);
    if(!mapFile.is_open()) // There was an issue opening a handle to the file
    {
        status = LoadStatus::IO_ERROR;
        return;
    }

    // We can now actually read the binary file into our class
    mapFile.read(reinterpret_cast<char*>(width), sizeof(int));          // Map width
    mapFile.read(reinterpret_cast<char*>(height), sizeof(int));         // Map height
    mapFile.read(reinterpret_cast<char*>(edgeCount), sizeof(int));      // Count of edges in map

    mapFile.close();

    status = LoadStatus::SUCCESS;
}

Mazer::cell Mazer::CMaze::Walk(const int& x, const int& y)
{
    Mazer::cell         c = Mazer::cell{x, y};
    std::vector<int>    dirs;
    std::mt19937        rng;
    int                 count = 0;
    //////////////////////////////////////////////////////////
    
    // Fill dirs vector
    dirs.reserve(4);
    for(unsigned int i = 0; i < 4; i++)
    {
        dirs.push_back(i);
    }

    rng.seed(seed);
    #ifdef _DEBUG_
    std::cout << "walking..." << std::endl;
    #endif
    if(x >= width || y >= height)
        std::cout << "What the fuck?!?!" << x << " " << y << std::endl;
    
    cells.at(Pos2Offset(x, y)) = true;
    do
    {
        count++;

        int offset = 0;
        std::shuffle(dirs.begin(), dirs.end(), rng);
        int rd = dirs.at(0);
        Mazer::cell cn = {c.x + dirVals[rd].x, c.y + dirVals[rd].y};
       
        // Definitely out of bounds, no segfault/outofrange for us, thanks! :^)
        if(cn.x < 0 || cn.x >= width || cn.y < 0 || cn.y >= height)
        {
            cn = {x, y}; // This could be some kind of operator overloading of '=', but this is much cleaner, and keeps cn as a pure struct.
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
                std::cout << "Creating an edge between (" << e.c_A.x << ", " << e.c_A.y << ") and " << e.c_B.x << ", " << e.c_B.y << ")" << std::endl;
            #endif

            edges.push_back(e);
            c = cn;
            count = 0;
            continue;
        }   
    }while(count != 4);

    #ifdef _DEBUG_
    std::cout << "done!" << std::endl;
    #endif

    return c; // This is a cell that is completely boxed in
}

Mazer::cell Mazer::CMaze::Hunt(void) const
{
    Mazer::cell c = INVALID_CELL;
    std::mt19937 rng;
    int off = 0;

    #ifdef _DEBUG_
    std::cout << "Hunting..." << std::endl;
    #endif
    rng.seed(seed);
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
    return c;
}

void Mazer::CMaze::GenerateMaze(std::uint32_t seed)
{
    #ifdef _DEBUG_
    Mazer::Log(Mazer::LogLevel::INFO, "generation seed: 0x%x\n", seed);
    #endif
    
    std::mt19937 rng;
    rng.seed(seed);
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
    while(c.x != -1 && c.y != -1)
    {
        Walk(c.x, c.y);
        c = Hunt();
    }

    
    Mazer::Log(Mazer::LogLevel::INFO, "Done Generating maze! Post check, please wait...\n");
    for(std::size_t i = 0; i < cells.size(); i++)
    {
        std::cout << ".";
        std::flush(std::cout);
        if(cells.at(i) == false)
        {
            Mazer::Log(Mazer::LogLevel::FATAL, "FATAL! Unvisited cell at : \n");
            break;
        }
    }
    Mazer::Log(Mazer::LogLevel::INFO, "Done!\n");
}

void Mazer::CMaze::WriteSVG(const std::string& path)
{
    std::ofstream mapFile;

    // Open a handle to the map file
    mapFile.open(path);

    if(!mapFile.is_open()) // There was an issue opening a handle to the file
    {
        //status = LoadStatus::IO_ERROR;
        return;
    }

    mapFile << "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>\n";
    mapFile << "\t<rect width='1' height='1' style='fill: black' />\n";

    /*edge e;

    for(int i = 0; i < edge_struct.get_size(); i++)
    {
        e[i]; //get from list of edges that Jesse makes

        mapFile << "<\tline stroke='white' stroke-width='0.005'"; 

        mapFile << "x1='"; 
        mapFile << e.c_A.x;

        mapFile << "' y1='"; 
        mapFile << e.c_A.y; 

        mapFile << "' x2='";
        mapFile << e.c_B.x;

        mapFile << "' y2='"; 
        mapFile << e.c_B.y;

        mapFile<< "'/>\n";
    }*/

    mapFile << "</svg>";

    mapFile.close();

    //status = LoadStatus::SUCCESS;
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
