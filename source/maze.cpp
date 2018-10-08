/**
 *  Copyright (c) 2018 Jesse Buhagiar and Timothy Davis
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
#include "maze.hpp"

#include <iostream>



Mazer::CMaze::CMaze(const unsigned int& _width, const unsigned int& _height, const std::uint32_t& _seed) : width(_width), height(_height), seed(_seed), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    cells.resize(width * height);
    std::fill(cells.begin(), cells.end(), false);
}

Mazer::CMaze::CMaze(const std::string& path) : width(0), height(0), seed(0), status(LoadStatus::INVALID_MAZE), cells(false), edges()
{
    LoadBinary(path);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void Mazer::CMaze::WriteBinary(const std::string& path)
{
    std::cout << "TODO: Implement Me!!!";
}

void Mazer::CMaze::LoadBinary(const std::string& path)
{
    std::cout << "TODO: Implement Me!!!";
}

void Mazer::CMaze::WriteSVG(const std::string& path)
{
    std::cout << "TODO: Implement Me!!!";
}
