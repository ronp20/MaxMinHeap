// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

constexpr int HEAP_MAX_CAPACITY = 100;
using namespace std;
class MaxMinHeap
{
public:
    explicit MaxMinHeap(std::vector<int>&& heap):
    _heap(std::move(heap))
    {}

    void build()
    {
        for (int i = static_cast<int>(_heap.size() / 2); i >= 0; --i)
        {
            cout << "Index " << i << endl;
            PushDown(i);
        }
    }

    void PrintHeap() const
    {
        for (auto i = 0; i < _heap.size(); ++i)
        {
            cout << _heap[i] << " ";
        }
        cout << endl;
    }
    void PushDown(size_t index)
    {
        static std::greater_equal<int> bigger;
        static std::less_equal<int> lesser;

        auto level = DepthFromIndex(index);
        if (level % 2 == 0)
        {
            PushDownMin(index, bigger);
        }
        else
        {
            PushDownMin(index, lesser);
        }
    }
    
private:
    void PushDownMin(
            size_t index,
            std::function<bool (int, int)> comparator)
    {
        if (!IsIndexExists(index))
        {
            return;
        }

        size_t leftChild, rightChild;
        
        GetLeftChildIndex(
            index,
            leftChild);

        GetRightChildIndex(
            index,
            rightChild);

        //Check if the node have child's 
        if (!IsIndexExists(leftChild) &&
            !IsIndexExists(rightChild))
        {
            return;    
        }
        
        bool isGrandChild;
        size_t smallestIndex = index;
        
        isGrandChild = false;
        if (IsIndexExists(leftChild))
        {
            smallestIndex = comparator(_heap[leftChild], _heap[index]) ?
                            leftChild : 
                            index;

            if (IsIndexExists(rightChild))
            {
                smallestIndex = comparator(_heap[rightChild], _heap[smallestIndex]) ?
                                rightChild : 
                                smallestIndex;
            }

            size_t leftGrandChildLeft, leftGrandChildRight;
            GetLeftChildIndex(
                leftChild,
                leftGrandChildLeft);

            GetRightChildIndex(
                leftChild,
                leftGrandChildRight);


            if (IsIndexExists(leftGrandChildLeft))
            {
                if (comparator(_heap[leftGrandChildLeft], _heap[smallestIndex]))
                {
                    smallestIndex = leftGrandChildLeft;
                    isGrandChild = true;
                }

            }
            if (IsIndexExists(leftGrandChildRight))
            {
                if (comparator(_heap[leftGrandChildRight], _heap[smallestIndex]))
                {
                    smallestIndex = leftGrandChildRight;
                    isGrandChild = true;
                }
            }

            size_t rightGrandChildLeft, rightGrandChildRight;
            GetLeftChildIndex(
                rightChild,
                rightGrandChildLeft);

            GetRightChildIndex(
                rightChild,
                rightGrandChildRight);

            if (IsIndexExists(rightGrandChildLeft))
            {
                if (comparator(_heap[rightGrandChildLeft], _heap[smallestIndex]))
                {
                    smallestIndex = rightGrandChildLeft;
                    isGrandChild = true;
                }
            }

            if (IsIndexExists(rightGrandChildRight))
            {
                if (comparator(_heap[rightGrandChildRight], _heap[smallestIndex]))
                {
                    smallestIndex = rightGrandChildRight;
                    isGrandChild = true;
                }
            }

//            cout << "Push Down Min left chiled index " <<  leftChild << endl;
//            cout << "Push Down Min right chiled index " <<  rightChild << endl;
//
//            cout << "Push Down Min left grandchiled left index " << leftGrandChildLeft << endl;
//            cout << "Push Down Min left grandchiled left index " <<  leftGrandChildRight << endl;
//
//            cout << "Push Down Min right grandchiled left index " << rightGrandChildLeft << endl;
//            cout << "Push Down Min right grandchiled left index " <<  rightGrandChildRight << endl;
//
//            cout << "Push Down Min right smallest index " <<  smallestIndex << endl;
//            PrintHeap();

        }

        if (isGrandChild)
        {
//            cout << "GrandChiled " << endl;
            if(comparator(_heap[smallestIndex], _heap[index]))
            {
                std::swap(_heap[smallestIndex], _heap[index]);

                if (smallestIndex != 0)
                {
                    auto parentSmllestIndex = GetParentIndex(smallestIndex);

                    if (!comparator(_heap[smallestIndex], _heap[parentSmllestIndex]))
                    {
                        std::swap(_heap[smallestIndex], _heap[parentSmllestIndex]);   
                    }

                    PushDown(smallestIndex);
                }

            }
        }
        else if(comparator(_heap[smallestIndex], _heap[index]))
        {
            std::swap(_heap[smallestIndex], _heap[index]);
        }
    }

    static inline size_t DepthFromIndex(size_t index)
    {
        return floor(log2(++index));
    }

    static size_t GetParentIndex(size_t index)
    {
        if (index != 0)
        {
            return (index % 2  == 0) ? (floor(index / 2) - 1): floor(index / 2);
        }

        return 0;
    }

    static inline void GetLeftChildIndex(
        size_t index,
        size_t& leftChildIndex)
    {
        leftChildIndex = (index * 2) + 1;
    }

     static inline void GetRightChildIndex(
        size_t index,
        size_t& rightChildIndex)
    {
        rightChildIndex = (index * 2) + 2;
    }

    bool inline IsIndexExists(size_t index) const
    {
        return (index < _heap.size());
    }

    std::vector<int> _heap;
};

int main() 
{
    std::cout << "Hello world!" << std::endl;
//    std::vector<int> vec {8, 71, 41, 31, 10, 11, 16, 46, 51, 31, 21, 13};
//    std::vector<int> vec {11, 71, 21, 31, 51, 8, 16, 46, 10, 31, 41, 13}; // 71 10 8 46 51 21 16 31 11 31 41 13
//    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; //12 2 1 9 11 6 7 8 4 10 5 3

    MaxMinHeap heap(std::move(vec));
//    heap.PushDown(5);
    heap.build();
    heap.PrintHeap();

    return 0;
}