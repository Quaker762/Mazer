/**
 *  Structures and class to perform operations on Mazes
 */
#ifndef _MAZE_HPP_INCLUDED_
#define _MAZE_HPP_INCLUDED_

#include <string>
#include <vector>

//TODO: Change to class?!?!?!
struct edge_t
{
    int x_cellA;
    int y_cellA;
    int x_cellB;
    int y_cellB;
};

struct point_t
{
    int x;
    int y;
};

class Maze
{
public:
    enum class LoadStatus
    {
        SUCCESS,
        INVALID_MAZE,
        IO_ERROR,
        FATAL_ERROR,
    };

public:
    /**
     *  Class Contructor
     */
    Maze();
    Maze(const std::string& path);

    /*
     *  Class Destructor
     */
    ~Maze();

    /**
     *  Loads a Maze from disk.
     *
     *  @param path The physical path to the maze binary file.
     */
    LoadStatus Load(const std::string& path);

private:
    int width;      /**< Maze Width */
    int height;     /**< Maze Height */
    int edgeCount;  /**< Number of edges in the maze */

    std::vector<std::vector<point_t>> cells;
};



#endif
