#pragma once

#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "../includes/globals.hpp"

bool cycles = false;
/**
 * @brief Get the list of neighbours
 * 
 * @param v 
 * @return std::vector<int> 
 */
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

/**
 * @brief check if there is a cicle in the nodes
 * 
 * @param root 
 * @param parents 
 * @param hijos 
 * @return true 
 * @return false 
 */
bool has_cicles(const node &root, const std::vector<int> &parents, const std::vector<int> &hijos){
    //si mi vecino ya tiene padre, y ese vecino no es mi papa -> hay ciclo
    for (auto &hijo: hijos){
        if (parents[hijo] != -1 && hijo != parents[root.id])
            return true;
    }
    return false;
}
/**
 * @brief 
 * 
 * @param root 
 * @param parents 
 */
void assign_parents(node &root, std::vector<int> &parents){
    //Encontrar padres dado la raiz del arbol
    std::vector<int> hijos = get_vecinos(root);
    if (has_cicles(root, parents, hijos)){
        cycles = true;
        return;
    }

    for (auto &hijo :hijos){
        if (parents[vertices[hijo].id] == -1){
            parents[vertices[hijo].id] = root.id;
            vertices[hijo].heigth = root.heigth + 1;
            assign_parents(vertices[hijo], parents);
            if (cycles)
                return; 
        }
    }
}
/**
 * @brief Construct a new std::vector<int>get parents object
 * 
 * @param root 
 */
std::vector<int>get_parents(node & root){
    std::vector<int> parents(vertices.size(), -1);
    parents[root.id] = -2;
    root.heigth = 0;
    std::vector<int> hijos = get_vecinos(root);
    for (auto &hijo : hijos){
        if (parents[vertices[hijo].id] == -1){
            parents[vertices[hijo].id] = root.id;
            vertices[hijo].heigth = root.heigth + 1;
            assign_parents(vertices[hijo], parents);
        }
    }
    // std::max_element(parents.begin(), parents.end());
    parents[root.id] = -1;
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].padre = parents[i];

    if (cycles){
        parents.clear();
        for (auto &n : vertices){
            n.heigth = 0;
            n.padre = -1;
        }
    }

    return parents;
}
/**
 * @brief 
 * 
 * @param v
 * @param colores
 * @param color
 */
void pintar_componente(const node &v, std::vector<int> &colores, const int &color){
    colores[v.id] = color;
    std::vector<int> vecinos = get_vecinos(v);
    for (auto &u : vecinos){
        if (colores[vertices[u].id] == -1)
            pintar_componente(vertices[u],colores,color);
    }
}
/**
 * @brief finds the number of conex compoents and paint them
 * 
 * @return std::pair<std::vector<int>,unsigned int> 
 */
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