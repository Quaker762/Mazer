/**
 *  Cell class. Defines one logical unit (square) in our map.
 *
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
namespace Mazer{

/**
 *  Cell class. Each square defines a logical (x,y) point on our maze. Each maze is made up
 *  of MxN cells (where M and N are valid integers). However, if desired, any type
 *  can be used in place (such as a float?!).
 */
template <typename T>
class CCell
{

public:
    /**
     *  Which way is this cell facing?
     */
    enum class DIRECTION
    {
        UP,     /** Walls on left and right side */
        DOWN,   /** Walls on left and right side */
        LEFT,   /** Walls on top, bottom and right side */
        RIGHT   /** Walls on top, bottom and left side */
    }

public:
    /**
     *  Default constructor
     */
    CCell() = default;

    /**
     *  
     */
    CCell(T x, T y);

    /**
     *  Set x-loc.
     */
    void SetX(T x);

    /**
     *  Get x-loc.
     */
    T GetX() const;

    /**
     *  Set y-loc.
     */
    void SetY(T y);

    /**
     *  Get y-loc.
     */
    T GetY() const;

private:
    T x;  /**< Cartesian x co-ord of this cell */
    T y;  /**< Cartesian y co-ord of this cell */
}
}











}}
