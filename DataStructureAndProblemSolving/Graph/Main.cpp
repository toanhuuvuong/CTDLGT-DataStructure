#include"Graph.h"
#include<conio.h>

int main()
{
	//GRAPH G(4);

	//G.addEdge2D(0, 2);
	//G.addEdge1D(0, 1);
	//G.addEdge1D(1, 2);
	//G.addEdge1D(2, 3);
	//G.addEdge1D(3, 3);

	//G.display();

	//GRAPH TG(4);
	//G.transpose(TG);

	//TG.display();
	int graph[5][5] = { {0,2,0,0,9},
						{2,0,4,1,5},
						{0,4,0,8,0},
						{0,1,8,0,7},
						{9,5,0,7,0} };

	dijkstraSPT(graph, 5, 4);


	_getch();
	return 0;
}