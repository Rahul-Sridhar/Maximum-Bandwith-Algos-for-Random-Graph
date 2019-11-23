#ifndef MAX_BW_PATH_WITH_HEAP_HPP
#define MAX_BW_PATH_WITH_HEAP_HPP

#include <bits/stdc++.h>
#include "Heap.hpp"

using namespace std;


class Max_BW_Path_with_heap
{
    public:
        Max_BW_Path_with_heap(vector<vector<int> >);
        void modified_dijkstra_with_heap(int, int);
        vector<int> reconstruct_max_bw_path_with_heap(int, vector<int>);

    private:
        vector<vector<int> > graph;
};

#endif // MAX_BW_PATH_WITH_HEAP_HPP
