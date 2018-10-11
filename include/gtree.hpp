/**
 *  Copyright (c) 2018 Jesse Buhagiar
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
#ifndef GTREE_INCLUDED
#define GTREE_INCLUDED

#include <cstdint>
#include <vector>
#include <random>

#include "maze.hpp"

namespace Mazer
{

/**
 *  Our growing tree 'algorithm' class. All other generation algorithms inherit off of this. Therefore, 
 *  the generate function must make a decision on what function to actually call (which will be in vtable, because
 *  the function _MUST_ be implemented in the derived class). This class acts as 'CMaze' did in the first one,
 *  that is, generate is called from this class and 'CMaze' is merely a data class.
 */
class CGrowingTree
{
public:

    /**
     *  Don't allow the default constructor
     */
    CGrowingTree() = delete;

    /**
     *  Actual constructor
     */
    explicit CGrowingTree(const int& width, const int& height, const std::uint32_t& seed);

    /**
     *  Virtual destructor to prevent to prevent gcc from being angry at me! :^)
     *  (Oh, and to stop undefined behaviour when deleting the base class, of course..)
     */
    virtual ~CGrowingTree(){}

    /**
     *  Generate the maze
     */
    void GenerateMaze();

    /**
     *  
     */
    virtual int GetNextCellIndex(void) = 0;

protected:
    CMaze                       maze;       /**< Our maze object (Should be used for data only!) */
    
    std::vector<cell>           cellList;   /**< Our cell list, C, for the growing tree */
    std::mt19937                rng;        /**< Our random number generator */
};

}
















#endif
