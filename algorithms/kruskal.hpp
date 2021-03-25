#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"

int raiz(const int &u, const std::vector<int> &padres){
    if (padres[u] != -1)
        return raiz(padres[u], padres);
    return u;
}

void juntar(const int &u, const int &v, std::vector<int> &padres){
    padres[raiz(u, padres)] = raiz(v, padres);
}

std::vector<edge> kusrkal(std::vector<node> &vertices, const std::vector<edge> &aristas){
    std::vector<edge> arbol;
    std::vector<edge> kruskal_aristas = aristas;
    std::sort(kruskal_aristas.begin(), kruskal_aristas.end(), compare()); //las ordenamos por peso
    std::vector<int> padres (vertices.size());
    
    for (auto &elem : padres)
        elem = -1;
    
    int u,v;
    for (int i = 0; i < kruskal_aristas.size(); ++i){
        u = kruskal_aristas[i].nodes[0];
        v = kruskal_aristas[i].nodes[1];
        if (raiz(u,padres) != raiz(v, padres)){
            arbol.push_back(kruskal_aristas[i]);
            juntar(u,v,padres);
        } 
    }
    return arbol;
}