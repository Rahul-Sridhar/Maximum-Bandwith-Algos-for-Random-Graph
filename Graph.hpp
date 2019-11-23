#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <bits/stdc++.h>

using namespace std;

class Graph
{
    public:
        Graph(int);
        void make_connected();
		void remaining_edges(int);
		vector<vector<pair<int, int> > > create_graph(int);

    private:
        int num_of_vertices, num_of_edges;
        unordered_set<int> uset;
        vector<vector<pair<int, int>>> graph;
};

#endif // GRAPH_H
