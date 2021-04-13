#pragma once

#include <vector>
#include <algorithm>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"
#include "../includes/globals.hpp"

// int raiz(const int &u, const std::vector<int> &padres){
//     if (padres[u] != -1)
//         return raiz(padres[u], padres);
//     return u;
// }
/**
 * @brief check the root of two nodes and meke them the sema as they are in the same conex component (disjoint sets)
 * 
 * @param u 
 * @param padres 
 * @return int 
 */
int raiz(const int &u, std::vector<int> & padres){
    int p = padres[u];
    if (p == -1)
        return u;
    else{
        int r = raiz(p,padres);
        padres[u] = r;
        return r;
    }
}
/**
 * @brief join the roots of two given nodes
 * 
 * @param u 
 * @param v 
 * @param padres 
 */
void juntar(const int &u, const int &v, std::vector<int> &padres){
    padres[raiz(u, padres)] = raiz(v, padres);
}
/**
 * @brief executes de mst kruskal
 * 
 * @return std::vector<edge> 
 */
std::vector<edge> kusrkal(){
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