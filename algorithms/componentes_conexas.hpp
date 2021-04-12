#pragma once

#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "../includes/globals.hpp"

std::vector<int> get_vecinos(const node &v){
    std::vector<int> vecinos;
    for (auto &a_index : v.arista_index){
        if (vertices[aristas[a_index].nodes[0]].id != v.id)
            vecinos.push_back(vertices[aristas[a_index].nodes[0]].id);
        else
            vecinos.push_back(vertices[aristas[a_index].nodes[1]].id);
    }
    return vecinos;
}

bool is_tree(){
    // se me ocurren dos cosas, una es detectar ciclos, y la otra es usar DFS como si fuera un arbol y si turena pues es que no es arbol
    return true;
}

void assign_parents(node &root, std::vector<int> &parents){
    //Encontrar padres dado la raiz del arbol
    std::vector<int> hijos = get_vecinos(root);
    for (auto &hijo :hijos){
        if (parents[root.id] == -1){
            parents[vertices[hijo].id] = root.id;
            assign_parents(vertices[hijo], parents);
        }
    }
}

std::vector<int>get_parents(node & root){
    std::vector<int> parents(vertices.size(), -1);
    parents[root.id] = -1;
    std::vector<int> hijos = get_vecinos(root);
    for (auto &hijo : hijos){
        if (parents[vertices[hijo].id] == -1){
            parents[vertices[hijo].id] = root.id;
            assign_parents(vertices[hijo], parents);
        }
    }
    std::max_element(parents.begin(), parents.end());
    return parents;
}

void pintar_componente(const node &v, std::vector<int> &colores, const int &color){
    colores[v.id] = color;
    std::vector<int> vecinos = get_vecinos(v);
    for (auto &u : vecinos){
        if (colores[vertices[u].id] == -1)
            pintar_componente(vertices[u],colores,color);
    }
}

std::pair<std::vector<int>,unsigned int> componentes_conexas(){
    std::vector<int> colores(vertices.size(), -1);
    unsigned int color = 0;
    for (auto &v : vertices){
        if (colores[v.id] == -1){
            pintar_componente(v, colores, color);
            color += 1;
        }
    }
    return{colores, color};
}