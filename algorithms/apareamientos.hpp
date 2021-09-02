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


std::vector<int> bfs(const node &root, std::vector<int> &matches){ 
    std::vector <int> caminito_bfs;
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> queue;

    visited[root.id] = true;

    queue.push_back(root.id);
    while(!queue.empty()){
        int s = queue.front();
        caminito_bfs.push_back(s);
        queue.pop_back();
        for (auto &v : get_vecinos(vertices[s])){
            if (!visited[v] && matches[v] == 0)
                queue.push_back(v);
        }
    }
    return caminito_bfs;
}   


node get_first_not_matched_node(std::vector<int> &matches){
    node not_matched;

    for (int i = 0; i < matches.size(); ++i){
        if (matches[i] == 0){
            not_matched = vertices[i];
            break;
        }
    }

    return not_matched;
}

std::vector<int> apareamientos(){
    // primero, tenemos que hacer los apareamientos iniciales
    std::vector<int> inital_matches = apareamientos_iniciales();
    std::vector<bool> visited(vertices.size(), false);
    // std::vector<int> caminito_bfs = bfs(vertices[inital_matches[0]]);
    //ahora tenemos que sacar el nuevo camino de aumento con bfs
    // lo que le tenemos que pasar es un nodo que no este en initial_matches
    node first_not_matches = get_first_not_matched_node(inital_matches);
    std::vector<int> matches = bfs(first_not_matches, inital_matches);
    while (matches != inital_matches){
        inital_matches = matches;
        node first_not_matches = get_first_not_matched_node(inital_matches);
        matches = bfs(first_not_matches, inital_matches);
    }

    return matches;
}