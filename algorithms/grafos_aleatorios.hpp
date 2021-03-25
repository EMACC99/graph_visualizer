#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../includes/edge.hpp"
#include "../includes/node.hpp"


void erdos_renyi(int n, float p, std::vector<edge>&aristas, std::vector<node>& vertices){
    for (int i = 0; i < n; ++i){
        node nodo;
        nodo.id = i;
        nodo.root_id = -1;
        vertices.push_back(nodo);
    } 

    for (int v = 0; v < n; ++v){
        for (int u = 0; u < v; ++u){
            float f =static_cast<float> (rand())/static_cast<float> (RAND_MAX);
            if (f < p){
                edge arista;
                arista.nodes = {u,v};
                vertices[v].arista_index.push_back(aristas.size());
                vertices[u].arista_index.push_back(aristas.size());
                aristas.push_back(arista);
            }
        }
    }
}