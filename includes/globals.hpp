#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "edge.hpp"
#include "node.hpp"

//index para mover el sprite interactivamente
int global_sprite_index;

//banderas para la interactividad
bool sprite_selected = false;
std::string mouse_button = "";

bool is_test = false;

//cosas para dibujar
sf::Texture blue_circle;
sf::Texture red_circle;
sf::Font font;

std::vector<sf::Text> textos_peso;

std::vector<sf::Vertex> lineas_coloreadas;
std::vector<sf::Sprite> sprites;

std::vector<sf::Vertex> lineas;
std::vector<sf::Vector2f> mouse_points;
std::vector<std::vector<sf::Vector2f>> connected_lines;
std::vector<std::vector<int>> connected_nodes_index;
std::vector<int> node_index;
std::vector<int> modified_lines_index;

//cosas del grafo
std::vector<node> vertices;
std::vector<edge> aristas;

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2){
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}