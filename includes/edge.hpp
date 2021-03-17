#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "node.hpp"
#pragma once

struct edge{
        float peso;
        std::vector<int> nodes; //de mi lista de verices, cuales conecto con esta arista
        bool colored = false;

        // edge(float peso, std::vector<node> nodes);
}; 
struct compare{  //para ordenarlos por peso en la queue
    bool operator()(const edge & a, const edge & b){
        return a.peso > b.peso;
    }
};
// edge::edge(float peso, std::vector<node> nodes){
//     peso = peso;
//     nodes = nodes;
// }   
