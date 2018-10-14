/**
 *  Copyright (c) 2018 Jesse Buhagiar
 *
 *  Maze related structures and classes.
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
 *  SOFTWARE
 **/
#ifndef _MAZE_HPP_INCLUDED_
#define _MAZE_HPP_INCLUDED_

#include <string>
#include <vector>
#include <list>
#include <cstdint>
#include <ctime>
#include <set>

#include "cell.hpp"
#include "edge.hpp"

namespace Mazer{

static const cell INVALID_CELL = Mazer::cell{-1, -1};

class CMaze
{
public:
    enum class LoadStatus
    {
        SUCCESS,
        INVALID_MAZE,
        IO_ERROR,
        FATAL_ERROR,
    };

    static constexpr std::uint32_t DEFAULT_SEED = 0xDEADBEEF;

public:
    /**
     *  Class Contructor
     */
    CMaze() = delete;
    CMaze(const int& width = 64, const int& height = 64, const std::uint32_t seed = std::time(nullptr)); // Is it stupid to pass by reference if an int is 32 bits and pointer to the int is 64 bits..?!?!
    CMaze(const std::string& path);

    /*
     *  Class Destructor
     */
    ~CMaze();

    /**
     *  Set the width of this maze
     */
    void SetWidth(const int width);

    /**
     *  Set the height of this maze
     */
    void SetHeight(const int height);

    /**
     *  Set the generation seed of this maze
     */
    void SetSeed(const int seed);

    /**
     *  Get the height of the maze
     */
    const int& GetHeight() const;

    /**
     *  Get the width of the maze
     */
    const int& GetWidth() const;

    /**
     *  Get the seed that was used to generate this maze
     */
    const std::uint32_t& GetSeed() const;
    
    /**
     *  Generate a new maze using the 'Hunt and Kill Algorithm'.
     */
    //void GenerateMaze();

    /**
     *  Save this maze as a .maze binary file
     */
    void WriteBinary(const std::string& path);
    
    /**
     *  Loads a Maze from disk.
     *
     *  @param path The physical path to the maze binary file.
     */
    void LoadBinary(const std::string& path);

    /**
     *  Writes an SVG from maze.
     *
     *  @param path The physical path to the SVG file.
     */
    void WriteSVG(const std::string& path);

    /**
     *  Get the load status of an IO operation.
     */
    LoadStatus GetStatus() const{return status;}

    /**
     *  Get the current load status of this map file and turn it into a human readable string.
     */
    const std::string GetError() const;

    /**
     *  Walk the grid by advancing to a random cell left, right, up or down from where we are,
     *  all the while checking whether they have been visited or not.
     */
    //Mazer::cell Walk(const int& x, const int& y);
    
    /**
     *  Search each row for a cell with at least one unvisited neighbour.
     */
    //Mazer::cell Hunt(void);

	/**
 	 *	Get a list of neigbours given a position	
	 */
	std::vector<Mazer::cell> GetNeighbours(const int& x, const int& y) const;
	std::vector<Mazer::cell> GetNeighbours(const Mazer::cell& c) const;	

    /**
     *  Set a particular cell as being visited
     */
    void VisitCell(const int& x, const int& y);
    void VisitCell(const Mazer::cell& c);

    /**
     *  Get whether or not a cell has been visited
     */
    bool IsCellVisited(const int& x, const int& y) const;
    bool IsCellVisited(const Mazer::cell& c) const;

    /**
     *  Generate an index in our grid (a one dimensional array) given two co-ords.
     */
    int Pos2Offset(const int& x, const int& y) const;
	int Pos2Offset(const Mazer::cell& c) const;
		
    /**
     *  Add an edge to the edge list
     */
    void AddEdge(Mazer::edge& e);

private:
    int 				    width;                                  /**< Maze Width */
    int 				    height;                                 /**< Maze Height */

    std::uint32_t           seed;                                   /**< Seed used to generate this maze */
    
    LoadStatus 			    status;                          		/**< Load status of this map */

    std::vector<bool> 	    cells;                    				/**< Array desribing which cells we have visited (for generation) */
    std::list<Mazer::edge>  edges;                                  /**< List of edges */

public:
    /**
     *  Cell directions
     */
    Mazer::cell dirVals[4] =
    {
        {0, 1}, // North
        {1, 0}, // East
        {0, -1}, //South
        {-1, 0} // West
    };
};
}


#endif

