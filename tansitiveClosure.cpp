#include<iostream>
#include <queue>
#include <stack>
using namespace std;

class graph//无向图
{
public:
	int** rec;//矩阵数组
	int** tc; //传递闭包
	int n;//用来记录节点数
	graph(int n);
	void  undirectedTC();//返回传递闭包，复杂性为O（n方），n为无向图的顶点数，采用构件标记策略
	void add(int i, int j);//添加边，因为是无向边，所以要对矩阵中的对称位置置1
	void print();//打印顶点连接关系
	bool hasPath(int source, int destination);
};
graph::graph(int n)
{
	this->n = n;
	rec = new int* [n + 1];
	tc = new int* [n + 1];
	for (int i = 1; i < n + 1; i++)
	{
		rec[i] = new int[n + 1] {}; //初始化为0
		tc[i] = new int[n + 1] {};
	}
}
void graph::add(int i, int j)
{
	if (i<1 || j<1 || i == j || i>n || j>n)
	{
		cout << "要添加的边不在范围内，或不允许添加自连边" << endl;
		return;
	}
	rec[i][j] = rec[j][i] = 1;
}
void graph::print()
{
	for (int row = 1; row < n + 1; row++)
	{
		cout << "与顶点" << row << "相连的有：";
		for (int col = 1; col < n + 1; col++)
		{
			if (rec[row][col] != 0)
			{
				cout << col << " ";
			}
		}
		cout << endl;
	}
}

void graph::undirectedTC()
{
	// 填充闭包矩阵
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (i != j) {
				int temp = rec[i][j];  // 保存原始连接状态
				rec[i][j] = rec[j][i] = 0;  // 临时删除直接连接

				if (hasPath(i, j)) {  // 如果删除直接连接后仍有路径
					tc[i][j] = tc[j][i] = 1;  // 加入闭包
				}

				rec[i][j] = rec[j][i] = temp;  // 恢复原始连接状态
			}
		}
	}
}

bool graph::hasPath(int source, int destination)
{
	if (source == destination) {
		return true;
	}
	bool* visited = new bool[n + 1];//标记
	for (int i = 0; i < n + 1; i++) {
		visited[i] = false;
	}
	queue<int> q;
	q.push(source);
	visited[source] = true;
	while (!q.empty()) {
		int index = q.front();
		q.pop();
		if (index == destination) {
			return true;
		}
		for (int j = 1; j < n + 1; j++) {
			if (rec[index][j] == 1 && !visited[j]) {
				q.push(j);
				visited[j] = true;
			}
		}
	}
	delete[] visited;
	return false;
}

int main()
{
	int n, i, j;

	cout << "请输入无向图中的节点数：";
	cin >> n;
	graph g(n);
	cout << "请依次输入图中无向边的起点和终点,当输入-1时停止:" << endl;
	cin >> i;
	while (i != -1)
	{
		cin >> j;
		g.add(i, j);
		cin >> i;
	}
	cout << "所形成的图中节点的连接关系:" << endl;
	g.print();
	cout << "该图所形成的闭包为：" << endl;
	g.undirectedTC();
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			cout << g.tc[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}