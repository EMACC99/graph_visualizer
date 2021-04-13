#pragma once

#include "node.hpp"
#include "edge.hpp"
#include "functions.hpp"
#include "globals.hpp"

class event_handler{
private:
    void clear_vectors();
    void select_algorithms(const sf::Event &event, sf::RenderWindow &window);
public:
    void interactivity(const sf::Event &event, sf::RenderWindow &window);
    event_handler();
    ~event_handler();
    
};

event_handler::event_handler(){
    // interactivity(event, window);
}

event_handler::~event_handler(){
}
/**
 * @brief clears the global vectors
 * 
 */
void event_handler::clear_vectors(){
    aristas.clear();
    vertices.clear();
    sprites.clear();
    lineas.clear();
    textos_peso.clear();
    lineas_coloreadas.clear();
}
/**
 * @brief 
 * 
 * @param event 
 * @param window 
 */
void event_handler::select_algorithms(const sf::Event &event, sf::RenderWindow &window){
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
        lineas_coloreadas.clear();

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
        //aqui va el prim
        lineas_coloreadas.clear();
        std::cout<< "El prim" << std::endl;
        std::vector<edge> prim_mst = call_mst("Prim");
        create_lineas_coloreadas(prim_mst, sf::Color::Green);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
        //aqui va el otro
        lineas_coloreadas.clear();
        std::cout << "El Kruskal" << std::endl;
        std::vector<edge> kusrkal_mst = call_mst("Kruskal");    
        create_lineas_coloreadas(kusrkal_mst, sf::Color::Red);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
        window.clear();
        clear_vectors();
        call_erdos_rentyi();
        display_random_graph(window);
        update_text_position();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
        window.clear();
        clear_vectors();
        call_erdos_rentyi(true);
        display_random_graph(window);
        update_text_position();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
        window.clear();
        clear_vectors();
        call_random_tree();
        display_random_graph(window);
        update_text_position();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
        window.clear();
        clear_vectors();
        call_random_conex_graph();
        display_random_graph(window);
        update_text_position();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
        lineas_coloreadas.clear();
        std::pair<std::vector<int>, unsigned int> colores = componentes_conexas();
        color_conex_components(colores);
        std::cout << "El numero de componentes conexas es: " << colores.second << "!!" << std::endl;

        if (colores.second == 1){
            std::vector<int> parents = call_get_parents();
            if (!parents.empty()){
            std::vector<std::pair<int, int>> parents_with_index;
            for (int i = 0; i < parents.size(); ++i)
                parents_with_index.push_back({i, parents[i]});

            for (auto &elem : parents_with_index)
                std::cout << "nodo: " << elem.first << " Padre: " << elem.second << std::endl;
            }
            else
                std::cout << "Hay un ciclo, no es arbol" << std::endl;
        }
        
        // display_tree_by_parents(parents_with_index, window);
    }
}
/**
 * @brief 
 * 
 * @param event 
 * @param window 
 */
void event_handler::interactivity (const sf::Event &event, sf::RenderWindow &window){
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (sprites.size() > 0){
            if (is_sprite(mouse, sprites)){
                int index = get_sprite_index(mouse, sprites);
                std::cout << "Mira!, el sprite " << index << "!!!" << std::endl;

                if(sprite_selected){
                    mouse_points.push_back(mouse);
                    connected_lines.push_back(mouse_points);
                    node_index.push_back(index);
                    connected_nodes_index.push_back(node_index);
                    vertices[node_index[0]].arista_index.push_back(aristas.size());
                    vertices[node_index[1]].arista_index.push_back(aristas.size());

                    edge arista;
                    arista.nodes = node_index;
                    arista.peso = 0;
                    aristas.push_back(arista);
                    lineas.push_back(sf::Vertex(mouse_points[0]));
                    lineas.push_back(sf::Vertex(mouse_points[1]));

                    std::cout << "Una linea" << std::endl;
                    sprite_selected = false;
                    mouse_points.clear();
                    node_index.clear();
                }
                else if (!sprite_selected){
                    mouse_points.push_back(mouse);
                    std::cout << "aqui no hay linea" << std::endl;
                    connected_lines.push_back(mouse_points);
                    node_index.push_back(index);
                    sprite_selected = true;
                }
            }
            else
                create_node(mouse);
        }
        else
            create_node(mouse);
    }
    ///mover nodo y las lineas de lugar
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle){
                
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (sprites.size() > 0){
            global_sprite_index = get_sprite_index(mouse, sprites);
            if (global_sprite_index != -1){
                std::cout << "el sprite que buscas es el " << global_sprite_index << std::endl;

                mouse_button = "Middle";
                get_lines_to_modify();

                modify_sprite_position(mouse);

                if (textos_peso.size() > 0)
                    update_text_position();
            }
            else{
                std::cout << "aqui no hay nada mi chavo" << std::endl; 
                
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved && mouse_button == "Middle"){
        if (sprite_selected){
            if (lineas.size() > 0){
                for (int i = 0; i < lineas.size(); ++i){
                    if (sprites[global_sprite_index].getGlobalBounds().contains(lineas[i].position))
                        modified_lines_index.push_back(i);
                }
            }
            sf ::Vector2f new_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            modify_sprite_position(new_position);

            if (textos_peso.size() > 0)
                update_text_position();
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && mouse_button == "Middle"){
        mouse_button = "";
        sprite_selected = false;
        global_sprite_index = -1;
        if(modified_lines_index.size() > 0)
            modified_lines_index.clear();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        event_handler::clear_vectors(); //borrar todo lo que esta en pantalla
    
    else
        event_handler::select_algorithms(event, window);
}