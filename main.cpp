#include <bits/stdc++.h>

using namespace std;

#include "Graph.hpp"
#include "Heap.hpp"
#include "Max_BW_Path_without_heap.hpp"
#include "Max_BW_Path_with_heap.hpp"
#include "Kruskal.hpp"

class RedirectStdOutput {
    public:
        RedirectStdOutput(std::ofstream& file)
            : _psbuf{file.rdbuf()}, _backup{std::cout.rdbuf()}
        {
            std::cout.rdbuf(_psbuf);
        }

        ~RedirectStdOutput() {
            std::cout.rdbuf(_backup);
        }

    private:
        std::streambuf* _psbuf;
        std::streambuf* _backup;
};

int main()
{
	std::ofstream file ("output.txt");
    RedirectStdOutput rso (file);
	cout<<"********************CSCE 629 Course Project************"<<endl;
	cout<<"***********************Rahul Sridhar*******************"<<endl;
	int num_of_vertices=5000, avg_degree=6;
	cout<<endl<<endl<<endl<<"Sparse Graph"<<endl<<endl<<endl;
	for(int i=0; i<5; i++)
    {
        Graph* g=new Graph(num_of_vertices);
        vector<vector<pair<int, int> > > graph=g->create_sparse_graph(avg_degree);
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

            cout<<"Source: "<<source<<"   Destination: "<<target<<endl;

            cout<<"Algorithm: Maximum BW Dijkstra without heap"<<endl;
            Max_BW_Path_without_heap* mbw=new Max_BW_Path_without_heap(graph);
            start_time=std::chrono::system_clock::now();
            vector<int> path=mbw->modified_dijkstra_without_heap(source, target);
            end_time=std::chrono::system_clock::now();
            delete mbw;
            cout<<"Path: ";
            for(int j=0; j<path.size(); j++)
            {
                cout<<path[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;

            cout<<"Algorithm: Maximum BW Dijkstra with heap"<<endl;
            Max_BW_Path_with_heap* mbw1=new Max_BW_Path_with_heap(graph);
            start_time=std::chrono::system_clock::now();
            vector<int> path1=mbw1->modified_dijkstra_with_heap(source, target);
            end_time=std::chrono::system_clock::now();
            delete mbw1;
            cout<<"Path: ";
            for(int j=0; j<path1.size(); j++)
            {
                cout<<path1[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;

            cout<<"Algorithm: Maximum BW Kruskal"<<endl;
            Kruskal* kr=new Kruskal(graph, num_of_vertices, avg_degree, edges);
            start_time=std::chrono::system_clock::now();
            vector<int> path2=kr->make_mst(source, target);
            end_time=std::chrono::system_clock::now();
            delete kr;
            cout<<"Path: ";
            for(int j=0; j<path2.size(); j++)
            {
                cout<<path2[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;
        }
        delete g;
        cout<<endl<<endl<<endl;
    }
    cout<<endl<<endl<<endl;
    cout<<"Dense Graph"<<endl;

    avg_degree=1000;
    for(int i=0; i<5; i++)
    {
        Graph* g=new Graph(num_of_vertices);
        vector<vector<pair<int, int> > > graph=g->create_dense_graph(avg_degree);
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

            cout<<"Source: "<<source<<"   Destination: "<<target<<endl<<endl;

            vector<int> path;

            cout<<"Algorithm: Maximum BW Dijkstra without heap"<<endl;
            Max_BW_Path_without_heap* mbw=new Max_BW_Path_without_heap(graph);
            start_time=std::chrono::system_clock::now();
            path=mbw->modified_dijkstra_without_heap(source, target);
            end_time=std::chrono::system_clock::now();
            delete mbw;
            cout<<"Path: ";
            for(int j=0; j<path.size(); j++)
            {
                cout<<path[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;

            cout<<"Algorithm: Maximum BW Dijkstra with heap"<<endl;
            Max_BW_Path_with_heap* mbw1=new Max_BW_Path_with_heap(graph);
            start_time=std::chrono::system_clock::now();
            path=mbw1->modified_dijkstra_with_heap(source, target);
            end_time=std::chrono::system_clock::now();
            delete mbw1;
            cout<<"Path: ";
            for(int j=0; j<path.size(); j++)
            {
                cout<<path[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;

            cout<<"Algorithm: Maximum BW Kruskal"<<endl;
            Kruskal* kr=new Kruskal(graph, num_of_vertices, avg_degree, edges);
            start_time=std::chrono::system_clock::now();
            path=kr->make_mst(source, target);
            end_time=std::chrono::system_clock::now();
            delete kr;
            cout<<"Path: ";
            for(int j=0; j<path.size(); j++)
            {
                cout<<path[j]<<" ";
            }
            elapsed_time_in_seconds = end_time - start_time;
            cout<<endl<<"Running Time: "<<elapsed_time_in_seconds.count()<<endl<<endl;
        }
        delete g;
        cout<<"done";
        cout<<endl<<endl<<endl;
    }
	return 0;
}




