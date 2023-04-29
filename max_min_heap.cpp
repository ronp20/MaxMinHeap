// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

using namespace std;
class MaxMinHeap
{
public:

    static void BuildHeap(std::vector<int>& heap)
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

    static void Insert(std::vector<int>& heap, int key)
    {
        heap.push_back(key);
        PushUp(heap, (heap.size() - 1));
    }

    static void Delete(std::vector<int>& heap, size_t index)
    {
        if (IsIndexExists(heap, index))
        {
            std::swap(heap[index], heap[heap.size() - 1]);
            heap.pop_back();
            PushDown(heap, index);
            PushUp(heap,index);
        }
    }

    static bool ExtractMax(
            std::vector<int>& heap,
            int& max)
    {
        auto retValue{true};
        if (heap.size() != 0)
        {
            max = heap[0];
            std::swap(heap[0], heap[heap.size() - 1]);
            heap.pop_back();
            PushDown(heap, 0);
        }
        else
        {
            cout << "Cannot Extract Max, Heap Is Empty" << endl;
            retValue = false;
        }

        return retValue;
    }

    static bool ExtractMin(
            std::vector<int>& heap,
            int& min)
    {
        auto retValue{true};
        auto heapSize = heap.size();

        if (heapSize != 0)
        {
            size_t minIndex;

            if (heapSize == 1)
            {
                minIndex = 0;
                min = heap[0];
            }
            else if (heapSize == 2)
            {
                minIndex = 1;
                min = heap[1];
            }
            else
            {
                if (heap[1] < heap[2])
                {
                    minIndex = 1;
                    min = heap[1];
                }
                else
                {
                    minIndex = 2;
                    min = heap[2];
                }
            }

            std::swap(heap[minIndex], heap[heap.size() - 1]);
            heap.pop_back();
            PushDown(heap, minIndex);
        }
        else
        {
            cout << "Cannot Extract Min, Heap Is Empty" << endl;
            retValue = false;
        }

        return retValue;
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

    static void PushUp(std::vector<int>& heap, size_t index)
    {
        if (!IsRoot(index))
        {
            auto indexParent = GetParentIndex(index);

            if (IsMaxLevel(index))
            {
                if (heap[index] < heap[indexParent])
                {
                    std::swap(heap[index], heap[indexParent]);
                    PushUpMin(heap, indexParent);
                }
                else
                {
                    PushUpMax(heap, index);
                }
            }
            else
            {
                if (heap[index] > heap[indexParent])
                {
                    std::swap(heap[index], heap[indexParent]);
                    PushUpMax(heap, indexParent);
                }
                else
                {
                    PushUpMin(heap, index);
                }
            }
        }
    }

    static void PushUpMin(std::vector<int>& heap, size_t index)
    {
        auto indexParent = GetParentIndex(index);
        if (!IsRoot(indexParent))
        {
            auto indexGrandParent = GetParentIndex(indexParent);
            if (IsIndexExists(heap, indexGrandParent) && heap[index] < heap[indexGrandParent])
            {
                std::swap(heap[index], heap[indexGrandParent]);
                PushUpMin(heap, indexGrandParent);
            }
        }
    }

    static void PushUpMax(std::vector<int>& heap, size_t index)
    {
        auto indexParent = GetParentIndex(index);
        if (!IsRoot(indexParent))
        {
            auto indexGrandParent = GetParentIndex(indexParent);
            if (IsIndexExists(heap, indexGrandParent) && heap[index] > heap[indexGrandParent])
            {
                std::swap(heap[index], heap[indexGrandParent]);
                PushUpMax(heap, indexGrandParent);
            }
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

    static inline bool IsMaxLevel(size_t index)
    {
        return (DepthFromIndex(index) % 2 == 0);
    }

    static inline bool IsRoot(size_t index)
    {
        return (index == 0);
    }

//    std::vector<int> _heap;
};

int main() 
{
    std::cout << "Hello world!" << std::endl;
//    std::vector<int> vec {8, 71, 41, 31, 10, 11, 16, 46, 51, 31, 21, 13};
    std::vector<int> vec {11, 71, 21, 31, 51, 8, 16, 46, 10, 31, 41, 13}; // 71 10 8 46 51 21 16 31 11 31 41 13
//    std::vector<int> vec {1, 2, 3, 4}; //12 2 1 9 11 6 7 8 4 10 5 3

//    MaxMinHeap heap(std::move(vec));
//    heap.PushDown(5);
    MaxMinHeap::BuildHeap(vec);
//    MaxMinHeap::PrintHeap(vec);
//    MaxMinHeap::Insert(vec, 40);
//    MaxMinHeap::Insert(vec, 40);
//    MaxMinHeap::Insert(vec, 10);
    MaxMinHeap::PrintHeap(vec);
//    MaxMinHeap::Delete(vec, 4 );
//    MaxMinHeap::PrintHeap(vec);

    int max, min;
    if (MaxMinHeap::ExtractMax(vec, max))
    {
        cout << "Max is " << max << endl;
        MaxMinHeap::PrintHeap(vec);
    }
    if (MaxMinHeap::ExtractMin(vec, min))
    {
        cout << "Min is " << min << endl;
        MaxMinHeap::PrintHeap(vec);
    }


    return 0;
}