#pragma once

#include <set>
#include <cmath>
#include <map>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"
#include "../includes/globals.hpp"


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
    return (int)std::sqrt(n.heigth) - 1;
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
