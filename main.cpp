#include <bits/stdc++.h>

using namespace std;

#include "Graph.hpp"
#include "Heap.hpp"
#include "Max_BW_Path_without_heap.hpp"
#include "Max_BW_Path_with_heap.hpp"
#include "Kruskal.hpp"

int main()
{
	//cout<<"***********CSCE 629 Course Project************"<<endl;
	//cout<<"**************Rahul Sridhar*******************"<<endl;
	//int num_of_vertices=5000, avg_degree=6;
	//cout<<"Sparse Graph"<<endl<<endl<<endl;
	/*for(int i=0; i<5; i++)
    {
        Graph* g=new Graph(num_of_vertices);
        vector<vector<pair<int, int> > > graph=g->sparse_create_graph(avg_degree);
        vector<vector<int> > edges=g->edges;
        for(int i=0; i<5; i++)
        {
            int source=rand()%num_of_vertices;
            int x=rand()%num_of_vertices;
            while(source==x)
            {
                x=rand()%num_of_vertices;
            }
            int target=x;

            std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
            std::chrono::duration<double> elapsed_time_in_seconds;

            cout<<source<<" "<<target<<endl;

            Max_BW_Path_without_heap* mbw=new Max_BW_Path_without_heap(graph);
            start_time=std::chrono::system_clock::now();
            vector<int> path=mbw->modified_dijkstra_without_heap(source, target);
            end_time=std::chrono::system_clock::now();
            for(int j=0; j<path.size(); j++)
            {
                cout<<path[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<elapsed_time_in_seconds.count()<<endl<<endl;

            Max_BW_Path_with_heap* mbw1=new Max_BW_Path_with_heap(graph);
            start_time=std::chrono::system_clock::now();
            vector<int> path1=mbw1->modified_dijkstra_with_heap(source, target);
            end_time=std::chrono::system_clock::now();
            for(int j=0; j<path1.size(); j++)
            {
                cout<<path1[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<elapsed_time_in_seconds.count()<<endl<<endl;

            Kruskal* kr=new Kruskal(graph, num_of_vertices, avg_degree, edges);
            start_time=std::chrono::system_clock::now();
            vector<int> path2=kr->make_mst(source, target);
            end_time=std::chrono::system_clock::now();
            for(int j=0; j<path2.size(); j++)
            {
                cout<<path2[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<elapsed_time_in_seconds.count()<<endl<<endl;
        }
        cout<<endl<<endl<<endl;
    }*/
    //cout<<endl<<endl<<endl;
    //cout<<"Dense Graph"<<endl;
    int num_of_vertices=5000, avg_degree=1000;
    Graph* g=new Graph(num_of_vertices);
    vector<vector<pair<int, int> > > graph=g->create_dense_graph(avg_degree);
    vector<vector<int> > edges=g->edges;
    for(int i=0; i<graph.size(); i++)
    {
        cout<<graph[i].size()<<" ";
    }
    Max_BW_Path_without_heap* mbw=new Max_BW_Path_without_heap(graph);
    vector<int> path=mbw->modified_dijkstra_without_heap(3, 10);
    for(int j=0; j<path.size(); j++)
    {
        cout<<path[j]<<" ";
    }
    cout<<endl;

    Max_BW_Path_with_heap* mbw1=new Max_BW_Path_with_heap(graph);
    vector<int> path1=mbw1->modified_dijkstra_with_heap(3, 10);
    for(int j=0; j<path1.size(); j++)
    {
        cout<<path1[j]<<" ";
    }
    cout<<endl;

    Kruskal* kr=new Kruskal(graph, num_of_vertices, avg_degree, edges);
    vector<int> path2=kr->make_mst(3, 10);
    for(int j=0; j<path2.size(); j++)
    {
        cout<<path2[j]<<" ";
    }
	return 0;
}




