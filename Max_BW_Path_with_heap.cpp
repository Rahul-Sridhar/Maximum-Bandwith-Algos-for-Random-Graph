#include "Max_BW_Path_with_heap.hpp"

Max_BW_Path_with_heap::Max_BW_Path_with_heap(vector<vector<pair<int, int> > > g)
{
    graph=g;
}

vector<int> Max_BW_Path_with_heap::modified_dijkstra_with_heap(int s, int t)
{
    vector<int> status(graph.size()), weights(graph.size()), dad(graph.size());
    Heap* heap=new Heap(graph.size());
    for(int i=0; i<graph.size(); i++)
    {
        // status=-1 indicates unseen
        status[i]=-1;
    }
    // status=1 indicates in_tree
    status[s]=1;
    dad[s]=-1;
    for(int i=0; i<graph[s].size(); i++)
    {
        // status=1 indicates fringe
        status[graph[s][i].first]=0;
        weights[graph[s][i].first]=graph[s][i].second;
        heap->update_weights(graph[s][i].second, graph[s][i].first);
        heap->insert_key(graph[s][i].first);
        dad[graph[s][i].first]=s;
    }
    while(status[t]!=1)
    {
        int pos=heap->maximum();
        //cout<<pos<<" ";
        heap->delete_key(pos);
        status[pos]=1;
        for(int i=0; i<graph[pos].size(); i++)
        {
            if(status[graph[pos][i].first]==-1)
            {
                status[graph[pos][i].first]=0;
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[pos][i].second);
                heap->update_weights(min(weights[pos], graph[pos][i].second), graph[pos][i].first);
                heap->insert_key(graph[pos][i].first);
            }
            else if(status[graph[pos][i].first]==0 && weights[graph[pos][i].first]<min(weights[pos], graph[pos][i].second))
            {
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[pos][i].second);
                heap->update_weights(min(weights[pos], graph[pos][i].second), graph[pos][i].first);
                heap->fix_heap(graph[pos][i].first);
            }
        }
    }
    cout<<weights[t]<<endl;
    return reconstruct_max_bw_path_with_heap(t, dad);
}

vector<int> Max_BW_Path_with_heap::reconstruct_max_bw_path_with_heap(int t, vector<int> dad)
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
