#pragma once

#include <set>
#include <cmath>

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
    return std::sqrt(n.heigth) - 1;
}

void factor_desconposition(const std::vector<int> &padres, node &u, node &v){
    return;
}
