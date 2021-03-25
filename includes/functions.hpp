#include <SFML/Graphics.hpp>
#include<vector>
#include "node.hpp"
#include "edge.hpp"
#include "../algorithms/grafos_aleatorios.hpp"

#pragma once
sf::Sprite create_sprite(const sf::Texture &texture, const sf::Vector2f &mouse){
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.01f, 0.01f);
    sprite.setPosition(mouse);
    return sprite;
}

std::vector<sf::Sprite> node_to_sprites(const std::vector<node> nodes, const sf::Texture &texture){
    std::vector<sf::Sprite> sprites;
    for (auto &n : nodes){
        sf::Sprite sprite = create_sprite(texture, sf::Vector2f(n.x,n.y));
        sprites.push_back(sprite);
    }
    return sprites;
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
}

void display_erdos_rentyi(std::vector<edge> &aristas, std::vector<node> &vertices, std::vector<sf::Sprite> &sprites, std::vector<sf::Vertex> &lineas,
                            const sf::RenderWindow &window, const sf::Texture &texture){
                                
        sf::Vector2u win_size = window.getSize();
        for (auto &v : vertices){
            float x = static_cast<float> (rand()) / static_cast <float> (RAND_MAX/(win_size.x - 50));
            float y = static_cast<float> (rand()) / static_cast <float> (RAND_MAX/(win_size.y - 50));
            v.x = x;
            v.y = y;
            sf::Vector2f pos(x,y);
            sf::Sprite sprite = create_sprite(texture, pos);
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