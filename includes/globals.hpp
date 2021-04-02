#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "edge.hpp"
#include "node.hpp"
//index para mover el sprite interactivamente
int global_sprite_index;

//banderas para la interactividad
bool sprite_selected = false;
bool mouse_button_pressed = false;
std::string mouse_button = "";

//cosas para dibujar
sf::Texture texture;
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