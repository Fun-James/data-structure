#include<iostream>
#include<fstream>
using namespace std;

bool subset[26];
char map[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool check(int k,int n)
{
	bool have=false;
	for(int i=k;i<n;i++)
	{
		if(subset[i]==true)
		{
			have=true;
			return true;
		}
	} 
	return false;
}

void child(int n, bool subset[], int index) 
{
	//打印当前已经选择的子集
    for (int i = 0; i < n; i++) 
	{
        if (subset[i]) {
            cout << map[i];

			//处理空格情况
			if (check(i,n)==true)//后面还有元素
			{
				cout << " ";
			}
        }
    }
    cout << endl;

    // 递归地添加后续的元素
    for (int i = index; i < n; i++) {

        subset[i] = true;        // 选择
        child(n, subset, i + 1); // 递归处理后续元素

        subset[i] = false;       // 撤销选择,不影响下一层
    }
}


int main() {
    int n;
    ifstream infile("input.txt");
    if (!infile.is_open())
	{  
        cerr << "Error opening file." << endl;
        return 1;
    }
    infile >> n;
    if (n >= 1 && n <= 26) 
	{
        child(n, subset, 0); 
    } 
	else
	{
        cout << "WRONG" << endl;
    }

    return 0;
}