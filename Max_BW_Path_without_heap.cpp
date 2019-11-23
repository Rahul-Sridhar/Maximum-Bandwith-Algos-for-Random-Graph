#include "Max_BW_Path_without_heap.hpp"

Max_BW_Path_without_heap::Max_BW_Path_without_heap(vector<vector<int> > g)
{
    graph=g;
}

void Max_BW_Path_without_heap::modified_dijkstra_without_heap(int s, int t)
{
    vector<int> status(graph.size()), weights(graph.size()), dad(graph.size()), fringe;
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
        fringe.push_back(graph[s][i].first);
        dad[graph[s][i].first]=s;
    }
    while(!fringe.empty())
    {
        int pos=-1, max_weight=INT_MIN;
        for(int i=0; i<fringe.size(); i++)
        {
            if(max_weight<weights[fringe[i]])
            {
                max_weight=weights[fringe[i]];
                pos=i;
            }
        }
        status[pos]=1;
        fringe.erase(fringe.begin()+pos);
        for(int i=0; i<graph[pos].size(); i++)
        {
            if(status[graph[pos][i].first]==-1)
            {
                status[graph[pos][i].first]=0;
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[graph[pos][i].second]);
                fringe.push_back(graph[pos][i].first);
            }
            else if(status[graph[pos][i].first]==0 && weights[graph[pos][i].first]<min(weights[pos], graph[graph[pos][i].second]))
            {
                dad[graph[pos][i].first]=pos;
                weights[graph[pos][i].first]=min(weights[pos], graph[graph[pos][i].second]);
            }
        }
    }
    return reconstruct_max_bw_path(t, dad);
}

vector<int> reconstruct_max_bw_path_without_heap(int t, vector<int> dad)
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
