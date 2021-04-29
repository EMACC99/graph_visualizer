#pragma once
#include <vector>

struct node{
    int padre;
    int id;
    float x,y;
    std::vector <int> arista_index; // de la lista de aristas, pon los que le corresponden, moejor dicho, todas la aristas que salen del vertice
};

struct node_compare{
    bool operator()(const node &u, const node &v)const{
        return u.id < v.id;
    }
};