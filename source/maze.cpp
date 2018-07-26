/**
 *  Implementation of Maze.hpp
 */
#include "maze.hpp"

Maze::Maze() : width(0), height(0), edgeCount(0), cells(0)
{
}

Maze::Maze(const std::string& path) : width(0), height(0), edgeCount(0), cells(0)
{
    Load(path);
}

Maze::~Maze()
{
}

Maze::LoadStatus Maze::Load(const std::string& path)
{
    return LoadStatus::SUCCESS;
}
