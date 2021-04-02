#pragma once
#include <vector>
#include <algorithm>
#include "node.hpp"

struct edge{
        float peso;
        std::vector<int> nodes; //de mi lista de verices, cuales conecto con esta arista
        bool colored = false;

};
struct compare{  //para ordenarlos por peso en la queue
    bool operator()(const edge & a, const edge & b){
        return a.peso > b.peso;
    }
};

