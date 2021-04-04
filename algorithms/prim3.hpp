#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <queue>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"
#include "../includes/globals.hpp"

std::vector<edge> prim(){
    std::vector<bool> vertices_explorados;
    std::vector<edge> arbol;
    std::priority_queue<edge, std::vector<edge>, compare_pq> aristas_por_explorar;

    int vertice_aleatorio = rand() % vertices.size();
    for (int i = 0; i < vertices.size(); ++i)
        vertices_explorados.push_back(false);
    
    vertices_explorados[vertice_aleatorio] = true;
    for (int i = 0; i<vertices[vertice_aleatorio].arista_index.size(); ++i){
        aristas_por_explorar.push(aristas[vertices[vertice_aleatorio].arista_index[i]]);
    }
    while (!aristas_por_explorar.empty()){
        edge s = aristas_por_explorar.top();
        aristas_por_explorar.pop();
        int u,v,w,aux;
        u = s.nodes[0];
        v = s.nodes[1];

        if (!vertices_explorados[v]){
            arbol.push_back(s);
            vertices_explorados[v] = true;
            for (int i = 0; i < vertices[v].arista_index.size(); ++i){ 
                aux = aristas[vertices[v].arista_index[i]].nodes[0];
                if (aux != v)
                    w = aux;
                else
                    w = aristas[vertices[v].arista_index[i]].nodes[1];
                
                if (!vertices_explorados[w])
                    aristas_por_explorar.push(aristas[vertices[v].arista_index[i]]);
            }
        }
        else if(!vertices_explorados[u]){
            arbol.push_back(s);
            vertices_explorados[u] = true;

            for (int i = 0; i < vertices[u].arista_index.size(); ++i){
                int aux = aristas[vertices[u].arista_index[i]].nodes[0];
                int w;
                if (aux != v)
                    w = aux;
                else
                    w = aristas[vertices[u].arista_index[i]].nodes[1];

                if (!vertices_explorados[w]){
                    aristas_por_explorar.push(aristas[vertices[u].arista_index[i]]);
                }
            }
        }
    }
    return arbol;
    
}