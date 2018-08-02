/**
    Copyright (c) 2018 Jesse Buhagiar

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    urnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    HE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#include <iostream>
#include <string>
#include <fstream>

/////////////////////////////////////////// M    A    Z    E ////////////////////////////////////////////////
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
    Maze():width(0), height(0), edgeCount(0), status(LoadStatus::SUCCESS){};

    /**
     *  Generate a maze using the Hunt and Kill Algorithm
     */
    void Generate();

    /**
     *  Write this file to a disk.
     */
    void WriteToDisk(const std::string& fname) const;
    
    /**
     *  Set the width of the map
     */
    void SetWidth(int _width);

    /**
     *  Set the height of the map
     */
    void SetHeight(int _height);

private:
    int width;                                  /**< Maze Width */
    int height;                                 /**< Maze Height */
    int edgeCount;                              /**< Number of edges in the maze */

    LoadStatus status;                          /** Load status of this map */
};

void Maze::WriteToDisk(const std::string& fname) const
{
    std::ofstream output(fname, std::ios::binary);

    if(!output.is_open())
    {
        std::cout << "Unable to open a handle to file! Aborting..." << std::endl;
        return;
    }

    // Okay, we're good to write the file out to disk now!
    output.write(reinterpret_cast<const char*>(&width), sizeof(int));
    output.write(reinterpret_cast<const char*>(&height), sizeof(height));
    // TODO: Maze generation algorithm!!!

    std::cout << "Done!" << std::endl;    
    output.close();
}

void Maze::SetWidth(int _width)
{
    width = _width;
}

void Maze::SetHeight(int _height)
{
    height = _height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Invalid number of arguments! Usage: mazegen [filename]" << std::endl;
        return -1;
    }

    Maze maze;
    int width, height;

    std::cout << "Mazer Maze Generator!" << std::endl;
    
    std::cout << "Map width:";
    std::cin >> width;
    
    std::cout << "Map height: ";
    std::cin >> height;

    maze.SetWidth(width);
    maze.SetHeight(height);
    std::cout << "Writing map to disk..." << std::endl;

    maze.WriteToDisk(argv[1]);
    return 0;
}

