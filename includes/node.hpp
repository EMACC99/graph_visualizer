#pragma once
#include <vector>
#include <algorithm>

struct node{
        int root_id;
        int id;
        float x,y;
        // std::vector<int> vecinos;
        std::vector <int> arista_index; // de la lista de aristas, pon los que le corresponden, moejor dicho, todas la aristas que salen del vertice
};

// node::node(int node_id, const sf::Vector2f &position){
//     id = node_id;
//     x = position.x;
//     y = position.y;
// } 
