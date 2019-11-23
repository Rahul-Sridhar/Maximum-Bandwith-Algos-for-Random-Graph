#include "Kruskal.hpp"

Kruskal::Kruskal(vector<vector<int> > g)
{
    rnk.resize(g.size());
    parent.resize(g.size());
    heap.resize(g.size());
    graph=g;
    max_heap_size=g.size();
    curr_heap_size=-1;
}

static bool Kruskal::cmp(vector<int> A, vector<int> B)
{
    return A[0]>B[0];
}

vector<int> Kruskal::maximum()
{
    if(curr_heap_size==-1)
    {
        return INT_MAX;
    }
    return heap[0];
}

void Kruskal::insert_key(int w, int u, int v)
{
    if(curr_heap_size==max_heap_size)
    {
        return;
    }
    curr_heap_size++;
    heap[curr_heap_size][0]=w;
    heap[curr_heap_size][1]=u;
    heap[curr_heap_size][2]=v;
    int i=curr_heap_size;
    while(i>=1 && heap[(i-1)/2][0]<heap[i][0])
    {
        swap(heap[(i-1)/2][0], heap[i][0]);
        swap(heap[(i-1)/2][1], heap[i][1]);
        swap(heap[(i-1)/2][2], heap[i][2]);
        i=(i-1)/2;
    }
}

void Kruskal::delete_key(int i)
{
    if(curr_heap_size==-1)
    {
        return;
    }
    heap[i][0]=heap[curr_heap_size][0];
    heap[i][1]=heap[curr_heap_size][1];
    heap[i][2]=heap[curr_heap_size][2];
    curr_heap_size--;
    while(i>=1 && heap[(i-1)/2]][0]<heap[i][0])
    {
        swap(heap[(i-1)/2][0], heap[i][0]);
        swap(heap[(i-1)/2][1], heap[i][1]);
        swap(heap[(i-1)/2][2], heap[i][2]);
        i=(i-1)/2;
    }
    while(((2*i+1)<=curr_heap_size && (heap[i][0]<heap[2*i+1][0])) || (((2*i+2)<=curr_heap_size) && (heap[i][0]<heap[2*i+2][0])))
    {
        if((2*i+1==curr_heap_size) || (heap[2*i+1][0]>heap[2*i+2][0]))
        {
            swap(heap[2*i+1][0], heap[i][0]);
            swap(heap[2*i+1][1], heap[i][1]);
            swap(heap[2*i+1][2], heap[i][2]);
            i=2*i+1;
        }
        else
        {
            swap(heap[2*i+2][0], heap[i][0]);
            swap(heap[2*i+2][1], heap[i][1]);
            swap(heap[2*i+2][2], heap[i][2]);
            i=2*i+2;
        }
    }
}

void Kruskal::create_weights_set()
{
    for(int i=0; i<graph.size(); i++)
    {
        for(int j=0; j<graph[i].size(); j++)
        {
            heap.insert_key(graph[i][j].second, i, graph[i][j].first);
        }
    }
}

void Kruskal::makeset(int vertex)
{
    rnk[vertex]=0;
    parent[vertex]=vertex;
}

int Kruskal::find_parent(int u)
{
    if(u!=parent[u])
    {
        parent[u]=find_parent(parent[u]);
    }
    return parent[u];
}

void Kruskal::merge_vertices_to_a_set(int x, int y)
{
    x=find_parent(x), y=find_parent(y);

    if(rnk[x]>rnk[y])
    {
        parent[y]=x;
    }
    else
    {
        parent[x]=y;
    }
    if(rnk[x]==rnk[y])
    {
        rnk[y]++;
    }
}

vector<int> Kruskal::make_mst(int s, int t)
{
    vector<int> dad(graph.size());

    create_weights_set();

    vector<vector<int>> mst_edges;

    for(int i=0; i<graph.size(); i++)
    {
        makeset(i);
    }

    for(int i=0; i<weights.size(); i++)
    {
        vector<int> curr_edge=maximum();
        delete_key(0);
        int u=curr_edge[1], v=curr_edge[2];
        int r1=find_parent(u), r2=find_parent(v);
        if(r1!=r2)
        {
            if(u==s)
            {
                dad[s]=-1;
            }
            else if(v!=s)
            {
                dad[v]=u;
            }
            merge_vertices_to_a_set(r1, r2);
        }
    }

    return reconstruct_kruskal_with_heap(t, dad);
}

vector<int> reconstruct_kruskal_with_heap(int t, vector<int> dad)
{
    vector<int> path;
    int i=t;
    path.push_back(t);
    while(dad[i]!=-1)
    {
        path.push_back(dad[i]);
        i=dad[i];
    }
    reverse(path.begin(), path.end());
    return path;
}






