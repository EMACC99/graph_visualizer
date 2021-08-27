#pragma once

#include <set>
#include <cmath>
#include <map>
#include <unordered_map>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"
#include "../includes/globals.hpp"

#include "componentes_conexas.hpp" //de aqui importamos la de get vecinos


node lca_naive(const std::vector<int> &padres, node &u, node &v){
    std::vector<node> ancestros_u {u};
    while (padres[u.id] != -1){ //mientras no sea la raiz
        ancestros_u.push_back(vertices[padres[u.id]]);
        u = vertices[padres[u.id]];
    }
    std::set<node, node_compare> ancestros_u_set (ancestros_u.begin(), ancestros_u.end());

    if (ancestros_u_set.find(v) != ancestros_u_set.end())
        return v;
    
    while (padres[v.id] != -1){
        v = vertices[padres[v.id]];
        if (ancestros_u_set.find(v) != ancestros_u_set.end())
            return v;
    }
}


int caclulate_section(const node &n){
    return ceil(std::sqrt(n.heigth)) - 1;
}

void assing_section(){
    for (auto &n : vertices)
        n.section = caclulate_section(n);
}

void assingn_to_b(std::vector<node> &B, const node &u, const node &p){
    if (u.section != p.section)
        B[u.id] = p;
    else
        B[u.id] = B[p.id];
}


node level_node (const node &u, node v, const std::vector<node> B){
    while(v.heigth > u.heigth)
        v = B[v.id];

    return v;
}

node factor_deconposition(const std::vector<int> &padres, node &u, node &v){
    assing_section();
    std::vector<node> B(vertices.size());
    for (int i = 0; i< padres.size(); ++i){
        if (padres[i] != -1){
            node u_h = vertices[i];
            node p = vertices[padres[i]];
            assingn_to_b(B, u_h, p);
        }
        else
            B[i] = vertices[i];
    }

    if (u.heigth > v.heigth)
        v = level_node(u, v, B);
    else
        u = level_node(v, u, B);

    while (B[u.id].id != B[v.id].id){ //Tengo que repetir hasta que sean iguales
        
        u = B[u.id];
        v = B[v.id];

    }
    if (u.id == -1){
        std::cout << "RIP" << std::endl;
        return u;
    }
    
    return lca_naive(padres, B[u.id], B[v.id]); //hay que hacer el LCA naive hasta B[u];
}

std::vector<unsigned int> get_2i_ancestors(const std::vector<int> &parents, node &u){
    std::vector<unsigned int> ancestros;
    //TODO ver como poner los 2i ancestros en un arreglo de arreglos ~~no se me ocurrio nada, pero luego veo que onda~~
    return ancestros;
}


std::vector<node> ancestros_potencias_de_dos(const std::vector<int> &padres, node &u, node &v){
    std::vector<node> vertices_por_nivel = vertices;
    std::sort(vertices_por_nivel.begin(), vertices_por_nivel.end(),
    [](const node &i, const node &j){
        return i.heigth < j.heigth;
    });
    std::vector<std::vector<unsigned int>> ancentros (vertices.size());
    for (int i = 0; i < vertices.size(); ++i){
        ancentros.at(i) = get_2i_ancestors(padres, vertices_por_nivel[i]);
    }
}

//Range minimum query

void dfs(std::map<int, bool> &visitado, std::vector<int> &caminito, const node &root){
    // aqui hacemos el dfs recursivo para obtener el caminito
    // no lo hice usando los otros que tenia porque me sirve de practica
    std::vector<int> hijitos = get_vecinos(root);
    for (auto hijito : hijitos){
        if (!visitado[hijito]){
            caminito.push_back(hijito);
            dfs(visitado, caminito, vertices[hijito]);
        }
    }
    
}

std::vector<int> generate_array_with_dfs(std::map<int, bool> &visitado, const node &root, const std::vector<std::pair<int, int>> &parents_with_index ){
    std::vector<int> caminito;
    std::vector<int> hijos = get_vecinos(root);
    visitado[root.id] = true;

    for (auto &h : hijos){
        if(!visitado[h]){
            caminito.push_back(h);
            dfs(visitado, caminito, vertices[h]);
        }
    }
    return caminito;
}


std::vector<int> get_min_index_for_rmq(const std::vector<int> &a, const int start_index){
    std::vector<int> min_indexes;
    for (int i = 0; std::pow(2, i) < a.size(); ++i){ //hay que guardar los menores indices
            std::vector<int>::const_iterator it_begin = a.begin() + start_index;
            std::vector<int>::const_iterator it_end  = a.begin() + (int)std::pow(2,i);
            std::vector<int> aux (it_begin, it_end);
            min_indexes.push_back(std::min_element (aux.begin(), aux.end(), [](const int &i, const int &j){ return vertices[i].heigth < vertices[j].heigth;}) - aux.begin());
    }
    return min_indexes;
}

node range_minimum_query(const std::vector<int>  &padres, node &u, node &v){
    // localizar el sub arreglo que me de el caminito de vertices
    //generar un arreglo recorriendo todo el arbol con DFS
    // usar rmq para saber el LCA dados dos nodos
    //profit

    //cosas para el dfs
    std::map<int, bool> visitado;
    std::vector<std::pair<int, int>> parents_with_index;
    for (int i = 0; i < padres.size(); ++i)
        parents_with_index.push_back({i, padres[i]});
    
    std::sort(parents_with_index.begin(), parents_with_index.end(), 
    [](const std::pair<int, int>&i, const std::pair<int, int>&j){
        return i.second < j.second;
    }
    );

    node root = vertices[parents_with_index[0].second];

    std::vector<int> caminito = generate_array_with_dfs(visitado, root, parents_with_index);
    
    std::vector<std::vector<int>> min_indexes;
    for (int i = 0; i < caminito.size(); ++i)
        min_indexes.push_back(get_min_index_for_rmq(caminito, i)); //O(n^2) ik, buy i don't have any other ideas
    
    auto u_index_it = std::find(caminito.begin(), caminito.end(), u.id);
    
    auto v_index_it = std::find(caminito.begin(), caminito.end(), v.id);

    int u_index = u_index_it - caminito.begin();

    int v_index = v_index_it - caminito.begin();

    node LCA;

    if (u_index < v_index){
        std::vector<int> bla = min_indexes[u_index];
        int index_mas_cercano = static_cast<int> (round(log(v_index)/log(2)));

    }
    else{
        std::vector<int> bla = min_indexes[v_index];
        int index_mas_cercano = static_cast<int> (round(log(u_index)/log(2)));  
        
    }

    return LCA;
}