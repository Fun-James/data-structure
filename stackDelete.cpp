#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class arrayStack{
    int top;
    int length;
    T *stack;

public:
    arrayStack(int capacity)
    {
        top = -1;
        length = capacity;
        stack = new T[capacity];
    }
    T pop()
    {
        if (top == -1)
        {
            throw string("empty stack");
        }
        T temp = stack[top];
        stack[top--].~T();
        return temp;
    }
    void push(T element)
    {
        if (top == length - 1)
        {
            cout << "full";
            return;
        }
        stack[++top] = element;
    }
    void display()
    {
        int index = top;
        while (index != 0)
        {
            cout << stack[index] << " ";
            index--;
        }
        cout << stack[0] << endl;
    }
    template <typename U>
    friend void delete_all(arrayStack<U> &s, U x);
};

template <typename T>
void delete_all(arrayStack<T> &s, T x)
{
    if (s.top == -1) {
        cout << "Stack is empty" << endl;
        return;
    }
    int currLength = s.top + 1;
    T *newarray = new T[s.length];
    int count = 0;
    for (int i = 0; i < currLength; i++)
    {
        if (s.stack[i] != x)
        {
            newarray[count++] = s.stack[i];
        }
    }
    delete[]s.stack;
    s.top=count-1;
    s.stack = newarray;
    return;
}

int main()
{
    ifstream infile("input.txt");
    arrayStack<char> st(10);
    char x;
    infile >> x; 
    char temp;  
    while (infile >> temp)
    {
        st.push(temp);
    }
    delete_all(st, x);
    st.display();
    return 0;
}