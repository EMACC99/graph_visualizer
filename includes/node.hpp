#pragma once
#include <vector>
#include <algorithm>

struct node{
        int root_id;
        int id;
        float x,y;
        std::vector <int> arista_index; // de la lista de aristas, pon los que le corresponden, moejor dicho, todas la aristas que salen del vertice
};
