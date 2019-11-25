#include <bits/stdc++.h>

using namespace std;

#include "Graph.hpp"
#include "Heap.hpp"
#include "Max_BW_Path_without_heap.hpp"
#include "Max_BW_Path_with_heap.hpp"
#include "Kruskal.hpp"

int main()
{
	int num_of_vertices=5000, avg_degree=6;
	Graph* g=new Graph(num_of_vertices);
	vector<vector<pair<int, int> > > graph=g->create_graph(avg_degree);
	vector<vector<int> > edges=g->edges;
	/*cout<<endl;
	for(int i=0; i<edges.size(); i++)
    {
        cout<<edges[i][0]<<" ";
    }
    cout<<endl;*/
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
    Kruskal* kr=new Kruskal(graph, num_of_vertices, avg_degree, edges);
    /*for(int i=0; i<5; i++)
    {
        int source=rand()%num_of_vertices;
        int x=rand()%num_of_vertices;
        while(source==x)
        {
            x=rand()%num_of_vertices;
        }
        int target=x;
        cout<<source<<" "<<target<<endl;
        vector<int> path=kr->make_mst(source, target);
        for(int j=0; j<path.size(); j++)
        {
            cout<<path[j]<<" ";
        }
        cout<<endl;
    }*/
    vector<int> path=kr->make_mst(3, 7);
    for(int j=0; j<path.size(); j++)
    {
        cout<<path[j]<<" ";
    }
    cout<<endl;
	return 0;
}




