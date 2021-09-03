#pragma once

#include <list>

#include "../includes/globals.hpp"
#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "componentes_conexas.hpp" // de aqui sacamos get vecinos


std::vector<int> apareamientos_iniciales(){
    // lo mas facil de hacer, pues es agarrar un nodo y juntarlo con su vecino, revisando que no esten apareados anteriormente

    std::vector<int> matches(vertices.size(), -1);
    for (auto &n : vertices){
        for (auto &h : get_vecinos(n)){
            if (matches[h] == -1 && matches[n.id] == -1){
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
            if (!visited[v] && matches[v] == -1)
                queue.push_back(v);
        }
    }
    // std::vector<int> matches(vertices.size(), 0);

    // ahora necesito ver quien esta matcheado con quien
    // para eso, tengo dos opciones, generar un vector de aristas y decir que tienen match, mas facil, o
    // generar un vector de nodos que digan que esos dos estan mathcheados
    for (int i = 1; i < caminito_bfs.size(); i += 2){
        matches[caminito_bfs[i - 1]] = matches[caminito_bfs[i]];
        matches[caminito_bfs[i]] = matches[caminito_bfs[i - 1]];
    }

    return matches;
}   


node get_first_not_matched_node(std::vector<int> &matches){
    node not_matched;
    not_matched.id = -2; // if the id is -2 there no more matchings
    for (int i = 0; i < matches.size(); ++i){
        if (matches[i] == -1){
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

    //ahora tenemos que sacar el nuevo camino de aumento con bfs
    // lo que le tenemos que pasar es un nodo que no este en initial_matches

    node first_not_matches = get_first_not_matched_node(inital_matches);

    if (first_not_matches.id == -2)
        return inital_matches;

    std::vector<int> matches = bfs(first_not_matches, inital_matches);

    while (matches != inital_matches){
        inital_matches = matches;
        node first_not_matches = get_first_not_matched_node(inital_matches);
        matches = bfs(first_not_matches, inital_matches);
    }

    return matches;
}