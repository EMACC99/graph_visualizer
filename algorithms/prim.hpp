#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "../includes/node.hpp"
#include "../includes/edge.hpp"

#pragma once

int get_min_arista(const std::vector<edge> &aristas){
    int min = 0;
    for (int i = 0; i < aristas.size(); ++i){
        if (aristas[i].peso < aristas[min].peso)
            min = i;
    }
    return min;
}


std::vector<edge> prim(const std::vector<node> &vertices, std::vector<edge> aristas){
    int vertice_aleatorio = rand() % vertices.size();
    std::vector<int> vectices_explorados {vertice_aleatorio}; //mis vertices explorados
    std::vector<int> aristas_por_explorar {vertices[vertice_aleatorio].arista_index}; //las aristas por explorar
    std::vector<edge> arbol; //mi arbol, que va a guardar las aristas
    std::vector<int> vertices_de_arista;
    int min_arista_index;
    edge arista;

    while (aristas_por_explorar.size() > 0){
        min_arista_index = get_min_arista(aristas);
        arista = aristas[min_arista_index];
        aristas.erase(aristas.begin() + min_arista_index);


        vertices_de_arista = arista.nodes;
        if(std::find(vectices_explorados.begin(), vectices_explorados.end(), vertices_de_arista[0]) == vectices_explorados.end()){ //si no esta uno, esta el otro
            arbol.push_back(arista);
            vectices_explorados.push_back(vertices_de_arista[0]);
            std::vector <int> nuevas_aristas = vertices[vertices_de_arista[0]].arista_index;
            for (int i = 0; i < nuevas_aristas.size(); ++i){
                if(std::find(vectices_explorados.begin(), vectices_explorados.end(), aristas[nuevas_aristas[i]].nodes[0]) == vectices_explorados.end())
                    aristas_por_explorar.push_back(nuevas_aristas[i]);
                
                else if (std::find(vectices_explorados.begin(), vectices_explorados.end(), aristas[nuevas_aristas[i]].nodes[1]) == vectices_explorados.end())
                    aristas_por_explorar.push_back(nuevas_aristas[i]);
            }

        }
        else if (std::find(vectices_explorados.begin(), vectices_explorados.end(), vertices_de_arista[1]) == vectices_explorados.end()){
            arbol.push_back(arista);
            vectices_explorados.push_back(vertices_de_arista[0]);
            std::vector <int> nuevas_aristas = vertices[vertices_de_arista[0]].arista_index;
            for (int i = 0; i < nuevas_aristas.size(); ++i){
                if(std::find(vectices_explorados.begin(), vectices_explorados.end(), aristas[nuevas_aristas[i]].nodes[0]) == vectices_explorados.end())
                    aristas_por_explorar.push_back(nuevas_aristas[i]);
                
                else if (std::find(vectices_explorados.begin(), vectices_explorados.end(), aristas[nuevas_aristas[i]].nodes[1]) == vectices_explorados.end())
                    aristas_por_explorar.push_back(nuevas_aristas[i]);
            }
        }
    }
    return arbol;
} 