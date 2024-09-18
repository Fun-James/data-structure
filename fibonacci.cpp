#include<iostream>
#include<fstream>
using namespace std;

long long fib[90] = {};

long long fibonacci(int n)
{
	//先判断是否已计算
	if (fib[n - 1] != 0)
	{
		return fib[n - 1];
	}
	//递归
	if (n == 0||n==1)
	{
		fib[0] = fib[1] = 1;
		return 1;
	}
	return fib[n-1]=fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	int n;
	ifstream infile("input.txt");
	if (!infile.is_open())
	{	// 检查文件是否成功打开
		cerr << "Error opening file." << endl;
		return 1;
	}
	infile >> n;
	if (n >= 0 && n <= 90)
	{
		cout << fibonacci(n)<<endl;
	}
	else
	{
		cout << "WRONG"<<endl;
	}
	
	

	return 0;
}