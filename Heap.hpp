#ifndef HEAP_HPP
#define HEAP_HPP

#include <bits/stdc++.h>

using namespace std;

class Heap
{
    public:
        Heap(int);
        void update_weights(int, int);
        int maximum();
        void insert_key(int);
        void delete_key(int);
        void fix_heap(int);
        bool heap_empty();



    private:
        std::vector<int> heap, weights, map_vertex_to_heapidx;
        int curr_heap_size;
        int max_heap_size;
};

#endif // HEAP_H

