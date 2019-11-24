#include <bits/stdc++.h>

using namespace std;

#include "Graph.hpp"
#include "Heap.hpp"
#include "Max_BW_Path_without_heap.hpp"
#include "Max_BW_Path_with_heap.hpp"
//#include "Kruskal.hpp"

int main()
{
	int num_of_vertices=10, avg_degree=6;
	Graph* g=new Graph(num_of_vertices);
	vector<vector<pair<int, int> > > graph=g->create_graph(avg_degree);
	//cout<<graph.size();
	/*for(int i=0; i<graph.size(); i++)
	{
		//cout<<i<<" -> ";
		for(int j=0; j<graph[i].size(); j++)
		{
			//cout<<graph[i][j].first<<" ";
		}
		//cnt+=graph[i].size();
	}*/
    //Heap* h=new Heap(num_of_vertices);
    //Max_BW_Path_without_heap* mbw=new Max_BW_Path_without_heap(graph);
    Max_BW_Path_with_heap* mbw=new Max_BW_Path_with_heap(graph);
    for(int i=0; i<5; i++)
    {
        int source=rand()%num_of_vertices;
        int x=rand()%num_of_vertices;
        while(source==x)
        {
            x=rand()%num_of_vertices;
        }
        int target=x;
        cout<<source<<" "<<target<<endl;
        vector<int> path=mbw->modified_dijkstra_with_heap(source, target);
        for(int j=0; j<path.size(); j++)
        {
            cout<<path[j]<<" ";
        }
        cout<<endl;
    }
	return 0;
}




