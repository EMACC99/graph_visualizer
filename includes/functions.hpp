#pragma once

#include <SFML/Graphics.hpp>
#include<vector>
#include <string>
#include "node.hpp"
#include "edge.hpp"
#include "../algorithms/grafos_aleatorios.hpp"
#include "../algorithms/kruskal.hpp"
#include "../algorithms/prim3.hpp"
#include "globals.hpp"

#define MAX_WEIGHT 25; 

sf::Sprite create_sprite(const sf::Vector2f &mouse){
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.01f, 0.01f);
    sprite.setPosition(mouse);
    return sprite;
}

void create_node(const sf::Vector2f &mouse){
    sf::Sprite sprite =  create_sprite(mouse);
    sprites.push_back(sprite);
    node vertice;
    vertice.id = vertices.size();
    vertice.x = mouse.x;
    vertice.y = mouse.y;
    vertice.root_id = -1;
    vertices.push_back(vertice);
}

bool is_sprite(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (auto &sprite : sprites){
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (bounds.contains(mouse)){
            return true;
        }
    }
    return false;
}

int get_sprite_index(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (int i = 0; i < sprites.size(); ++ i){
        sf::FloatRect bounds = sprites[i].getGlobalBounds();
        if (bounds.contains(mouse))
            return i;
    }
    return -1;
}

void assign_random_weights_to_edge(std::vector<edge> &aristas){        
    for (auto &a : aristas)
        a.peso = random() % MAX_WEIGHT;
}

void create_lineas_coloreadas(std::vector<sf::Vertex> &lineas_coloreadas, const std::vector<edge> &mst, const std::vector<sf::Sprite> &sprites, const sf::Color &color ){

    for (auto &elem: mst){
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[0]].getPosition()));
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[1]].getPosition()));
    }
    for (auto &l : lineas_coloreadas)
        l.color = color;
}

std::vector<edge> call_mst(std::vector<edge> &aristas, std::vector<node> &vertices, std::string type){
    if (aristas[0].peso == 0)
        assign_random_weights_to_edge(aristas);
    std::vector<edge> mst;
    if (vertices.size() > 0 && aristas.size() > 0){
        if (type == "Kruskal")
            mst = kusrkal(vertices,aristas);
        else if(type == "Prim")
            mst = prim(vertices,aristas);
    }
    return mst;
}

void call_erdos_rentyi(std::vector<edge> &aristas, std::vector<node> &vertices, bool m_edges = false){
    int n;
    std::cout << "Cuantos nodos quieres?: "; 
    std::cin >> n;

    if (m_edges){
        int m;
        std::cout << "Cuantas aristas?: ";
        std::cin >> m;
        erdos_renyi_m(n,m,aristas,vertices);
    }
    else{
        float p;
        std::cout << "Con cuanta probabilidad?: ";
        std::cin >> p;
        erdos_renyi(n, p, aristas, vertices);
    }
    assign_random_weights_to_edge(aristas);
}

void random_conex_graph(std::vector<edge> &aristas, std::vector<node> &vertices){
    int n;
    std:: cout << "Cuantos nodos quieres?: ";
    std::cin >> n;
    grafo_conexo_aleatorio(n, aristas, vertices);
    assign_random_weights_to_edge(aristas);
}

void call_random_tree(std::vector<edge> &aristas, std::vector<node> &vertices, bool binary_tree = false){
    int n;
    std::cout << "Cuantos nodos quieres? ";
    std::cin >> n;
    arbol_aleatorio(n, aristas, vertices);
    assign_random_weights_to_edge(aristas);
}

void display_random_graph(const sf::RenderWindow &window){
                                
        sf::Vector2u win_size = window.getSize();
        for (auto &v : vertices){
            float x = static_cast<float> (rand()) / static_cast <float> (RAND_MAX/(win_size.x - 50));
            float y = static_cast<float> (rand()) / static_cast <float> (RAND_MAX/(win_size.y - 50));
            v.x = x;
            v.y = y;
            sf::Vector2f pos(x,y);
            sf::Sprite sprite = create_sprite(pos);
            sprites.push_back(sprite);
        }

        for (auto &e: aristas){
            float nodo1_x = vertices[e.nodes[0]].x;
            float nodo1_y = vertices[e.nodes[0]].y;

            float nodo2_x = vertices[e.nodes[1]].x;
            float nodo2_y = vertices[e.nodes[1]].y;

            sf::Vector2f pos1 (nodo1_x,nodo1_y);
            sf::Vector2f pos2 (nodo2_x, nodo2_y);
            lineas.push_back(sf::Vertex(pos1));
            lineas.push_back(sf::Vertex(pos2));
        }
}