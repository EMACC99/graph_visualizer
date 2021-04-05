#pragma once
#include <vector>

struct edge{
        float peso;
        std::vector<int> nodes; //de mi lista de verices, cuales conecto con esta arista
        bool colored = false;

};
struct compare{  //para ordenarlos en un vector
    bool operator()(const edge & a, const edge & b){
        return a.peso < b.peso;
    }
};

struct compare_pq{ //para ordenarlos por peso en la queue y que saque el menor primero
    bool operator()(const edge &a, const edge &b){
        return a.peso > b.peso;
    }
};