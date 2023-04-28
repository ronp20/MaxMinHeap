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

    static void build(std::vector<int>& heap)
    {
        int heapSize = static_cast<int>(heap.size());
        for (auto i = (heapSize / 2); i >= 0; --i)
        {
            PushDown(heap, i);
        }
    }

    static void PrintHeap(const std::vector<int>& heap)
    {
        for (auto i = 0; i < heap.size(); ++i)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    static void PushDown(
            std::vector<int>& heap,
            size_t index)
    {
        static std::greater_equal<int> bigger;
        static std::less_equal<int> lesser;

        auto level = DepthFromIndex(index);
        if (level % 2 == 0)
        {
            PushDownMin(heap,
                    index,
                    bigger);
        }
        else
        {
            PushDownMin(heap,
                    index,
                    lesser);
        }
    }
    
private:
    static void PushDownMin(
            std::vector<int>& heap,
            size_t index,
            std::function<bool (int, int)> comparator)
    {
        if (!IsIndexExists(heap, index))
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
        if (!IsIndexExists(heap,leftChild) &&
            !IsIndexExists(heap, rightChild))
        {
            return;    
        }
        
        bool isGrandChild;
        size_t smallestIndex = index;
        
        isGrandChild = false;
        if (IsIndexExists(heap, leftChild))
        {
            smallestIndex = comparator(heap[leftChild], heap[index]) ?
                            leftChild : 
                            index;

            if (IsIndexExists(heap, rightChild))
            {
                smallestIndex = comparator(heap[rightChild], heap[smallestIndex]) ?
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


            if (IsIndexExists(heap, leftGrandChildLeft))
            {
                if (comparator(heap[leftGrandChildLeft], heap[smallestIndex]))
                {
                    smallestIndex = leftGrandChildLeft;
                    isGrandChild = true;
                }

            }
            if (IsIndexExists(heap, leftGrandChildRight))
            {
                if (comparator(heap[leftGrandChildRight], heap[smallestIndex]))
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

            if (IsIndexExists(heap, rightGrandChildLeft))
            {
                if (comparator(heap[rightGrandChildLeft], heap[smallestIndex]))
                {
                    smallestIndex = rightGrandChildLeft;
                    isGrandChild = true;
                }
            }

            if (IsIndexExists(heap, rightGrandChildRight))
            {
                if (comparator(heap[rightGrandChildRight], heap[smallestIndex]))
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
            if(comparator(heap[smallestIndex], heap[index]))
            {
                std::swap(heap[smallestIndex], heap[index]);

                if (smallestIndex != 0)
                {
                    auto parentSmllestIndex = GetParentIndex(smallestIndex);

                    if (!comparator(heap[smallestIndex], heap[parentSmllestIndex]))
                    {
                        std::swap(heap[smallestIndex], heap[parentSmllestIndex]);
                    }

                    PushDown(heap, smallestIndex);
                }

            }
        }
        else if(comparator(heap[smallestIndex], heap[index]))
        {
            std::swap(heap[smallestIndex], heap[index]);
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

    static bool inline IsIndexExists(
            const std::vector<int>& heap,
            size_t index)
    {
        return (index < heap.size());
    }

//    std::vector<int> _heap;
};

int main() 
{
    std::cout << "Hello world!" << std::endl;
//    std::vector<int> vec {8, 71, 41, 31, 10, 11, 16, 46, 51, 31, 21, 13};
//    std::vector<int> vec {11, 71, 21, 31, 51, 8, 16, 46, 10, 31, 41, 13}; // 71 10 8 46 51 21 16 31 11 31 41 13
    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; //12 2 1 9 11 6 7 8 4 10 5 3

//    MaxMinHeap heap(std::move(vec));
//    heap.PushDown(5);
    MaxMinHeap::build(vec);
    MaxMinHeap::PrintHeap(vec);

    return 0;
}