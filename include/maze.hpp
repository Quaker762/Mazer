/**
 *  Copyright (c) 2018 Jesse Buhagiar and Timothy Davis
 *
 *  Pure virtual class that all maze types (with their respective algorithms) inherit off of.
 *  This class _CANNOT_ be instantiated!
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
#ifndef _MAZE_HPP_INCLUDED_
#define _MAZE_HPP_INCLUDED_

#include <string>
#include <vector>
#include <list>
#include <cstdint>
#include <ctime>

#include "cell.hpp"
#include "edge.hpp"

namespace Mazer{

/**
 *  Pure virtual maze class.
 */
class CMaze
{
public:
    
    /**
     *  Load status enum. 
     *  Gives information about the load state of the maze
     */
    enum LoadStatus
    {
        SUCCESS,
        INVALID_MAZE,
        IO_ERROR,
        FATAL_ERROR
    };

    /**
     *  Default constructor
     */
    CMaze() = delete;
    explicit CMaze(const int& width = 64, const int& height = 64, const std::uint32_t& seed = std::time(nullptr)) = 0;
    explicit CMaze(const std::string& path) = 0;

    /**
     *  Virtual destructor
     */
    virtual ~CMaze() = 0;

    /**
     *  Set the width of a maze
     */
    inline void SetWidth(const unsigned int& width){this->width = width;}

    /**
     *  Set the height of a maze
     */
    inline void SetHeight(const unsigned int& height){this->height = height;}

    /**
     *  Set the seed of the maze
     */
    inline void SetSeed(const unsigned int& seed){this->seed = seed;}

    /**
     *  Get the width of this maze
     */
    const unsigned int& GetWidth() const{return width;}

    /**
     *  Get the height of this maze
     */
    const unsigned int& GetHeight() const{return height;}

    /**
     * Get the seed of this maze
     */
    const std::uint32_t& GetSeed() const{return seed;}

    /**
     *  Maze Generation function. This is PURE VIRTUAL because the subclass _must_ implement it!
     */
    virtual void GenerateMaze() = 0;

    /**
     *  Write this maze file to a binary
     */
    void WriteBinary(const std::string& path);

    /**
     *  Loads a Maze binary file from disk
     */
    void LoadBinary(const std::string& path);

    /**
     *  Save this maze as an SVG
     */
    void WriteSVG(const std::string& path);

    /**
     *  Get the load status of an IO operation
     */
    inline LoadStatus& GetStatus() const{return status;}

    /**
     *  Get the current load status of this map file and turn it into a human readable string.
     */
    const inline std::string& GetError() const;

private:
    unsigned int    width;
    unsigned int    height;

    std::uint32_t   seed;   


};












}







#endif
