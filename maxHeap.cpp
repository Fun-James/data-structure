#include <iostream>
#include <string>

using namespace std;
int N = 100;
template <class T>
class MaxHeap
{
    int maxSize, currentSize;
    T *heap;

public:
    MaxHeap(T maxElement, T minElement)
    {
        maxSize = 2 * N + 2;
        heap = new T[maxSize];
        heap[0] = maxElement; // 根节点从heap[1]开始，这样节点i的Leftchild是2i，rightchild是2i+1;节点j的父节点是i/2,int自动向下取整。
        for (int i = N + 1; i < maxSize; i++)
        {
            heap[i] = minElement;
        }
        currentSize = 0;
    }
    MaxHeap<T> &insert(const T &x)
    {
        if (currentSize == maxSize)
        {
            cout << "FULL,cannot insert!";
            return *this;
        }
        int i = ++currentSize;
        while (i != 1 && x > heap[i / 2])
        {
            heap[i] = heap[i / 2]; // 父节点下降
            i /= 2;
        }
        heap[i] = x;
        return *this;
    }
    MaxHeap<T> &deleteMax(T &x)
    {
        if (currentSize == 0)
        {
            cout << "Empty!";
            x = INT_MAX;
            return *this;
        }
        x = heap[1];
        int i = 1; // 从根节点开始
        while (i <= currentSize)
        {
            T childMax;
            int childMaxpos;
            if (heap[2 * i] > heap[2 * i + 1]) // 不用担心超出界限
            {
                childMax = heap[2 * i];
                childMaxpos = 2 * i;
            }
            else
            {
                childMax = heap[2 * i + 1];
                childMaxpos = 2 * i + 1;
            }

            if (heap[currentSize] >= childMax)
            {
                heap[i] = heap[currentSize];
                heap[currentSize] = heap[maxSize - 1];
                currentSize--;
                break;
            }
            else // 交换
            {
                heap[i] = childMax;
                i = childMaxpos;
            }
        }
        return *this;
    }
    void printHeap()
    {
        for (int i = 1; i <= currentSize; i++)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    MaxHeap<int> heap(100,0);

    // Insert elements
    heap.insert(10).insert(20).insert(15).insert(30).insert(5);
    cout << "Heap after inserts: ";
    heap.printHeap();

    // Delete max
    int maxElement;
    heap.deleteMax(maxElement);
    cout << "Deleted max element: " << maxElement << endl;

    cout << "Heap after delete: ";
    heap.printHeap();
    return 0;
}