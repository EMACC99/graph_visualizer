#pragma once

#include <unordered_map>

#include "node.hpp"
#include "edge.hpp"
#include "globals.hpp"

#include "../algorithms/grafos_aleatorios.hpp"
#include "../algorithms/kruskal.hpp"
#include "../algorithms/prim3.hpp"
#include "../algorithms/componentes_conexas.hpp"
#include "../algorithms/LCA.hpp"
#include "../algorithms/apareamientos.hpp"

#define MAX_WEIGHT 25; 
//fuciones de ayuda para dibujar y ser interactivos
/**
 * @brief Creates a sprite
 * 
 * @param mouse 
 * @return sf::Sprite 
 */
sf::Sprite create_sprite(const sf::Vector2f &mouse){
    sf::Sprite sprite;
    sprite.setTexture(blue_circle);
    sprite.setScale(0.01f, 0.01f);
    sprite.setPosition(mouse);
    return sprite;
}

void make_sprite_red(sf::Sprite &sprite){
    sprite.setTexture(red_circle);
    sprite.setScale(0.04f, 0.04f);
}

void make_sprite_blue(sf::Sprite &sprite){
    sprite.setTexture(blue_circle);
    sprite.setScale(0.01f, 0.01f);
}
/**
 * @brief Creates a node
 * 
 * @param mouse 
 */
void create_node(const sf::Vector2f &mouse){
    sf::Sprite sprite =  create_sprite(mouse);
    sprites.push_back(sprite);
    node vertice;
    vertice.id = vertices.size();
    vertice.x = mouse.x;
    vertice.y = mouse.y;
    vertice.padre = -1;
    vertices.push_back(vertice);
}
/**
 * @brief Checks if it is a sprite
 * 
 * @param mouse 
 * @param sprites 
 * @return true 
 * @return false 
 */
bool is_sprite(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (auto &sprite : sprites){
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (bounds.contains(mouse)){
            return true;
        }
    }
    return false;
}
/**
 * @brief Get the index of the current sprite from the sprites list
 * 
 * @param mouse 
 * @param sprites the list of sprites 
 * @return int 
 */
int get_sprite_index(const sf::Vector2f &mouse, const std::vector<sf::Sprite> &sprites){
    for (int i = 0; i < sprites.size(); ++ i){
        sf::FloatRect bounds = sprites[i].getGlobalBounds();
        if (bounds.contains(mouse))
            return i;
    }
    return -1;
}
/**
 * @brief Get the lines to modify
 * 
 */
void get_lines_to_modify(){
    if (lineas.size() > 0){
        for (int i = 0; i < lineas.size(); ++i){
            if (sprites[global_sprite_index].getGlobalBounds().contains(lineas[i].position))
                modified_lines_index.push_back(i);
        }
    }
}
/**
 * @brief modifies the position of the sprite selected
 * 
 * @param mouse 
 */
void modify_sprite_position(const sf::Vector2f &mouse){ //move to visualizer
    sprites[global_sprite_index].setPosition(mouse);
    vertices[global_sprite_index].x = mouse.x;
    vertices[global_sprite_index].y = mouse.y;

    if(modified_lines_index.size() > 0){
        for (int i = 0; i < modified_lines_index.size(); ++i)
            lineas[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
    }
    sprite_selected = true;
}
/**
 * @brief assigns random weights to the edges
 * 
 */
void assign_random_weights_to_edge(){        
    for (auto &a : aristas)
        a.peso = std::rand() % MAX_WEIGHT + 1;
}
//colorear aristas del mst
/**
 * @brief Create a lineas coloreadas from mst
 * 
 * @param mst Prim or Kruskal
 * @param color sf::Color
 */
void create_lineas_coloreadas(const std::vector<edge> &mst, const sf::Color &color = sf::Color::Red){ //move to visualizer

    for (auto &elem: mst){
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[0]].getPosition()));
        lineas_coloreadas.push_back(sf::Vertex(sprites[elem.nodes[1]].getPosition()));
    }
    for (auto &l : lineas_coloreadas)
        l.color = color;
}

//colorear aritas de compoenetes conexas
/**
 * @brief Random Colorsfor coloring the conex components
 * 
 * @param colores 
 */
void color_conex_components(const std::pair<std::vector<int>, unsigned int> &colores){ //move to visualizer
    //definimos los colores para dibujar las componentes conexas
    std::vector<sf::Color> drawing_colors;
    uint8_t r,g,b; //uint8_t porque pues un color es de 8 bits por canal
    for (int i = 0; i < colores.second; ++i){ //agarramos colores al azar
        r = static_cast<uint8_t> (rand() % 255);
        g = static_cast<uint8_t> (rand() % 255);
        b = static_cast<uint8_t> (rand() % 255);
        drawing_colors.push_back(sf::Color (r,g,b));
    }

    int u,v;
    for (auto &arista: aristas){
        sf::Color color = drawing_colors[colores.first[arista.nodes[0]]];
        sf::Vertex linea_coloreada_1, linea_coloreada_2;
        linea_coloreada_1.position = sprites[arista.nodes[0]].getPosition();
        linea_coloreada_1.color = color;

        linea_coloreada_2.position = sprites[arista.nodes[1]].getPosition();
        linea_coloreada_2.color = color;

        lineas_coloreadas.push_back(linea_coloreada_1);
        lineas_coloreadas.push_back(linea_coloreada_2);
    }
}
//texto
/**
 * @brief Creates the text to be displayed
 * 
 */
