#include <iostream>
#include <fstream>

using namespace std;

void josephusArray(int n,int m)
{
    int* people=new int[n];
    bool* status=new bool[n];
    for(int i=0;i<n;i++)
    {
        people[i]=i+1;
    }
    int remaining=n;
    int index;//当前索引
    int count;//计数器


}

int main()
{
    ifstream infile("input.txt");
    int n,m;
    cin>>n>>m;
    if (n < 3 || n > 100 || m < 1 || m > n) 
    {
        cout << "WRONG" <<endl;
    }
    else 
    {
        josephusArray(n, m);
    }
    return 0;
}