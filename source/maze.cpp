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

static constexpr Mazer::cell INVALID_CELL = Mazer::cell{-1, -1};

Mazer::CMaze::CMaze() : width(0), height(0), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{

}

Mazer::CMaze::CMaze(const int& _width, const int& _height) : width(_width), height(_height), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    cells.resize(width * height);
    std::fill(cells.begin(), cells.end(), false);
}

Mazer::CMaze::CMaze(const std::string& path) : width(0), height(0), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    Load(path);
}

Mazer::CMaze::~CMaze()
{
}

int Mazer::CMaze::Pos2Offset(const int& x, const int& y) const
{
    return y * width + x;
}

int Mazer::CMaze::Pos2Offset(const Mazer::cell& c) const
{
	return c.y * width + c.x;
}

std::list<Mazer::cell> Mazer::CMaze::GetNeighbours(const Mazer::cell& c) const
{
    std::list<Mazer::cell> list;

    list.push_back(Mazer::cell{c.x-1, c.y}); // Left neighbour
    list.push_back(Mazer::cell{c.x+1, c.y}); // Right neighbour
    list.push_back(Mazer::cell{c.x, c.y+1}); // Top neighbour
    list.push_back(Mazer::cell{c.x, c.y-1}); // Bottom neighbour

    return list;
}

std::list<Mazer::cell> Mazer::CMaze::GetNeighbours(const int& x, const int& y) const
{
    std::list<Mazer::cell> list;

    list.push_back(Mazer::cell{x-1, y}); // Left neighbour
    list.push_back(Mazer::cell{x+1, y}); // Right neighbour
    list.push_back(Mazer::cell{x, y+1}); // Top neighbour
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

    rng.seed(std::time(nullptr));
    std::cout << "walking..." << std::endl;
    do
    {
        count++;

        int offset = 0;
        std::shuffle(dirs.begin(), dirs.end(), rng);
        int rd = dirs.at(0);
        Mazer::cell cn = {c.x + dirVals[rd].x, c.y + dirVals[rd].y};
        
        offset = Pos2Offset(cn);
       
        if(cells.at(offset) != true)
        {
            std::cout << "found a cell at " << cn.x << " " << cn.y << std::endl;
            cells.at(offset) = true;
            c = cn;
            count = 0;
            continue;
        }   
    }while(count != 4);

    std::cout << "done!" << std::endl;
    return c; // This is a cell that is completely boxed in
}

void Mazer::CMaze::GenerateMaze(std::uint32_t seed)
{
    #ifdef _DEBUG_
    Mazer::Log(Mazer::LogLevel::INFO, "generation seed: 0x%x\n", seed);
    #endif
    
    std::mt19937 rng;
    rng.seed(seed);
    std::uniform_int_distribution<std::mt19937::result_type> x_rng(0, width);
    std::uniform_int_distribution<std::mt19937::result_type> y_rng(0, height);

    // First, we need to start at a random point in the maze.
    int startx = x_rng(rng);
    int starty = y_rng(rng);

    #ifdef _DEBUG_
    std::cout << "random x start: " << startx << std::endl;
    std::cout << "random y start: " << starty << std::endl;
    #endif

    int start = Pos2Offset(startx, starty);
    cells.at(start) = true; // This cell has been visited.. OBVIOUSLY!

    Walk(startx, starty);
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
