#include <iostream>

using namespace std;

class doubleQueue
{
    int maxsize;
    int count;
    int* queue;
    int left;
    int right;

public:
    doubleQueue()
    {
        maxsize = 5;
        count = 0;
        queue = new int[maxsize];
        left = 0;
        right = 0;
    }

    bool IsEmpty()
    {
        return (count == 0);
    }

    bool IsFull()
    {
        return (count == maxsize);
    }

    void AddLeft(int x)
    {
        if (IsFull())
        {
            cout << "FULL" << endl;
            return;
        }
        left = (left - 1 + maxsize) % maxsize;
        queue[left] = x;
        count++;
        print();
    }

    void AddRight(int x)
    {
        if (IsFull())
        {
            cout << "FULL" << endl;
            return;
        }
        queue[right] = x;
        right = (right + 1) % maxsize;
        count++;
        print();
    }

    void DeleteLeft()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        left = (left + 1) % maxsize;
        count--;
        nonEmptyPrint();
    }

    void DeleteRight()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        right = (right - 1 + maxsize) % maxsize;
        count--;
        nonEmptyPrint();
    }

    void nonEmptyPrint()
    {
        int curr = left;
        for (int i = 0; i < count; i++)
        {
            cout << queue[curr] << " ";
            curr = (curr + 1) % maxsize;
        }
        cout << endl;
    }

    void print()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        int curr = left;
        for (int i = 0; i < count; i++)
        {
            cout << queue[curr] << " ";
            curr = (curr + 1) % maxsize;
        }
        cout << endl;
    }

    void Left()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << queue[left] << endl;
    }

    void Right()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << queue[(right - 1 + maxsize) % maxsize] << endl;
    }
};

int main()
{
    doubleQueue dq;
    string op;
    while (cin >> op && op != "End")
    {
        if (op == "IsEmpty")
        {
            cout << (dq.IsEmpty() ? "Yes" : "No") << endl;
        }
        else if (op == "IsFull")
        {
            cout << (dq.IsFull() ? "Yes" : "No") << endl;
        }
        else if (op == "Left")
        {
            dq.Left();
        }
        else if (op == "Right")
        {
            dq.Right();
        }
        else if (op == "AddLeft")
        {
            int x;
            cin >> x;
            dq.AddLeft(x);
        }
        else if (op == "AddRight")
        {
            int x;
            cin >> x;
            dq.AddRight(x);
        }
        else if (op == "DeleteLeft")
        {
            dq.DeleteLeft();
        }
        else if (op == "DeleteRight")
        {
            dq.DeleteRight();
        }
        else
        {
            cout << "WRONG";
        }
    }
    return 0;
}