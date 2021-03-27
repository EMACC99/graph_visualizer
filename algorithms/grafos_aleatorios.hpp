#pragma once

#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>
#include <time.h>

#include "../includes/edge.hpp"
#include "../includes/node.hpp"
#include "kruskal.hpp"

void create_nodes(std::vector<node> &vertices, int n){
    for (int i = 0; i < n; ++i){
        node nodo;
        nodo.id = i;
        nodo.root_id = -1;
        vertices.push_back(nodo);
    }
}


void join_nodes(const int &v, const int &u, std::vector<edge>& aristas, std::vector<node> &vertices){
    edge arista;
    arista.nodes = {u,v};
    vertices[u].arista_index.push_back(aristas.size());
    vertices[v].arista_index.push_back(aristas.size());
    aristas.push_back(arista);
}

void erdos_renyi(const int n, const float p, std::vector<edge>&aristas, std::vector<node>& vertices){
    create_nodes(vertices, n);

    for (int v = 0; v < n; ++v){
        for (int u = 0; u < v; ++u){
            float f = static_cast<float> (rand())/static_cast<float> (RAND_MAX);
            if (f < p){
                edge arista;
                arista.nodes = {u,v};
                vertices[v].arista_index.push_back(aristas.size());
                vertices[u].arista_index.push_back(aristas.size());
                aristas.push_back(arista);
            }
        }
    }
}

void erdos_renyi_m(const int n, const int m, std::vector<edge>& aristas, std::vector<node> & vertices){

    create_nodes(vertices, n);

    for (int v = 0; v < n; ++v){
        for (int u = 0; u <v; ++u){
            edge arista;
            arista.nodes = {u,v};
            vertices[v].arista_index.push_back(aristas.size());
            vertices[u].arista_index.push_back(aristas.size());
            aristas.push_back(arista);
        }
    }
    // std::vector<edge>aristas2;
    // std::__sample(aristas.begin(), aristas.end(), std::back_inserter(aristas2), m,std::mt19937{std::random_device{}()});
    // sample(aristas.begin(), aristas.end(), std::back_inserter(aristas), m,std::mt19937{std::random_device{}()});

    std::random_shuffle(aristas.begin(), aristas.end()); //ordenalos aleatoriamente
    aristas.resize(m); //toma las m aristas
}

// agarra dos aristas al azar, revisa si no se forma un ciclo y unelas, eso de revisarlo es como los disjoints sets de kurskal

void arbol_aleatorio(int n, std::vector<edge> &aristas, std::vector<node> & vertices){
    create_nodes(vertices, n);

    std::vector<int> padres (vertices.size());
    
    for (auto &elem : padres)
        elem = -1;
    
    int u,v;
    while (aristas.size() < n -1){
        u = rand() % n;
        v = rand() % n;
        if (raiz(u,padres) != raiz(v, padres)){ //las funciones de raiz y de juntar estan definidas en kruskal.hpp
            // edge arista;
            // arista.nodes = {u,v};
            // vertices[v].arista_index.push_back(aristas.size());
            // vertices[u].arista_index.push_back(aristas.size());
            // aristas.push_back(arista);
            join_nodes(v,u,aristas, vertices);
            juntar(u,v,padres); 
        }
    }
}

// Para mi grafo conexo aleatorio, se me ocurre que podemos puedes tomar dos nodos al azar y unirlos con una arista, despues vuelves a tomar otros dos nodos, revisas
// si no tienen dos aristas, si no los unes, si si, escoge otro al azar. necesita tener n-1 aristas para funcionar, despues de eso, las aristas ya pueden estar en el lugar que sea


void grafo_conexo_aleatorio(int n,std::vector<edge> & aristas, std::vector<node> & vertices){ 
    
    // create_nodes(vertices, n);

    int num_aristas = rand() % 2*n + n+1 ;//no es lo mejor pero genera numeros entre n + 1 y 2n, si no le sumo el uno no me sale un gafo
    int v,u;
    arbol_aleatorio(n, aristas, vertices);
    for (int i = n;  i <  num_aristas; ++ i){ // pues tenemos que partir de algun lugar no?
        u = rand() % n;
        v = rand() % n;
        join_nodes(v,u,aristas, vertices);
    }
}