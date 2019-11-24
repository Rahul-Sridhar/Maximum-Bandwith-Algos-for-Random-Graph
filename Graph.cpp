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
	for(int i=0; i<num_of_vertices; i++)
	{
		int w=rand()%100+1;
		if(i==0)
		{
			graph[i].push_back(make_pair(i+1, w));
			graph[i].push_back(make_pair(graph.size()-1, w));
			uset.insert(i*10000+(i+1));
			uset.insert(i*10000+(graph.size()-1));
		}
		else if(i==graph.size()-1)
		{
			graph[i].push_back(make_pair(i-1, w));
			graph[i].push_back(make_pair(0, w));
			uset.insert(i*10000+(i-1));
			uset.insert(i*10000+0);
		}
		else
		{
			graph[i].push_back(make_pair(i-1, w));
			graph[i].push_back(make_pair(i+1, w));
			uset.insert(i*10000+(i-1));
			uset.insert(i*10000+(i+1));
		}

	}
}

void Graph::remaining_edges(int num_of_remaining_edges)
{
	int i=0;
	srand(time(0));
	int count = 0;
	while(i < num_of_remaining_edges)
	{
	    count++;
	    //cout << count << ":" << i << endl;
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
        //cout<<a<<" "<<b<<endl;
		graph[a].push_back(make_pair(b, w));
	    uset.insert(a*10000+b);
	    graph[b].push_back(make_pair(a, w));
	    uset.insert(b*10000+a);
	    i++;
	    //cout<<i<<endl;
	}
}

vector<vector<pair<int, int>> > Graph::create_graph(int avg_degree)
{
	make_connected();
    cout<<11<<endl;
    num_of_edges=(avg_degree*num_of_vertices)/2;
    cout<<12<<endl;
    remaining_edges(num_of_edges - num_of_vertices);
    cout<<13<<endl;
	return graph;
}

