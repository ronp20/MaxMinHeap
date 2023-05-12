// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

class MaxMinHeap
{
public:
    MaxMinHeap() = default;
    MaxMinHeap(const MaxMinHeap&) = delete;
    MaxMinHeap(MaxMinHeap&&) = delete;
    MaxMinHeap& operator=(MaxMinHeap&) = delete;
    MaxMinHeap& operator=(MaxMinHeap&&) = delete;

    /**
     * BuildHeap - Build max min heap from an unordered vector
     * The function is looping from last node to the root and Heapify each node
     * @param heap - an unsorted array
     */
    void BuildHeap(const std::vector<int>& heap)
    {
        _heap = heap;
        int heapSize = static_cast<int>(_heap.size());
        for (auto i = (heapSize / 2); i >= 0; --i)
        {
            Heapify(i);
        }
    }

    /**
     * PrintHeap - Printing the heap - for debug session
     * @param heap
     */
    void PrintHeap() const
    {
        for (auto i = 0; i < _heap.size(); ++i)
        {
            std::cout << _heap[i] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * Heapify - Placed an index in the heap vector using PushDown
     * @param index
     */
    void Heapify(size_t index)
    {
        if (IsMaxLevel(index))
        {
            PushDown(index, maxComparator);
        }
        else
        {
            PushDown(index, minComparator);
        }
    }

    /**
     * Insert - Insert a key in an ordered heap
     * @param heap
     * @param key
     */
    void Insert(int key)
    {
        _heap.push_back(key);
        PushUp((_heap.size() - 1));
    }

    /**
     * Delete - Delete an index from an ordered heap
     * @param heap
     * @param index
     * @return false if index is not in the heap
     */
    bool Delete(size_t index)
    {
        auto retValue{true};

        if(!_heap.empty())
        {
            if (IsIndexExists(index))
            {
                _heap[index] = _heap[0] + 1;
                PushUp(index);
                Heapify(index);
                int max;
                ExtractMax(max);
            }
            else
            {
                std::cout << "Index Is Not In The Heap\n";
                retValue = false;
            }
        }
        else
        {
            std::cout << "Heap is empty\n";
            retValue = false;
        }

        return retValue;
    }

    /**
     * ExtractMax - Extract max value from an ordered heap
     * @param heap
     * @param max
     * @return false if the heap is empty
     */
    bool ExtractMax(int& max)
    {
        auto retValue{true};
        if (_heap.size() != 0)
        {
            max = _heap[0];
            std::swap(_heap[0], _heap[_heap.size() - 1]);
            _heap.pop_back();
            Heapify(0);
        }
        else
        {
            std::cout << "Cannot Extract Max, Heap Is Empty" << std::endl;
            retValue = false;
        }

        return retValue;
    }

    /**
     * ExtractMin - Extract min value from an ordered heap
     * @param heap
     * @param min
     * @return false if the heap is empty
     */
    bool ExtractMin(int& min)
    {
        auto retValue{true};
        auto heapSize = _heap.size();

        if (heapSize != 0)
        {
            size_t minIndex;

            if (heapSize == 1)
            {
                minIndex = 0;
                min = _heap[0];
            }
            else if (heapSize == 2)
            {
                minIndex = 1;
                min = _heap[1];
            }
            else
            {
                if (_heap[1] < _heap[2])
                {
                    minIndex = 1;
                    min = _heap[1];
                }
                else
                {
                    minIndex = 2;
                    min = _heap[2];
                }
            }

            std::cout << "Min index " << minIndex << std::endl;
            std::swap(_heap[minIndex], _heap[_heap.size() - 1]);
            _heap.pop_back();
            Heapify(minIndex);
        }
        else
        {
            std::cout << "Cannot Extract Min, Heap Is Empty" << std::endl;
            retValue = false;
        }

        return retValue;
    }

    inline size_t GetSize() const
    {
        return _heap.size();
    }

    // For debug
    bool IsHeapValid() const
    {
        size_t i = 0;
        while(i < _heap.size())
        {
            auto isMaxLevel = IsMaxLevel(i);
            for (auto leftChildIndex = i; leftChildIndex < _heap.size(); leftChildIndex = GetLeftChildIndex(leftChildIndex))
            {
                if (isMaxLevel)
                {
                    if (_heap[i] < _heap[leftChildIndex])
                    {
                        std::cout << "Heap is not valid Index " << i << " is smaller then index " << leftChildIndex << std::endl;
                        return false;
                    }
                }
                else
                {
                    if (_heap[i] > _heap[leftChildIndex])
                    {
                        std::cout << "Heap is not valid Index " << i << " is bigger then index " << leftChildIndex << std::endl;
                        return false;
                    }
                }
            }

            for (auto rightChildIndex = i; rightChildIndex < _heap.size(); rightChildIndex = GetRightChildIndex(rightChildIndex))
            {
                if (isMaxLevel)
                {
                    if (_heap[i] < _heap[rightChildIndex])
                    {
                        std::cout << "Heap is not valid Index " << i << " is smaller then index " << rightChildIndex << std::endl;
                        return false;
                    }
                }
                else
                {
                    if (_heap[i] > _heap[rightChildIndex])
                    {
                        std::cout << "Heap is not valid Index " << i << " is bigger then index " << rightChildIndex << std::endl;
                        return false;
                    }
                }
            }

            ++i;
        }

        return  true;

    }

private:
    /**
     * PushDown - Pushing down the index to his placed using comparator function in an ordered heap
     * @param heap
     * @param index
     * @param comparator
     */
    void PushDown(size_t index, std::function<bool (int, int)> comparator)
    {
        if (!IsIndexExists(index))
        {
            return;
        }

        size_t leftChild, rightChild;

        leftChild = GetLeftChildIndex(index);

        rightChild = GetRightChildIndex(index);

        //Check if the node have child's
        if (!IsIndexExists(leftChild) &&
            !IsIndexExists(rightChild))
        {
            return;
        }

        // Find the smallest child or grandchild
        bool isGrandChild = false;
        size_t comparedIndex = index;

        if (IsIndexExists(leftChild))
        {
            comparedIndex = comparator(_heap[leftChild], _heap[index]) ?
                            leftChild :
                            index;

            if (IsIndexExists(rightChild))
            {
                comparedIndex = comparator(_heap[rightChild], _heap[comparedIndex]) ?
                                rightChild :
                                comparedIndex;
            }

            size_t leftGrandChildLeft, leftGrandChildRight;
            leftGrandChildLeft = GetLeftChildIndex( leftChild);

            leftGrandChildRight = GetRightChildIndex(leftChild);


            if (IsIndexExists(leftGrandChildLeft))
            {
                if (comparator(_heap[leftGrandChildLeft], _heap[comparedIndex]))
                {
                    comparedIndex = leftGrandChildLeft;
                    isGrandChild = true;
                }

            }
            if (IsIndexExists(leftGrandChildRight))
            {
                if (comparator(_heap[leftGrandChildRight], _heap[comparedIndex]))
                {
                    comparedIndex = leftGrandChildRight;
                    isGrandChild = true;
                }
            }

            size_t rightGrandChildLeft, rightGrandChildRight;
            rightGrandChildLeft = GetLeftChildIndex(rightChild);

            rightGrandChildRight = GetRightChildIndex(rightChild);

            if (IsIndexExists(rightGrandChildLeft))
            {
                if (comparator(_heap[rightGrandChildLeft], _heap[comparedIndex]))
                {
                    comparedIndex = rightGrandChildLeft;
                    isGrandChild = true;
                }
            }

            if (IsIndexExists(rightGrandChildRight))
            {
                if (comparator(_heap[rightGrandChildRight], _heap[comparedIndex]))
                {
                    comparedIndex = rightGrandChildRight;
                    isGrandChild = true;
                }
            }
        }

        if (isGrandChild)
        {
            if(comparator(_heap[comparedIndex], _heap[index]))
            {
                std::swap(_heap[comparedIndex], _heap[index]);

                if (comparedIndex != 0)
                {
                    auto parentComparedIndex = GetParentIndex(comparedIndex);

                    if (!comparator(_heap[comparedIndex], _heap[parentComparedIndex]))
                    {
                        std::swap(_heap[comparedIndex], _heap[parentComparedIndex]);
                    }

                    Heapify(comparedIndex);
                }

            }
        }
        else if(comparator(_heap[comparedIndex], _heap[index]))
        {
            std::swap(_heap[comparedIndex], _heap[index]);
        }
    }

    /**
     * PushUp - Push up the index to his placed using comparator function in an ordered heap
     * @param heap
     * @param index
     */
    void PushUp(size_t index)
    {
        if (!IsRoot(index))
        {
            auto indexParent = GetParentIndex(index);

            if (IsMaxLevel(index))
            {
                if (_heap[index] < _heap[indexParent])
                {
                    std::swap(_heap[index], _heap[indexParent]);
                    BubbleUp(indexParent, minComparator);
                }
                else
                {
                    BubbleUp(index, maxComparator);
                }
            }
            else
            {
                if (_heap[index] > _heap[indexParent])
                {
                    std::swap(_heap[index], _heap[indexParent]);
                    BubbleUp(indexParent, maxComparator);

                }
                else
                {
                    BubbleUp(index, minComparator);
                }
            }
        }
    }

    void BubbleUp(size_t index, std::function<bool (int, int)> comparator)
    {
        auto indexParent = GetParentIndex(index);
        if (!IsRoot(indexParent))
        {
            auto indexGrandParent = GetParentIndex(indexParent);
            if (IsIndexExists(indexGrandParent) && comparator(_heap[index], _heap[indexGrandParent]))
            {
                std::swap(_heap[index], _heap[indexGrandParent]);
                BubbleUp(indexGrandParent, comparator);
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

    static inline size_t GetLeftChildIndex(size_t index)
    {
        return ((index * 2) + 1);
    }

    static inline size_t GetRightChildIndex(size_t index)
    {
        return ((index * 2) + 2);
    }

    bool inline IsIndexExists(size_t index) const
    {
        return (index < _heap.size());
    }

    static inline bool IsMaxLevel(size_t index)
    {
        return (DepthFromIndex(index) % 2 == 0);
    }

    static inline bool IsRoot(size_t index)
    {
        return (index == 0);
    }

    std::vector<int> _heap;
    static std::greater_equal<int> maxComparator;
    static std::less_equal<int> minComparator;
};

std::greater_equal<int> MaxMinHeap::maxComparator;
std::less_equal<int> MaxMinHeap::minComparator;


//////////////////////////// Menu Functions //////////////////////////////////
void HeapExtractMaxSelection(MaxMinHeap& heap)
{
    std::cout << "\nYou selected Heap Extract Max\n";
    int max;
    if (heap.ExtractMax(max))
    {
        std::cout << "Max value was " << max << std::endl;
    }
    else
    {
        std::cout << "Extract Max failed, please Try Again\n";
    }
}

void HeapExtractMinSelection(MaxMinHeap& heap)
{
    std::cout << "\nYou selected Heap Extract Min\n";
    int min;
    if (heap.ExtractMin(min))
    {
        std::cout << "Min value was " << min << std::endl;
    }
    else
    {
        std::cout << "Extract Min failed, please Try Again\n";
    }
}

void HeapInsertSelection(MaxMinHeap& heap)
{
    std::cout << "\nYou selected Heap Insert\n";
    std::cout << "Please Insert The Value You Want To Insert\n";
    int inputInsert;
    std::cin >> inputInsert;
    if (!std::cin)
    {
        std::cout << "Next time please enter valid number\n";
        return;
    }
    heap.Insert(inputInsert);
}

void HeapDeleteSelection(MaxMinHeap& heap)
{
    std::cout << "\nYou selected Heap Delete\n";
    std::cout << "Please Insert The Index You Want To Delete - Range From 0 To " << heap.GetSize() - 1 << std::endl;
    int inputIndex;
    std::cin >> inputIndex;
    if (!std::cin)
    {
        std::cout << "Next time please enter valid number\n";
        return;
    }
    if (!heap.Delete(inputIndex))
    {
        std::cout << "Failed to delete, please Try Again\n";
    }
}

bool HeapBuildSelection(MaxMinHeap& heap, std::vector<int>& outputVector)
{
    std::cout << "Please enter your array size\n";
    int inputSize;
    std::cin >> inputSize;
    if (!std::cin)
    {
        std::cout << "Please enter a valid number\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> inputSize;
    }

    if (!std::cin)
    {
        std::cout << "Next time please enter valid number\n";
        return false;
    }

    if (inputSize <= 0)
    {
        std::cout << "Please run the program again with size larger then 0\n";
        return false;
    }

    std::vector<int> inputVec;
    std::cout << "Please enter " << inputSize << " numbers\n";
    for (auto i = 0; i < inputSize; ++i)
    {
        int inputNumber;
        std::cin >> inputNumber;
        if (!std::cin)
        {
            std::cout << "Next time please enter valid number\n";
            return false;
        }

        inputVec.push_back(inputNumber);
    }

    std::cout << "\nYour input array is:\n";
    for (const auto& elem: inputVec)
    {
        std::cout << elem << " ";
    }

    std::cout << std::endl;

    heap.PrintHeap();

    heap.BuildHeap(inputVec);

    return true;
}

int main()
{
    while (true)
    {
        std::cout << "Welcome to Ron Potashnik Max Min Heap\n";

        MaxMinHeap heap;
        std::vector<int> inputVec;

        if(!HeapBuildSelection(heap, inputVec))
        {
            break;
        }

        std::cout << "\nPlease enter:\n"
                "1 - if you want to build MaxMin Heap from your array\n"
                "Any other value for for exit\n";

        int inputSelect;
        std::cin >> inputSelect;
        if (inputSelect == 1)
        {
            while (true)
            {
                std::cout << "\nYour MaxMin Heap is:\n";
                heap.PrintHeap();
                std::cout << "\nPlease enter:\n"
                        "1 - Heap Extract Max\n"
                        "2 - Heap Extract Min\n"
                        "3 - Heap Insert\n"
                        "4 - Heap Delete\n"
                        "5 - Heap Build\n"
                        "Any other value for for exit\n";
                std::cin >> inputSelect;

                // Heap Extract Max
                if (inputSelect == 1)
                {
                    HeapExtractMaxSelection(heap);
                }
                // Heap Extract Min
                else if (inputSelect == 2)
                {
                    HeapExtractMinSelection(heap);
                }
                //Heap Insert
                else if (inputSelect == 3)
                {
                    HeapInsertSelection(heap);
                }
                //Heap Delete
                else if (inputSelect == 4)
                {
                    HeapDeleteSelection(heap);
                }
                //Heap Build
                else if (inputSelect == 5)
                {
                    std::cout << "\nYou selected Heap Build\n";
                    if (!HeapBuildSelection(heap, inputVec))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            break;
        }
        else
        {
            break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}