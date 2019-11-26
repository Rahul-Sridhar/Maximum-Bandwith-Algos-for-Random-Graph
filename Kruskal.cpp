#include "Kruskal.hpp"

Kruskal::Kruskal(vector<vector<pair<int, int> > > g, int num_vertices, int degree, vector<vector<int> > edges_of_graph)
{
    num_of_vertices=num_vertices;
    avg_degree=degree;
    //try {
    rnk.resize(g.size());
    parent.resize(g.size());
    /*} catch (std::bad_alloc &ba) {
        std::cout << "bad_alloc caught: " << ba.what() << '\n';
    }*/
    int n = (avg_degree*num_of_vertices)/2;
    for (int i = 0; i < n; i++)
    {
        //try {
        heap.push_back({});
        /*} catch (std::bad_alloc &ba) {
            cout << "Gotcha ============" << endl;
        }*/
    }
    graph=g;
    max_heap_size=(avg_degree*num_of_vertices)/2;
    curr_heap_size=-1;
    edges=edges_of_graph;
    //cout << "Returning from Constructor" << endl;
}

vector<int> Kruskal::maximum()
{
    if(curr_heap_size==-1)
    {
        return {INT_MAX};
    }
    return heap[0];
}

void Kruskal::insert_key(int w, int u, int v)
{
    if(curr_heap_size==max_heap_size-1)
    {
        return;
    }
    curr_heap_size++;
    heap[curr_heap_size] = {w, u, v};

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
    heap[curr_heap_size][0]=-1;
    heap[curr_heap_size][1]=-1;
    heap[curr_heap_size][2]=-1;
    curr_heap_size--;
    while(i>=1 && heap[(i-1)/2][0]<heap[i][0])
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
    for(int i=0; i<edges.size(); i++)
    {
        insert_key(edges[i][0], edges[i][1], edges[i][2]);
    }
}

void Kruskal::makeset(int vertex)
{
    rnk[vertex]=0;
    parent[vertex]=vertex;
}

// Path compression
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
    int n=max_heap_size-1;
    for(int i=0; i<num_of_vertices; i++)
    {
        makeset(i);
    }
    create_weights_set();
    unordered_map<int, vector<int>> umap;
    for(int i=0; i<=n; i++)
    {
        vector<int> curr_edge=maximum();
        delete_key(0);
        int u=curr_edge[1], v=curr_edge[2];
        int r1=find_parent(u), r2=find_parent(v);
        if(r1!=r2)
        {
            umap[u].push_back(v);
            umap[v].push_back(u);
            merge_vertices_to_a_set(r1, r2);
        }
    }
    return reconstruct_kruskal_with_heap(s, t, umap);
}

vector<int> Kruskal::reconstruct_kruskal_with_heap(int s, int t, unordered_map<int, vector<int>> umap)
{
    vector<int> path;
    path.push_back(s);
    vector<int> visited(num_of_vertices, -1);
    visited[s]=1;
    vector<int> ans=dfs(s, t, umap, path, visited);
    int value=INT_MAX;
    for(int i=0; i<ans.size()-1; i++)
    {
        int u=ans[i], v=ans[i+1];
        for(int j=0; j<graph[u].size(); j++)
        {
            if(graph[u][j].first==v)
            {
                value=min(value, graph[u][j].second);
                break;
            }
        }
    }
    cout<<"Bandwidth: "<<value<<endl;
    return ans;
}

vector<int> Kruskal::dfs(int vertex, int t, unordered_map<int, vector<int>> umap, vector<int> ans, vector<int>& visited)
{
    if(vertex==t)
    {
        return ans;
    }
    for(int i=0; i<umap[vertex].size(); i++)
    {
        if(visited[umap[vertex][i]]!=1)
        {
           ans.push_back(umap[vertex][i]);
           visited[umap[vertex][i]]=1;
           vector<int> soln=dfs(umap[vertex][i], t, umap, ans, visited);
           if(visited[t]==1)
           {
               return soln;
           }
           ans.pop_back();
        }
    }
    return {};
}
