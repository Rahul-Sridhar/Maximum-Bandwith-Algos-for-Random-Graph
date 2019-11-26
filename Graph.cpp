#include "Graph.hpp"
#define WEIGHT_MAX 10000000

using namespace std;


Graph::Graph(int num_vertices)
{
    num_of_vertices=num_vertices;
    graph.resize(num_vertices);
}

void Graph::make_connected()
{
	vector<int> A(num_of_vertices, 0);
	for(int i=0; i<num_of_vertices; i++)
	{
		A[i]=i;
	}
	random_shuffle(A.begin(), A.end());
	srand(time(0));
	for(int i=0; i<num_of_vertices; i++)
	{
		int w=rand()%WEIGHT_MAX+1;
		if(i==graph.size()-1)
		{
			vector<int> entry_edges;
			entry_edges.push_back(w);
			entry_edges.push_back(A[i]);
			entry_edges.push_back(A[0]);
			edges.push_back(entry_edges);
			graph[A[i]].push_back(make_pair(A[0], w));
			graph[A[0]].push_back(make_pair(A[i], w));
			uset.insert(A[i]*10000+(A[0]));
			uset.insert(A[0]*10000+A[i]);
		}
		else
		{
			vector<int> entry_edges;
			entry_edges.push_back(w);
			entry_edges.push_back(A[i]);
			entry_edges.push_back(A[i+1]);
			edges.push_back(entry_edges);
			graph[A[i]].push_back(make_pair(A[i+1], w));
			graph[A[i+1]].push_back(make_pair(A[i], w));
			uset.insert(A[i]*10000+(A[i+1]));
			uset.insert((A[i+1])*10000+(A[i]));
		}

	}
}

void Graph::remaining_edges_sparse(int num_of_remaining_edges)
{
	int i=0;
	srand(time(0));
	while(i < num_of_remaining_edges)
	{
	    int a = rand()%num_of_vertices;
	    int b = rand()%num_of_vertices;
	    if(uset.find(a*10000+b)!=uset.end())
	    {
	    	continue;
		}
		else if(a==b)
		{
			continue;
		}
        int w=rand()%WEIGHT_MAX+1;
        vector<int> entry_edges;
        entry_edges.push_back(w);
        entry_edges.push_back(a);
        entry_edges.push_back(b);
        edges.push_back(entry_edges);
		graph[a].push_back(make_pair(b, w));
	    uset.insert(a*10000+b);
	    graph[b].push_back(make_pair(a, w));
	    uset.insert(b*10000+a);
	    i++;
	}
}

void Graph::remaining_edges_dense(int num_of_remaining_edges)
{
    srand(time(0));
    for(int i=0; i<num_of_vertices; i++)
    {
        for(int j=i+1; j<num_of_vertices; j++)
        {
            if(((double) rand() / (RAND_MAX))>0.2)
            {
                continue;
            }
            if(uset.find(i*10000+j)!=uset.end())
            {
                continue;
            }
            int w=rand()%WEIGHT_MAX+1;
            vector<int> entry_edges;
            entry_edges.push_back(w);
            entry_edges.push_back(i);
            entry_edges.push_back(j);
            edges.push_back(entry_edges);
            graph[i].push_back(make_pair(j, w));
            uset.insert(i*10000+j);
            graph[j].push_back(make_pair(i, w));
            uset.insert(j*10000+i);
        }
    }
}

vector<vector<pair<int, int>> > Graph::create_sparse_graph(int avg_degree)
{
	make_connected();
    num_of_edges=(avg_degree*num_of_vertices)/2;
    remaining_edges_sparse(num_of_edges - num_of_vertices);
	return graph;
}

vector<vector<pair<int, int>> > Graph::create_dense_graph(int avg_degree)
{
	make_connected();
    num_of_edges=(avg_degree*num_of_vertices)/2;
    remaining_edges_dense(num_of_edges - num_of_vertices);
	return graph;
}

