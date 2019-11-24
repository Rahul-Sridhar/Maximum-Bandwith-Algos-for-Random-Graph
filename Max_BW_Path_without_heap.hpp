#ifndef MAX_BW_PATH_WITHOUT_HEAP_HPP
#define MAX_BW_PATH_WITHOUT_HEAP_HPP

#include <bits/stdc++.h>

using namespace std;

class Max_BW_Path_without_heap
{
    public:
        Max_BW_Path_without_heap(vector<vector<pair<int, int> > >);
        vector<int> modified_dijkstra_without_heap(int, int, bool verbose=false);
        vector<int> reconstruct_max_bw_path_without_heap(int, vector<int>);

    private:
        vector<vector<pair<int, int> > > graph;

};

#endif // MAX_BW_PATH_WITHOUT_HEAP_H
