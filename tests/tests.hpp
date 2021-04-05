#pragma once

#include <string>

#include "../algorithms/prim3.hpp"
#include "../algorithms/kruskal.hpp"

#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "../includes/globals.hpp"


void test(){
    /* 
    primero, vamos a crear el grafo, la representacion del grafo esta dada por (nodo1, peso, nodo2)
    (0,1,2);
    (0,3,3);
    (1,2,2);
    (1,5,4);
    (2,10,4);
    (3,7,4);
    */
    for (int i = 0; i<5; ++i){
        node vertice;
        vertice.id = i;
        vertice.root_id = -1;
        vertices.push_back(vertice);
    }

    edge arista1;
    arista1.peso = 1;
    arista1.nodes = std::vector<int> {0,2};
    vertices[0].arista_index.push_back(aristas.size());
    vertices[2].arista_index.push_back(aristas.size());
    aristas.push_back(arista1);
    
    edge arista2;
    arista2.peso = 3;
    arista2.nodes = std::vector<int> {0,3};
    vertices[0].arista_index.push_back(aristas.size());
    vertices[3].arista_index.push_back(aristas.size());
    aristas.push_back(arista2);
    
    edge arista3;
    arista3.peso = 2;
    arista3.nodes = std::vector<int> {1,2};
    vertices[2].arista_index.push_back(aristas.size());
    vertices[1].arista_index.push_back(aristas.size());
    aristas.push_back(arista3);
    
    edge arista4;
    arista4.peso = 5;
    arista4.nodes = std::vector<int> {1,4};
    vertices[1].arista_index.push_back(aristas.size());
    vertices[4].arista_index.push_back(aristas.size());
    aristas.push_back(arista4);

    edge arista5;
    arista5.peso = 10;
    arista5.nodes = std::vector<int> {2,4};
    vertices[2].arista_index.push_back(aristas.size());
    vertices[4].arista_index.push_back(aristas.size());
    aristas.push_back(arista5);

    edge arista6;
    arista6.peso = 7;
    arista6.nodes = std::vector<int> {3,4};
    vertices[3].arista_index.push_back(aristas.size());
    vertices[4].arista_index.push_back(aristas.size());
    aristas.push_back(arista6);

    std::vector<edge> prim_mst = prim();
    std::vector<edge> kruskal_mst = kusrkal();

    std::cout << "Grafica formada por prim" << std::endl;
    for (auto &p : prim_mst){
        std::cout << "(" << p.nodes[0]<< "," << p.peso << ","<< p.nodes[1] << ")";
    }
    std::cout << std::endl;

    std::cout<< "Grafica formada por Kruskal" << std::endl;
    for (auto &k : kruskal_mst){
        std::cout << "(" << k .nodes[0] << "," << k.peso << "," <<k.nodes[1] << ")";
    }
    std::cout << std::endl;
}