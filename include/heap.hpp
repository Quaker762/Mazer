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
#ifndef BINARY_HEAP_INCLUDED
#define BINARY_HEAP_INCLUDED

#include "cell.hpp"

#include <vector>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////

/**
 *  Node structure for our Binary Heap
 */
struct node
{
    Mazer::cell c;
    int         m_dist;

    // Less than
    bool operator<(node& rhs)
    {
        return m_dist < rhs.m_dist;
    }

    // Less than or equal to
    bool operator<=(node& rhs)
    {
        return m_dist <= rhs.m_dist;
    }

    // Greater than
    bool operator>(node& rhs)
    {
        return m_dist > rhs.m_dist;       
    }

    bool operator>=(node& rhs)
    {
        return m_dist >= rhs.m_dist;
    }
};
//////////////////////////////////////////////////////////////////////////////

namespace Mazer {

/**
 *  Binary max heap class for maze sorting algorithm
 */
template <class T>
class CBinaryHeap
{
public:
    
    /**
     *  Constructors
     */
    CBinaryHeap() : heap(0){};

    /**
     *  Get the leftmost node of parent i
     */
    T& GetLeft(int i) const{return heap.at(2*i);}

    /**
     *  Get the rightmost node of parent i
     */
    T& GetRight(int i) const{return heap.at((2*i)+1);}

    /**
     *  Get the index of the parent of a child node in the heap
     */
    int GetParentPtr(int child) const
    {
        if(child % 2 == 0)
            return (child / 2) - 1;
        else
            return child / 2;
    }

    /**
     *  Swap two nodes in the heap
     */
    void Swap(int n1, int n2)
    {
        std::swap(heap.at(n1), heap.at(n2));
    }

    /**
     *  Repair the heap after an insertion
     */
    void Repair()
    {
        int child   = heap.size() - 1;
        int parent  = GetParentPtr(child);

        while(heap.at(child) > heap.at(parent) && child >= 0 && parent >= 0)
        {
            Swap(child, parent);
            child = parent;
            parent = GetParentPtr(child);
        }
    }

    /**
     *  Insert a new value into the heap
     */
    void Insert(T& val)
    {
        heap.push_back(val);
        
        if(heap.size() > 1)
            Repair();
    }

    /**
     *  Repair the heap after node insertion
     */
    void MaxHeapify(int i)
    {
        int left    = 2*i;
        int right   = (2*i)+1;
        int largest = i;
    
        if(left <= heap.size() && heap.at(left) > heap.at(largest))
            largest = left;

        if(right <= heap.size() && heap.at(right) > heap.at(largest))
            largest = right;

        if(largest != i)
        {
            Swap(heap.at(i), heap.at(largest));
            MaxHeapify(largest);
        }
    }


private:
    std::vector<T> heap;

};







}












#endif
