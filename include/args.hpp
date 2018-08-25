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
#ifndef _ARGS_HPP_INCLUDED_
#define _ARGS_HPP_INCLUDED_

#include <string>
#include <vector>
#include <cstdint>

namespace Mazer{

class CArgs{

public:
	CArgs(int argc, char** argv);

    /**
     *  Parse all input arguments and dispatch appropriate jobs
     */
    void Parse() const;


private:
	std::vector<std::string>   args;
	std::uint32_t              seed;

private:
    const std::string ARGV_FAIL = "Input argument failure";
    const std::string LOAD_BIN = "--lb";
    const std::string SAVE_BIN = "--sb";
    const std::string SAVE_SVG = "--sv";
    const std::string GEN_SEED = "--g";
};

}

#endif
