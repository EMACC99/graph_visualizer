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

// edge::edge(float peso, std::vector<node> nodes){
//     peso = peso;
//     nodes = nodes;
// }   
