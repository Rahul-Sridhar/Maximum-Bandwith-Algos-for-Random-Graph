#include "Kruskal.hpp"

Kruskal::Kruskal(vector<vector<pair<int, int> > > g, int num_vertices, int degree, vector<vector<int> > edges_of_graph)
{
    num_of_vertices=num_vertices;
    avg_degree=degree;
    rnk.resize(g.size());
    parent.resize(g.size());
    int n = (avg_degree*num_of_vertices)/2;
    for (int i = 0; i < n; i++)
    {
        heap.push_back({});
    }
    graph=g;
    max_heap_size=(avg_degree*num_of_vertices)/2;
    curr_heap_size=-1;
    edges=edges_of_graph;
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
    //cout<<"makset "<<vertex<<" "<<parent[vertex]<<endl;
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
    //vector<int> dad(graph.size());
    for(int i=0; i<num_of_vertices; i++)
    {
        makeset(i);
    }
    create_weights_set();
    //dad[s]=-1;
    unordered_map<int, vector<int>> umap;
    //cout<<endl;
    for(int i=0; i<=n; i++)
    {
        vector<int> curr_edge=maximum();
        //cout<<curr_edge[0]<<" ";
        delete_key(0);
        int u=curr_edge[1], v=curr_edge[2];
        int r1=find_parent(u), r2=find_parent(v);
        //cout<<"check"<<endl;
        //cout<<u<<" "<<v<<" "<<r1<<" "<<r2<<endl;
        if(r1!=r2)
        {
            /*if(v!=s)
            {
                dad[v]=u;
            }*/
            //cout<<"i am here"<<endl;
            /*cout<<"("<<u<<")"<<"("<<v<<")"<<curr_edge[0]<<"("<<curr_edge[1]<<")"<<"("<<curr_edge[2]<<")"<<" ";*/
            umap[u].push_back(v);
            umap[v].push_back(u);
            merge_vertices_to_a_set(r1, r2);
        }
    }
    cout<<endl;
    return reconstruct_kruskal_with_heap(s, t, umap);
}

vector<int> Kruskal::reconstruct_kruskal_with_heap(int s, int t, unordered_map<int, vector<int>> umap)
{
    vector<int> path;
    /*int i=t;
    path.push_back(t);
    while(dad[i]!=-1)
    {
        path.push_back(dad[i]);
        i=dad[i];
    }
    reverse(path.begin(), path.end());*/
    /*for(auto it:umap)
    {
        cout<<it.first<<" -> ";
        for(int i=0; i<it.second.size(); i++)
        {
            cout<<it.second[i]<<" ";
        }
        cout<<endl;
    }
    cout<<"***"<<s<<" "<<t<<endl;
    cout<<"cool"<<endl;*/
    path.push_back(s);
    //int curr_vertex=s;
    /*for(int i=0; i<graph.size(); i++)
    {
        for(int j=0; j<graph[i].size(); j++)
        {
            cout<<"("<<i<<")"<<"("<<graph[i][j].first<<")"<<graph[i][j].second<<" ";
        }
        cout<<endl;
    }*/
    vector<int> visited(num_of_vertices, -1);
    visited[s]=1;
    vector<int> ans1=dfs(s, t, umap, path, visited);
    int value=INT_MAX;
    cout<<endl;
    /*for(int i=0; i<ans1.size()-1; i++)
    {
        cout<<ans1[i]<<" "<<ans1[i+1]<<" "<<graph[ans1[i]][ans1[i+1]].second<<endl;
        value=min(value, graph[ans1[i]][ans1[i+1]].second);
    }
    cout<<value<<endl;*/
    return ans1;
    /*while(true)
    {
        for(int i=0; i<umap[curr_vertex].size(); i++)
        {
            if(visited.find(umap[curr_vertex][i])==visited.end())
            {
                visited.insert(umap[curr_vertex][i]);
                path.push_back(umap[curr_vertex][i]);
                curr_vertex=umap[curr_vertex][i];
                break;
            }
        }
        if(curr_vertex==t)
        {
            break;
        }
    }*/
    return path;
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
           //cout<<umap[vertex][i]<<endl;
           ans.push_back(umap[vertex][i]);
           visited[umap[vertex][i]]=1;
           vector<int> soln=dfs(umap[vertex][i], t, umap, ans, visited);
           if(visited[t]==1)
           {
               //ans.push_back(umap[vertex][i]);
               return soln;
           }
           ans.pop_back();
        }
    }
    return {};
}






