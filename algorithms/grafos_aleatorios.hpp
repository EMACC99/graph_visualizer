#pragma once

#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>

#include "../includes/edge.hpp"
#include "../includes/node.hpp"


void erdos_renyi(const int n, const float p, std::vector<edge>&aristas, std::vector<node>& vertices){
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

void erdos_renyi_m(const int n, const int m, std::vector<edge>& aristas, std::vector<node> & vertices){
    for (int i = 0; i < n; ++i){
        node nodo;
        nodo.id = i;
        nodo.root_id = -1;
        vertices.push_back(nodo);
    } 
    for (int v = 0; v < n; ++v){
        for (int u = 0; u <v; ++u){
            edge arista;
            arista.nodes = {u,v};
            vertices[v].arista_index.push_back(aristas.size());
            vertices[u].arista_index.push_back(aristas.size());
            aristas.push_back(arista);
        }
    }
    // std::vector<edge>aristas2;
    // std::__sample(aristas.begin(), aristas.end(), std::back_inserter(aristas2), m,std::mt19937{std::random_device{}()});
    // sample(aristas.begin(), aristas.end(), std::back_inserter(aristas), m,std::mt19937{std::random_device{}()});

    std::random_shuffle(aristas.begin(), aristas.end());
    aristas.resize(m);
} 