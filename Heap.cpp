#include "Heap.hpp"

Heap::Heap(int heap_size)
{
    //ctor
    max_heap_size=heap_size;
    heap.resize(max_heap_size);
    weights.resize(max_heap_size, 0);
    map_vertex_to_heapidx.resize(max_heap_size, -1);
    curr_heap_size=-1;
}

void Heap::update_weights(int new_weight, int vertex_idx)
{
    weights[vertex_idx]=new_weight;
}

int Heap::maximum()
{
    if(curr_heap_size==-1)
    {
        return INT_MAX;
    }
    return heap[0];
}

void Heap::insert_key(int value)
{
    if(curr_heap_size==max_heap_size-1)
    {
        return;
    }
    heap[++curr_heap_size]=value;
    map_vertex_to_heapidx[value]=curr_heap_size;
    int i=curr_heap_size;
    while(i>=1 && weights[heap[(i-1)/2]]<weights[heap[i]])
    {
        map_vertex_to_heapidx[heap[(i-1)/2]]=i;
        map_vertex_to_heapidx[heap[i]]=(i-1)/2;
        swap(heap[(i-1)/2], heap[i]);
        i=(i-1)/2;
    }
}

void Heap::delete_key(int del_vertex)
{
    if(curr_heap_size==-1)
    {
        return;
    }
    int i=map_vertex_to_heapidx[del_vertex];
    map_vertex_to_heapidx[del_vertex]=-1;
    map_vertex_to_heapidx[heap[curr_heap_size]]=i;
    heap[i]=heap[curr_heap_size--];
    while(i>=1 && weights[heap[(i-1)/2]]<weights[heap[i]])
    {
        map_vertex_to_heapidx[heap[(i-1)/2]]=i;
        map_vertex_to_heapidx[heap[i]]=(i-1)/2;
        swap(heap[i], heap[(i-1)/2]);
        i=(i-1)/2;
    }
    while(((2*i+1)<=curr_heap_size && (weights[heap[i]]<weights[heap[2*i+1]])) || (((2*i+2)<=curr_heap_size) && (weights[heap[i]]<weights[heap[2*i+2]])))
    {
        if((2*i+1==curr_heap_size) || (weights[heap[2*i+1]]>weights[heap[2*i+2]]))
        {
            map_vertex_to_heapidx[heap[2*i+1]]=i;
            map_vertex_to_heapidx[heap[i]]=2*i+1;
            swap(heap[i], heap[2*i+1]);
            i=2*i+1;
        }
        else
        {
            map_vertex_to_heapidx[heap[2*i+2]]=i;
            map_vertex_to_heapidx[heap[i]]=2*i+2;
            swap(heap[i], heap[2*i+2]);
            i=2*i+2;
        }
    }
}

void Heap::fix_heap(int vertex)
{
    int i=map_vertex_to_heapidx[vertex];
    if(curr_heap_size==-1)
    {
        return;
    }
    while(i>=1 && weights[heap[(i-1)/2]]<weights[heap[i]])
    {
        map_vertex_to_heapidx[heap[(i-1)/2]]=i;
        map_vertex_to_heapidx[heap[i]]=(i-1)/2;
        swap(heap[i], heap[(i-1)/2]);
        i=(i-1)/2;
    }
    while(((2*i+1)<=curr_heap_size && (weights[heap[i]]<weights[heap[2*i+1]])) || (((2*i+2)<=curr_heap_size) && (weights[heap[i]]<weights[heap[2*i+2]])))
    {
        if((2*i+1==curr_heap_size) || (weights[heap[2*i+1]]>weights[heap[2*i+2]]))
        {
            map_vertex_to_heapidx[heap[2*i+1]]=i;
            map_vertex_to_heapidx[heap[i]]=2*i+1;
            swap(heap[i], heap[2*i+1]);
            i=2*i+1;
        }
        else
        {
            map_vertex_to_heapidx[heap[2*i+2]]=i;
            map_vertex_to_heapidx[heap[i]]=2*i+2;
            swap(heap[i], heap[2*i+2]);
            i=2*i+2;
        }
    }
}

bool Heap::heap_empty()
{
    if(curr_heap_size==-1)
    {
        return true;
    }
    return false;
}
