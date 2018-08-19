/**
 *  Implementation of Maze.hpp
 */
#include "maze.hpp"
#include "log.hpp"

#include <fstream>
#include <algorithm>

Mazer::CMaze::CMaze() : width(0), height(0), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false)
{

}

Mazer::CMaze::CMaze(int _width, int _height) : width(_width), height(_height), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false)
{
    cells.resize(width * height);
    std::fill(cells.begin(), cells.end(), false);
}

Mazer::CMaze::CMaze(const std::string& path) : width(0), height(0), edgeCount(0), status(LoadStatus::INVALID_MAZE), cells(false)
{
    Load(path);
}

Mazer::CMaze::~CMaze()
{
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

    status = LoadStatus::SUCCESS;
}

void Mazer::CMaze::GenerateMaze(std::uint32_t seed)
{
    Mazer::Log(Mazer::LogLevel::INFO, "default seed: 0x%x\n", seed);
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