void create_text_to_display(){ //move to visualizer
    for (auto &arista : aristas){
        sf::Text texto;
        texto.setFont(font);
        texto.setString(to_string_with_precision(arista.peso)); //funcion en globals.hpp
        texto.setCharacterSize(16);
        texto.setFillColor(sf::Color::Blue);
        textos_peso.push_back(texto);
    }
}
/**
 * @brief 
 * 
 */
void update_text_position(){ //move to visualizer
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
//llamar algoritmos
/**
 * @brief handles the calling fot the Prim adn Kruskal Algorithms
 * 
 * @param type 
 * @return std::vector<edge> 
 */
std::vector<edge> call_mst(std::string type){
    if (aristas[aristas.size() - 1].peso == 0)
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
/**
 * @brief handles the inputs and callig of both types of the erdos rentyi algorithm
 * 
 * @param m_edges 
 */
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
/**
 * @brief handles the inputs and calling for the random conex graph inplementations
 * 
 */
void call_random_conex_graph(){
    int n;
    std:: cout << "Cuantos nodos quieres?: ";
    std::cin >> n;
    grafo_conexo_aleatorio(n, aristas, vertices);
    assign_random_weights_to_edge();
    create_text_to_display();
}
/**
 * @brief call the random tree implementation
 * 
 * @param binary_tree 
 */
void call_random_tree(bool binary_tree = false){
    int n;
    std::cout << "Cuantos nodos quieres? ";
    std::cin >> n;
    arbol_aleatorio(n, aristas, vertices);
    // assign_random_weights_to_edge();
    // create_text_to_display();
}
/**
 * @brief calls the get_parents function for trees
 * 
 * @return std::vector<int> 
 */
std::vector<int> call_get_parents(){
    int root_index;
    std::cout << "quien es la raiz? ";
    std::cin  >> root_index;
    return get_parents(vertices[root_index]);
}

node call_lca(const std::vector<int> &padres){
    int v_id,u_id;
    std::cout << "Id del primer nodo: ";
    std::cin >> v_id;
    std::cout << "Id del segundo nodo: ";
    std::cin >> u_id;
    node u = vertices[u_id],v = vertices[v_id];
    
    // return lca_naive(padres, u, v);
    return factor_deconposition(padres, u, v);
}

std::vector<edge> call_bipartite_matching(){
    std::vector<int> matches = apareamientos();
    std::vector<edge> bipartite_edges;
    
    int size = matches.size()/2;
    for (int i = 0; i < size; ++i){
        edge a;
        std::vector<int> nodes;
        nodes.push_back(i);
        nodes.push_back(matches[i]);
        a.nodes = nodes;
        a.colored = true;
        bipartite_edges.push_back(a);
    } 
    return bipartite_edges;
}

//dar parametros para el visualizador para dibujar cosas en lugares random
/**
 * @brief  displays the components in random positions on the canvas
 * 
 * @param window 
 */
void display_graph(const sf::RenderWindow &window){ //move to visualizer
                                
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
/**
 * @brief 
 * 
 * @param parents_with_index
 * @param window 
 */
void display_tree_by_parents(std::vector<std::pair<int, int>> parents_with_index, const sf::RenderWindow &window){ //move to visualizer
    sf::Vector2u win_size = window.getSize();
    
    std::sort(parents_with_index.begin(), parents_with_index.end(),  //los ordenamos por padre
    [](const std::pair<int, int>&i, const std::pair<int, int>&j){
        return i.second < j.second;
    }
    );

    //asignamos los niveles a los nodos
    // assing_level_to_node(vertices, parents_with_index);
    // ahora tengo que contar cuantos nodos tiene cada nivel para repartirlo en la visualizacion
    std::unordered_map<int, int> nodes_by_level = {};
    for (int i = 0; i < vertices.size(); ++i){
        std::unordered_map<int, int>::iterator it = nodes_by_level.find(vertices[i].heigth);
        if (it == nodes_by_level.end())
            nodes_by_level.insert({vertices[i].heigth, 1});
        else
            it  -> second ++;
    }

    float x_increment , y_increment = static_cast<float>(win_size.y / nodes_by_level.size());

    sf::Vector2f root_possition = {static_cast<float>(win_size.x / 2), 10};

    global_sprite_index = parents_with_index[0].first; //sacamos el index para el sprite y le ponemos su nueva posicion
    get_lines_to_modify();
    modify_sprite_position(root_possition);
    sprite_selected = false;
    modified_lines_index.clear();

    std::vector<node> aux_vertices = vertices;

    std::sort(aux_vertices.begin(), aux_vertices.end(), [](const node &i , const node &j){
        return i.heigth < j.heigth;
    });


    int previous_parent = parents_with_index[0].second, increment = 1;
    bool parent_changed = false;
    int x_counter = 1, y_counter = 1;
    for (int i = 1; i < vertices.size(); ++i){
        if (aux_vertices[i].padre != previous_parent){
            parent_changed = true;
            x_counter = 1;
            previous_parent = aux_vertices[i].padre;            
            ++y_counter;
        }
        sf::Vector2f new_position;
        if (nodes_by_level[aux_vertices[i].heigth] == 1)
            new_position = {vertices[aux_vertices[i].padre].x, static_cast<float>(50* y_counter)};
        
        else{
            x_increment = static_cast<float>(win_size.x / (nodes_by_level[aux_vertices[i].heigth] + 1) );
            new_position = {x_increment * x_counter, static_cast<float>(50* y_counter)};
        }
        global_sprite_index = aux_vertices[i].id;
        get_lines_to_modify();
        modify_sprite_position(new_position);
        sprite_selected = false;
        modified_lines_index.clear();

        if (parent_changed)
            parent_changed = false;
        
        ++x_counter;
    }

    if (!textos_peso.empty())
        update_text_position();

    make_sprite_red(sprites[parents_with_index[0].first]);
}