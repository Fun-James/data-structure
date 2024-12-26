#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

// 定义一个结构体来存储边的信息
struct Edge
{
	int destination; // 目标顶点
	int weight;		 // 权重
	Edge(int dest, int w) : destination(dest), weight(w) {}
};

class Graph
{
private:
	int V;					// 顶点数
	bool directed;			// 是否为有向图
	vector<list<Edge>> adj; // 邻接表 (存储Edge结构体)

public:
	// 构造函数
	Graph(int vertices, bool isDirected = false) : V(vertices), directed(isDirected)
	{
		adj.resize(vertices);
	}

	// 添加边
	void addEdge(int v, int w, int weight = 1)
	{
		adj[v].push_back(Edge(w, weight));
		if (!directed)
		{
			adj[w].push_back(Edge(v, weight));
		}
	}

	// 删除边
	void removeEdge(int v, int w)
	{
		adj[v].remove_if([w](const Edge& e)
			{ return e.destination == w; });
		if (!directed)
		{
			adj[w].remove_if([v](const Edge& e)
				{ return e.destination == v; });
		}
	}

	// 广度优先搜索
	void BFS(int start)
	{
		vector<bool> visited(V, false);
		queue<int> queue;

		visited[start] = true;
		queue.push(start);

		while (!queue.empty())
		{
			int v = queue.front();
			cout << v << " ";
			queue.pop();

			for (const auto& e : adj[v])
			{
				int w = e.destination;
				if (!visited[w])
				{
					visited[w] = true;
					queue.push(w);
				}
			}
		}
		cout << endl;
	}

	// 深度优先搜索
	void DFS(int start)
	{
		vector<bool> visited(V, false);
		DFSUtil(start, visited);
		cout << endl;
	}

	// 获取顶点数
	int getVertexCount() const
	{
		return V;
	}

	// 检查边是否存在
	bool hasEdge(int v, int w) const
	{
		for (const auto& e : adj[v])
		{
			if (e.destination == w)
				return true;
		}
		return false;
	}

	// 打印图
	void printGraph() const
	{
		for (int v = 0; v < V; v++)
		{
			cout << "顶点 " << v << " 的邻接表:\n";
			for (const auto& e : adj[v])
			{
				cout << "-> " << e.destination << " (权重: " << e.weight << ")\n";
			}
			cout << endl;
		}
	}

	vector<int> shortestPath(int start, int end)
	{
		if (start < 0 || start >= V || end < 0 || end >= V)
		{
			return vector<int>();
		}

		vector<bool> visited(V, false);
		vector<int> predecessor(V, -1);
		queue<int> queue;

		visited[start] = true;
		queue.push(start);

		bool found = false;
		while (!queue.empty() && !found)
		{
			int v = queue.front();
			queue.pop();

			for (const auto& e : adj[v])
			{
				int w = e.destination;
				if (!visited[w])
				{
					visited[w] = true;
					predecessor[w] = v;
					queue.push(w);
					if (w == end)
					{
						found = true;
						break;
					}
				}
			}
		}
		// 如果没有找到路径
		if (!found)
		{
			return vector<int>();
		}
		// 重建路径
		vector<int> path;
		for (int v = end; v != -1; v = predecessor[v])
		{
			path.push_back(v);
		}
		reverse(path.begin(), path.end());
		return path;
	}

private:
	// DFS的递归辅助函数
	void DFSUtil(int v, vector<bool>& visited)
	{
		visited[v] = true;
		cout << v << " ";

		for (const auto& e : adj[v])
		{
			int w = e.destination;
			if (!visited[w])
			{
				DFSUtil(w, visited);
			}
		}
	}
};

// 使用示例
int main()
{
	// 创建一个具有6个顶点的无向图
	Graph g(5);

	// 添加边
	g.addEdge(0, 1);
	g.addEdge(1, 4);
	g.addEdge(0, 2);
	g.addEdge(2, 4);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	int start, end;
	cout << "请输入起始顶点: ";
	cin >> start;
	cout << "请输入目标顶点: ";
	cin >> end;

	vector<int> path = g.shortestPath(start, end);

	if (path.empty())
	{
		cout << "不存在从顶点 " << start << " 到顶点 " << end << " 的路径" << endl;
	}
	else
	{
		cout << "最短路径: ";
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i];
			if (i < path.size() - 1)
			{
				cout << " -> ";
			}
		}
		cout << endl;
	}

	return 0;
}
