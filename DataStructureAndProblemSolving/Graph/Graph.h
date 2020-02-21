#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<iostream>
#include<iomanip>
#include<vector>
#include<list>
#include<minmax.h>

class GRAPH
{
private:
	std::vector<int>* m_graph;
	int m_vertices;

	void DFSUntil(int src, bool* visited)
	{
		visited[src] = true;
		std::cout << src << "\t";

		std::vector<int>::iterator it;
		for (it = m_graph[src].begin(); it != m_graph[src].end(); it++)
		{
			if (visited[*it] == false)
				DFSUntil(*it, visited);
		}
	}
public:
	GRAPH() { m_graph = NULL; }
	GRAPH(const int &vertices) : m_vertices(vertices) { m_graph = new std::vector<int>[vertices]; }
	~GRAPH() { if (m_graph) delete[] m_graph; }

	void addEdge1D(const int &u, const int &v)
	{
		m_graph[u].push_back(v);
	}
	void addEdge2D(const int &u, const int &v)
	{
		m_graph[u].push_back(v);
		m_graph[v].push_back(u);
	}

	void display()
	{
		for (int i = 0; i < m_vertices; i++)
		{
			std::cout << "Vertex " << i << ":" << std::endl << "Head";
			for (int j = 0; j < m_graph[i].size(); j++)
				std::cout << " -> " << m_graph[i][j];
			std::cout << std::endl << std::endl;
		}
	}
	void BFS(int src)
	{
		bool* visited = new bool[m_vertices];
		std::list<int> queue;
		// Khởi tạo
		for (int i = 0; i < m_vertices; i++)
			visited[i] = false;
		queue.push_back(src);
		visited[src] = true;

		std::vector<int>::iterator it;
		while (!queue.empty())
		{
			src = queue.front();
			std::cout << src << "\t";
			queue.pop_front();

			for (it = m_graph[src].begin(); it != m_graph[src].end(); it++)
			{
				if (visited[*it] == false)
				{
					queue.push_back(*it);
					visited[*it] = true;
				}
			}
		}

		delete[] visited;
	}
	void DFS(int src)
	{
		bool* visited = new bool[m_vertices];
		// Khởi tạo
		for (int i = 0; i < m_vertices; i++)
			visited[i] = false;

		DFSUntil(src, visited);

		delete[] visited;
	}
	void DFS()
	{
		bool* visited = new bool[m_vertices];
		// Khởi tạo
		for (int i = 0; i < m_vertices; i++)
			visited[i] = false;
		// Duyệt từng đỉnh là src
		for (int i = 0; i < m_vertices; i++)
		{
			if (visited[i] == false)
				DFSUntil(i, visited);
		}

		delete[] visited;
	}
	void transpose(GRAPH &transposeGraph)
	{
		for (int i = 0; i < m_vertices; i++)
		{
			for (int j = 0; j < m_graph[i].size(); j++)
				transposeGraph.addEdge1D(m_graph[i][j], i);
		}
	}
};
// =========================================================== PRIM MIN SPANNING TREE ===========================================================
// Tìm key có weight nhỏ nhất và chưa được đánh dấu
int minIndexKey(int* key, bool* mstSet, const int &nVertice)
{
	int min = INT_MAX, minIndex = -1;
	for (int i = 0; i < nVertice; i++)
	{
		if (mstSet[i] == false && key[i] <= min)
		{
			minIndex = i;
			min = key[i];
		}
	}
	return minIndex;
}
// In cây khung tối tiểu
void displayMST(int graph[5][5], int* parent, const int &nVertice)
{
	std::cout << "=========================================== DISPLAY 1 ===========================================" << std::endl;
	std::cout << std::setw(10) << std::left << "Edge";
	std::cout << std::setw(10) << std::left << "Weight" << std::endl << std::endl;
	for (int i = 1; i < nVertice; i++)
	{
		std::cout << std::setw(1) << std::left << parent[i];
		std::cout << std::setw(2) << std::left << "--";
		std::cout << std::setw(7) << std::left << i;
		std::cout << std::setw(10) << std::left << graph[i][parent[i]] << std::endl;
	}
	std::cout << "=========================================== DISPLAY 2 ===========================================" << std::endl;
	int temp[100][100], i, j;
	for (i = 0; i < nVertice; i++)
	{
		for (j = 0; j < nVertice; j++)
			temp[i][j] = 0;
	}
	for (i = 0; i < nVertice; i++)
	{
		temp[i][parent[i]] = graph[i][parent[i]];
		temp[parent[i]][i] = graph[parent[i]][i];
	}
	for (i = 0; i < nVertice; i++)
	{
		for (j = 0; j < nVertice; j++)
			std::cout << temp[i][j] << "\t";
		std::cout << std::endl;
	}
}
// Thuật toán primMST
void primMST(int graph[5][5], const int &nVertice)
{
	int* parent = new int[nVertice];
	int* key = new int[nVertice];
	bool* mstSet = new bool[nVertice];
	// Khởi tạo cho key và mstSet
	for (int i = 0; i < nVertice; i++)
	{
		key[i] = INT_MAX;
		mstSet[i] = false;
	}
	// Luôn cho đỉnh 0 là đỉnh bắt đầu
	key[0] = 0;
	parent[0] = -1;
	// Thuật toán
	int minIndex;
	for (int i = 0; i < nVertice - 1; i++)
	{
		minIndex = minIndexKey(key, mstSet, nVertice); // Tìm min weight
		mstSet[minIndex] = true; // Đánh dấu
		for (int j = 0; j < nVertice; j++)
		{
			if (graph[minIndex][j] && mstSet[j] == false && graph[minIndex][j] < key[j])
			{
				parent[j] = minIndex;
				key[j] = graph[minIndex][j]; // Đỉnh nào có liên kết với đỉnh minIndex đều cập nhật lại trọng số
			}
		}
	}
	displayMST(graph, parent, nVertice);

	delete[] parent;
	delete[] key;
	delete[] mstSet;
}
// ========================================================= DIIJKSTRA SORTEST PATH TREE =========================================================
int indexMinDistance(int* dist, bool* sptSet, const int &V)
{
	int Min = INT_MAX, iMin = -1;
	for (int i = 0; i < V; i++)
	{
		if (sptSet[i] == false && dist[i] <= Min)
			Min = dist[i], iMin = i;
	}
	return iMin;
}
void displaySPT(int* parent, int* dist, const int &V, const int &src)
{
	for (int i = 0; i < V; i++)
	{
		std::cout << "Distance: " << dist[i] << std::endl;
		int dest = i;
		while (dest != src)
		{
			std::cout << dest << " <- ";
			dest = parent[dest];
		}
		std::cout << src << std::endl << "--------------------------------------------" << std::endl;
	}
}
void dijkstraSPT(int graph[5][5], const int &V, const int &src)
{
	int *dist = new int[V], *parent = new int[V];
	bool *sptSet = new bool[V];
	// Khởi động
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, parent[i] = -1, sptSet[i] = false;
	dist[src] = 0;
	// B3
	for (int i = 1; i < V; i++)
	{
		int iMin = indexMinDistance(dist, sptSet, V);
		sptSet[iMin] = true;
		for (int j = 0; j < V; j++)
		{
			if (sptSet[j] == false && graph[iMin][j] && dist[j] > dist[iMin] + graph[iMin][j])
				dist[j] = dist[iMin] + graph[iMin][j], parent[j] = iMin;
		}
	}
	displaySPT(parent, dist, V, src);

	delete[] dist;
	delete[] parent;
	delete[] sptSet;
}


#endif