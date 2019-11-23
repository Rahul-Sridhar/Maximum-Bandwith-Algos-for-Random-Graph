#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP


class Kruskal
{
    public:
        Kruskal();
        static bool cmp(vector<int>, vector<int>);
        vector<int> maximum();
        void insert_key(int);
        void delete_key(int);
        void create_weights_set();
        int find_parent(int);
        void merge_vertices_to_a_set(int, int);
        vector<int> make_mst(int, int);
        vector<int> reconstruct_kruskal_with_heap(int, vector<int>);

    private:
        int max_heap_size, curr_heap_size;
        vector<int> rnk, parent;
        vector<vector<int> > graph, weights, heap;
};

#endif // KRUSKAL_HPP
