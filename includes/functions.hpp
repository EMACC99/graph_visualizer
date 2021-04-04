#pragma once

#include <SFML/Graphics.hpp>

#include "node.hpp"
#include "edge.hpp"
#include "globals.hpp"

#include "../algorithms/grafos_aleatorios.hpp"
#include "../algorithms/kruskal.hpp"
#include "../algorithms/prim3.hpp"

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

void get_lines_to_modify(){
    if (lineas.size() > 0){
        for (int i = 0; i < lineas.size(); ++i){
            if (sprites[global_sprite_index].getGlobalBounds().contains(lineas[i].position))
                modified_lines_index.push_back(i);
        }
    }
}

void modify_sprite_position(const sf::Vector2f &mouse){
    sprites[global_sprite_index].setPosition(mouse);
    vertices[global_sprite_index].x = mouse.x;
    vertices[global_sprite_index].y = mouse.y;

    if(modified_lines_index.size() > 0){
        for (int i = 0; i < modified_lines_index.size(); ++i)
            lineas[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
    }
    sprite_selected = true;
}

void assign_random_weights_to_edge(){        
    for (auto &a : aristas)
        a.peso = random() % MAX_WEIGHT;
}

void create_lineas_coloreadas(const std::vector<edge> &mst, const sf::Color &color ){

    for (auto &elem: mst){
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[0]].getPosition()));
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[1]].getPosition()));
    }
    for (auto &l : lineas_coloreadas)
        l.color = color;
}

void create_text_to_display(){
    for (auto &arista : aristas){
        sf::Text texto;
        texto.setFont(font);
        texto.setString(std::to_string(arista.peso));
        texto.setCharacterSize(16);
        texto.setFillColor(sf::Color::Blue);
        textos_peso.push_back(texto);
    }
}

void update_text_position(){
    float new_x_1, new_x_2, new_y_1,new_y_2, new_text_x, new_text_y;
    for (int i = 0; i < aristas.size();  ++i){ //en teoria, los arreglos del texto y de las aristas son de la misma longitud
        new_x_1 = vertices[aristas[i].nodes[0]].x;
        new_y_1 = vertices[aristas[i].nodes[0]].y;

        new_x_2 = vertices[aristas[i].nodes[1]].x;
        new_y_2 = vertices[aristas[i].nodes[1]].y;

        new_text_x = (new_x_1 + new_x_2)/2;
        new_text_y = (new_y_1 + new_y_2)/2;
        
        textos_peso[i].setPosition(sf::Vector2f {new_text_x, new_text_y});
    }
}

std::vector<edge> call_mst(std::string type){
    if (aristas[0].peso == 0)
        assign_random_weights_to_edge();
    std::vector<edge> mst;
    if (vertices.size() > 0 && aristas.size() > 0){
        if (type == "Kruskal")
            mst = kusrkal();
        else if(type == "Prim")
            mst = prim();
    }
    return mst;
}

void call_erdos_rentyi(bool m_edges = false){
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
    assign_random_weights_to_edge();
    create_text_to_display();
}

void call_random_conex_graph(){
    int n;
    std:: cout << "Cuantos nodos quieres?: ";
    std::cin >> n;
    grafo_conexo_aleatorio(n, aristas, vertices);
    assign_random_weights_to_edge();
    create_text_to_display();
}

void call_random_tree(bool binary_tree = false){
    int n;
    std::cout << "Cuantos nodos quieres? ";
    std::cin >> n;
    arbol_aleatorio(n, aristas, vertices);
    assign_random_weights_to_edge();
    create_text_to_display();
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