#pragma once

#include <list>

#include "../includes/globals.hpp"
#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "componentes_conexas.hpp" // de aqui sacamos get vecinos


std::vector<int> apareamientos_iniciales(){
    // lo mas facil de hacer, pues es agarrar un nodo y juntarlo con su vecino, revisando que no esten apareados anteriormente

    std::vector<int> matches(vertices.size(), 0);
    for (auto &n : vertices){
        for (auto &h : get_vecinos(n)){
            if (matches[h] == 0 && matches[n.id] == 0){
                matches[h] = n.id;
                matches[n.id] = h;
                break;
            }
        }
    }
    return matches;
}


void bsf(const node &root){
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> queue;

    visited[root.id] = true;

    queue.push_back(root.id);

    std::vector<int> vecinos = get_vecinos(root);


}   

std::vector<node> apareamientos(){
    // primero, tenemos que hacer los apareamientos iniciales
    std::vector<int> inital_matches = apareamientos_iniciales();
    
}