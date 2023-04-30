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
            Heapify(heap, i);
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

    static void Heapify(
            std::vector<int>& heap,
            size_t index)
    {
        static std::greater_equal<int> bigger;
        static std::less_equal<int> lesser;

        auto level = DepthFromIndex(index);
        if (level % 2 == 0)
        {
            PushDown(heap,
                    index,
                    bigger);
        }
        else
        {
            PushDown(heap,
                    index,
                    lesser);
        }
    }

    static void Insert(std::vector<int>& heap, int key)
    {
        heap.push_back(key);
        PushUp(heap, (heap.size() - 1));
    }

    static bool Delete(std::vector<int>& heap, size_t index)
    {
        auto retValue{true};
        if (IsIndexExists(heap, index))
        {
            std::swap(heap[index], heap[heap.size() - 1]);
            heap.pop_back();
            Heapify(heap, index);
            PushUp(heap,index);
        }
        else
        {
            cout << "Index Is Not In The Heap\n";
            retValue = false;
        }

        return retValue;
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
            Heapify(heap, 0);
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
            Heapify(heap, minIndex);
        }
        else
        {
            cout << "Cannot Extract Min, Heap Is Empty" << endl;
            retValue = false;
        }

        return retValue;
    }

private:
    static void PushDown(
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
        }

        if (isGrandChild)
        {
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

                    Heapify(heap, smallestIndex);
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
};


// TODO Change function names
// TODO make insert generic

int main() 
{
    while (true)
    {
        cout << "Welcome to Ron Potashnik Max Min Heap\n";
        cout << "Please enter your array size\n";
        int inputSize;
        cin >> inputSize;
        if (!cin)
        {
            cout << "Please enter a valid number\n";
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> inputSize;
        }

        if (!cin)
        {
            cout << "Next time please enter valid number\n";
            break;
        }

        if (inputSize <= 0)
        {
            cout << "Please run the program again with size larger then 0\n";
            break;
        }

        auto validInput{true};
        std::vector<int> inputVec;
        cout << "Please enter " << inputSize << " numbers\n";
        for (auto i = 0; i < inputSize; ++i)
        {
            int inputNumber;
            cin >> inputNumber;
            if (!cin)
            {
                cout << "Next time please enter valid number\n";
                validInput = false;
                break;
            }

            inputVec.push_back(inputNumber);
        }

        if (!validInput)
        {
            break;
        }

        cout << "\nYour input array is:\n";
        MaxMinHeap::PrintHeap(inputVec);

        cout << "\nPlease enter:\n"
                "1 - if you want to build MaxMin Heap from your array\n"
                "Any other value for for exit\n";
        int inputSelect;
        cin >> inputSelect;
        if (inputSelect == 1)
        {
            MaxMinHeap::BuildHeap(inputVec);
            while (true)
            {
                cout << "\nYour MaxMin Heap is:\n";
                MaxMinHeap::PrintHeap(inputVec);

                cout << "\nPlease enter:\n"
                        "1 - Heap Extract Max\n"
                        "2 - Heap Extract Min\n"
                        "3 - Heap Insert\n"
                        "4 - Heap Delete\n"
                        "5 - Heap Heapify\n"
                        "Any other value for for exit\n";
                cin >> inputSelect;

                // Heap Extract Max
                if (inputSelect == 1)
                {
                    cout << "\nYou selected Heap Extract Max\n";
                    int max;
                    if (MaxMinHeap::ExtractMax(inputVec, max))
                    {
                        cout << "Max value was " << max << endl;
                    }
                    else
                    {
                        cout << "Please Try Again\n";
                    }

                    continue;
                }
                // Heap Extract Min
                else if (inputSelect == 2)
                {
                    cout << "\nYou selected Heap Extract Min\n";
                    int min;
                    if (MaxMinHeap::ExtractMin(inputVec, min))
                    {
                        cout << "Min value was " << min << endl;
                    }
                    else
                    {
                        cout << "Please Try Again\n";
                    }

                    continue;
                }
                //Heap Insert
                else if (inputSelect == 3)
                {
                    cout << "\nYou selected Heap Insert\n";
                    cout << "Please Insert The Value You Want To Insert\n";
                    int inputInsert;
                    cin >> inputInsert;
                    if (!cin)
                    {
                        cout << "Next time please enter valid number\n";
                        break;
                    }
                    MaxMinHeap::Insert(inputVec, inputInsert);
                    continue;
                }
                //Heap Delete
                else if (inputSelect == 4)
                {
                    cout << "\nYou selected Heap Delete\n";
                    cout << "Please Insert The Index You Want To Delete - Range From 0 To " << inputVec.size() - 1 << endl;
                    int inputIndex;
                    cin >> inputIndex;
                    if (!cin)
                    {
                        cout << "Next time please enter valid number\n";
                        break;
                    }
                    if (!MaxMinHeap::Delete(inputVec, inputIndex))
                    {
                        if (inputVec.size() == 0)
                        {
                            cout << "The Heap Is Empty\n";
                        }
                        cout << "Please Try Again\n";
                    }

                    continue;
                }
                //Heap Heapify
                else if (inputSelect == 5)
                {
                    cout << "\nYou selected Heap Heapify\n";
                    cout << "Please Insert The Index You Want To Heapify - Range From 0 To " << inputVec.size() - 1 << endl;
                    int inputIndex;
                    cin >> inputIndex;
                    if (!cin)
                    {
                        cout << "Next time please enter valid number\n";
                        break;
                    }
                    if (!inputIndex >= inputVec.size())
                    {
                        MaxMinHeap::Heapify(inputVec, inputIndex);
                    }
                    else
                    {
                        cout << "The index " << inputIndex << " is not in the heap\n";
                        cout << "Please Try Again\n";
                    }

                    continue;
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

    cout << "Goodbye!\n";
    return 0;
}