/**
 *  Implementation of Maze.hpp
 */
#include "maze.hpp"

#include <fstream>

Maze::Maze() : width(0), height(0), edgeCount(0), status(LoadStatus::SUCCESS), cells(0)
{
}

Maze::Maze(const std::string& path) : width(0), height(0), edgeCount(0), status(LoadStatus::SUCCESS), cells(0)
{
    Load(path);
}

Maze::~Maze()
{
}

// TODO: Refactor me to be void and store LoadStatus inside the class!!!!
void Maze::Load(const std::string& path)
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

    status = LoadStatus::SUCCESS;
}

const std::string Maze::GetError() const
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
