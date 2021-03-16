#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <queue>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"
#pragma once

int get_min_index(const std::vector<edge> &aristas, const std::vector<bool> vertices_explorados){
    int min_index = 0;

    for (int i = 0; i < aristas.size(); ++i){
        if (vertices_explorados[i] == false && aristas[i].peso < aristas[min_index].peso)
            min_index = i;
    }

    return min_index;
}

void get_aristas_from_node(const node &vertice, std::priority_queue<int> &aristas_por_explorar){

    for (int i = 0; i < vertice.arista_index.size(); ++i)
        aristas_por_explorar.push(vertice.arista_index[i]);
    
}

void remove_min (const int &min_index, std::priority_queue<int> &aristas_por_explorar){
    std::priority_queue<int> new_aristas;
    int n = aristas_por_explorar.size(); //cambia de size por lo que tiene que ser constante
    int value;
    for (int i = 0; i < n; ++i){
        value = aristas_por_explorar.top();
        if (value != min_index)
            new_aristas.push(value);
        
        aristas_por_explorar.pop();
    }
    aristas_por_explorar.swap(new_aristas);
}

std::vector<int> prim(const std::vector<node> &vertices, std::vector<edge> aristas){

    std::vector<int> arbol;

    int vertice_aleatorio = rand() % vertices.size();
    std::priority_queue<int> aristas_por_explorar;
    std::vector<bool> vertices_explorados;
    for (int i = 0; i < vertices.size(); ++i)
        vertices_explorados.push_back(false);
    
    vertices_explorados[vertice_aleatorio] = true;
    get_aristas_from_node(vertices[vertice_aleatorio], aristas_por_explorar);

    int min_arista_index;
    while (!aristas_por_explorar.empty()){
        min_arista_index = get_min_index(aristas, vertices_explorados);
        remove_min(min_arista_index, aristas_por_explorar);
        int u,v;
        u = aristas[min_arista_index].nodes[0];
        v = aristas[min_arista_index].nodes[1];

        if(vertices_explorados[v] == false){
            arbol.push_back(min_arista_index);
            vertices_explorados[v] = true;
            
            for (int i = 0; i <  vertices[v].arista_index.size(); ++i){
                int aux = aristas[vertices[v].arista_index[i]].nodes[0];
                int w;
                if (aux != v)
                    w = aux;
                else
                    w = aristas[vertices[v].arista_index[i]].nodes[1];

                if (vertices_explorados[w] == false){
                    aristas_por_explorar.push(vertices[v].arista_index[i]);
                }
            }
        }
        else if(vertices_explorados[u] == false){
            arbol.push_back(min_arista_index);
            vertices_explorados[u] = true;

            for (int i = 0; i < vertices[u].arista_index.size(); ++i){
                int aux = aristas[vertices[u].arista_index[i]].nodes[0];
                int w;
                if (aux != v)
                    w = aux;
                else
                    w = aristas[vertices[u].arista_index[i]].nodes[1];

                if (vertices_explorados[w] == false){
                    aristas_por_explorar.push(vertices[u].arista_index[i]);
                }
            }
        }
    }
    
    return arbol;
}