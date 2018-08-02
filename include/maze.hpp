/**
 *  Structures and class to perform operations on Mazes
 */
#ifndef _MAZE_HPP_INCLUDED_
#define _MAZE_HPP_INCLUDED_

#include <string>
#include <vector>

/**
 *  Defines a logical (x, y) position in cartesian space
 */
struct point_t
{
    int x;
    int y;
} __attribute__((packed));

/**
 *  An edge is defined 
 */
struct edge_t
{
    point_t cellA;
    point_t cellB;
} __attribute__((packed));

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
    void Load(const std::string& path);

    /**
     *  Get the current load status of this map file and turn it into a human readable string.
     */
    const std::string GetError() const;

private:
    int width;                                  /**< Maze Width */
    int height;                                 /**< Maze Height */
    int edgeCount;                              /**< Number of edges in the maze */

    LoadStatus status;                          /** Load status of this map */

    std::vector<std::vector<edge_t>> cells;    /**< Cell list, each _nested_ vector defines a ROW in the map (cells.at(0) would equate to ROW 0). */
};



#endif
