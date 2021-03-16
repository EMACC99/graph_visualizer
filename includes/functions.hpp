#include <SFML/Graphics.hpp>
#include<vector>
#include "node.hpp"
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