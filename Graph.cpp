#include "Graph.hpp"

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
		A[i]=i+1;
	}
	random_shuffle(A.begin(), A.end());
	srand(time(0));
	for(int i=0; i<num_of_vertices; i++)
	{
		int w=rand()%100+1;
		if(i==graph.size()-1)
		{
			vector<int> entry_edges;
			entry_edges.push_back(w);
			entry_edges.push_back(i);
			entry_edges.push_back(0);
			edges.push_back(entry_edges);
			graph[i].push_back(make_pair(0, w));
			graph[0].push_back(make_pair(i, w));
			uset.insert(i*10000+(0));
			uset.insert(0*10000+i);
		}
		else
		{
			vector<int> entry_edges;
			entry_edges.push_back(w);
			entry_edges.push_back(i);
			entry_edges.push_back(i+1);
			edges.push_back(entry_edges);
			graph[i].push_back(make_pair(i+1, w));
			graph[i+1].push_back(make_pair(i, w));
			uset.insert(i*10000+(i+1));
			uset.insert((i+1)*10000+(i));
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
        int w=rand()%100+1;
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
            int w=rand()%100+1;
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

