#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <bits/stdc++.h>

using namespace std;

class Kruskal
{
    public:
        Kruskal(vector<vector<pair<int, int> > >);
        static bool cmp(vector<int>, vector<int>);
        vector<int> maximum();
        void insert_key(int, int, int);
        void delete_key(int);
        void create_weights_set();
        void makeset(int);
        int find_parent(int);
        void merge_vertices_to_a_set(int, int);
        vector<int> make_mst(int, int);
        vector<int> reconstruct_kruskal_with_heap(int, vector<int>);

    private:
        int max_heap_size, curr_heap_size;
        vector<int> rnk, parent;
        vector<vector<int> > weights, heap;
        vector<vector<pair<int, int> > > graph;
};

#endif // KRUSKAL_HPP
