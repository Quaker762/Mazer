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

namespace Mazer{

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

public:
    /**
     *  Class Contructor
     */
    CMaze();
    CMaze(const std::string& path);

    /*
     *  Class Destructor
     */
    ~CMaze();

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

//    std::vector<std::vector<edge_t>> cells;    /**< Cell list, each _nested_ vector defines a ROW in the map (cells.at(0) would equate to ROW 0). */
};
}


#endif

