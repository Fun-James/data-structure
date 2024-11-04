#include <iostream>
#include <fstream>
using namespace std;

void josephusArray(int n, int m)
{
    int *people = new int[n];
    bool *status = new bool[n];
    for (int i = 0; i < n; i++)
    {
        people[i] = i + 1;
        status[i] = false; // false没有出列，true出了列
    }
    int remaining = n;
    int index = 0; // 当前索引
    int count = 0; // 计数器
    while (remaining > 1)
    {
        if (status[index] == 0)
        {
            count++;
            if (count == m)
            {
                cout << people[index] << " ";
                status[index] = 1;
                count = 0;
                remaining--;
            }
        }
        index = (index + 1) % n;
    }
    for (int i = 0; i < n; ++i)
    {
        if (status[i] == 0)
        {
            cout << people[i] << endl;
            break;
        }
    }
}

class Node
{
public:
    Node *next;
    int number;
    bool status;
    Node(int num)
    {
        next = nullptr;
        status = false;
        number = num;
    }
};
class List
{
    Node *head;
    Node *tail;

public:
    List() { head = tail = nullptr; }
    void insert(int n)
    {
        Node *newnode = new Node(n);
        if (head == nullptr)
        {
            head = tail = newnode;
            return;
        }
        tail->next = newnode;
        tail = newnode;
        return;
    }
    void josephusList(int n, int m)
    {
        for (int i = 1; i <= n; i++)
        {
            insert(i);
        }
        int remaining = n;
        int index = 0; // 当前索引
        int count = 0; // 计数器
        Node *curr = head;
        while (remaining > 1)
        {
            if(curr->status==false)
            {
                count++;
                if(count==m)
                {
                    count=0;
                    curr->status=true;
                    cout<<curr->number<<" ";
                    remaining--;
                }
            }
            curr=curr->next;
            if(curr==nullptr)
            {
                curr=head;
            }
        }
        //输出最后一个
        curr=head;
        while(curr!=nullptr)
        {
            if(curr->status==false)
            {
                cout<<curr->number<<endl;
            }
            curr=curr->next;
        }
    }
};

int main()
{
    ifstream input("input.txt");
    int n, m;
    input >> n >> m;
    if (n < 3 || n > 100 || m < 1 || m > n)
    {
        cout << "WRONG" << endl;
    }
    else
    {
        josephusArray(n, m);
        List ls;
        ls.josephusList(n,m);
    }

    return 0;
}