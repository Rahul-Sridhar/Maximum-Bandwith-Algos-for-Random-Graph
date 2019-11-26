#include "Max_BW_Path_without_heap.hpp"

Max_BW_Path_without_heap::Max_BW_Path_without_heap(vector<vector<pair<int, int> > > g)
{
    graph=g;
}

vector<int> Max_BW_Path_without_heap::modified_dijkstra_without_heap(int s, int t)
{
    vector<int> status(graph.size()), weights(graph.size(), 0), dad(graph.size()), fringe;
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
        // status=0 indicates fringe
        status[graph[s][i].first]=0;
        weights[graph[s][i].first]=graph[s][i].second;
        fringe.push_back(graph[s][i].first);
        dad[graph[s][i].first]=s;
    }
    while(status[t]!=1)
    {
        int pos=-1, pos_idx=-1, max_weight=INT_MIN;
        for(int i=0; i<fringe.size(); i++)
        {
            if(max_weight<weights[fringe[i]])
            {
                max_weight=weights[fringe[i]];
                pos=fringe[i];
                pos_idx=i;
            }
        }
        status[pos]=1;
        fringe.erase(fringe.begin()+pos_idx);
        for(int i=0; i<graph[pos].size(); i++)
        {
            if(status[graph[pos][i].first]==-1)
            {
                status[graph[pos][i].first]=0;
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[pos][i].second);
                fringe.push_back(graph[pos][i].first);
            }
            else if(status[graph[pos][i].first]==0 && weights[graph[pos][i].first]<min(weights[pos], graph[pos][i].second))
            {
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[pos][i].second);
            }
        }
    }
    cout<<"Bandwidth: "<<weights[t]<<endl;
    return reconstruct_max_bw_path_without_heap(t, dad);
}

vector<int> Max_BW_Path_without_heap::reconstruct_max_bw_path_without_heap(int t, vector<int> dad)
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
