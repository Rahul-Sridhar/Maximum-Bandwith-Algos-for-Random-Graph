#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <bits/stdc++.h>

using namespace std;

class Graph
{
    public:
        vector<vector<int> > edges;
        Graph(int);
        void make_connected();
		void remaining_edges_sparse(int);
		void remaining_edges_dense(int);
		vector<vector<pair<int, int> > > create_sparse_graph(int);
		vector<vector<pair<int, int> > > create_dense_graph(int);

    private:
        int num_of_vertices, num_of_edges;
        unordered_set<int> uset;
        vector<vector<pair<int, int> > > graph;
};

#endif // GRAPH_H
