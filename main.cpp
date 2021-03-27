#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>

#include "includes/node.hpp"
#include "includes/functions.hpp"
#include "includes/edge.hpp"

#include "algorithms/prim3.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/grafos_aleatorios.hpp"

#include "tests/tests.hpp"

int main(int argc, char *argv[]){
    srand(time(NULL)); //semilla pal random
// cosas para el unit test
    if (argc == 2){
        std::string arg = argv[1];
        if (arg == "test"){
            test();
            return 0; //corre los test y finaliza el programa
        }   
    }
    else{ //si me pasas muchos argumentos o uno que no es, continua con el programa
        std::cout << "muchos argumentos, solo quiero uno >:(" << std::endl;
    }

    // SFML declarations
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Visualizador de grafos");
    sf::Texture texture;

    //cosas del grafo
    std::vector<node> vertices;
    std::vector<edge> edges;

    //cosas para dibujarlo
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Vertex> lineas;
    std::vector<sf::Vector2f> mouse_points;
    std::vector<std::vector<sf::Vector2f>> connected_lines;
    std::vector<std::vector<int>> connected_nodes_index;
    std::vector<int> node_index;
    std::vector<int> modified_lines_index;

    std::vector<sf::Vertex> lineas_coloreadas;

    //banderas para la interactividad
    bool sprite_selected = false;
    bool mouse_button_pressed = false;
    std::string mouse_button = "";
    // std::vector<int> mo1;

    //index para mover el sprite interactivamente
    int global_sprite_index;

    //cargar las texturas
    if (!texture.loadFromFile("Assets/blue-circle.png")){
        std::cout << "Error con textura" << std::endl;
        return 0;
    }

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)){
                if (lineas_coloreadas.size() > 0)
                    lineas_coloreadas.clear();
            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
                //aqui va el prim
                lineas_coloreadas.clear();
                std::cout<< "El prim" << std::endl;
                
                std::vector<edge> prim_mst = call_mst(edges, vertices, "Prim");
                create_lineas_coloreadas(lineas_coloreadas, prim_mst, sprites);
                for (auto &l : lineas_coloreadas)
                    l.color = sf::Color::Green;
                
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
                //aqui va el otro
                lineas_coloreadas.clear();
                std::cout << "El Kruskal" << std::endl;

                std::vector<edge> kusrkal_mst = call_mst(edges, vertices, "Kruskal");
                
                create_lineas_coloreadas(lineas_coloreadas, kusrkal_mst, sprites);
                for (auto &l : lineas_coloreadas)
                    l.color = sf::Color::Red;

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
                window.clear();
                edges.clear();
                vertices.clear();
                sprites.clear();
                lineas.clear();
                call_erdos_rentyi(edges, vertices);
                display_random_graph(edges, vertices, sprites, lineas, window,texture);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
                window.clear();
                edges.clear();
                vertices.clear();
                sprites.clear();
                lineas.clear();
                call_erdos_rentyi(edges, vertices,true);
                display_random_graph(edges, vertices, sprites, lineas, window,texture);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
                window.clear();
                edges.clear();
                vertices.clear();
                sprites.clear();
                lineas.clear();
                call_random_tree(edges, vertices);
                display_random_graph(edges, vertices, sprites, lineas, window, texture);
            }
            //interactividad
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
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
                            vertices[node_index[0]].arista_index.push_back(edges.size());
                            vertices[node_index[1]].arista_index.push_back(edges.size());
                            edge arista;
                            arista.nodes = node_index;
                            arista.peso = 0;
                            edges.push_back(arista);
                            lineas.push_back(sf::Vertex(mouse_points[0]));
                            lineas.push_back(sf::Vertex(mouse_points[1]));
                            
                            std::cout << "Una linea" << std::endl;
                            sprite_selected = false;
                            mouse_points.clear();
                            node_index.clear();
                            // window.draw(line, 2, sf::Lines);
                        }
                        else if (!sprite_selected){
                            mouse_points.push_back(mouse);
                            std::cout << "aqui no hay linea" << std::endl;
                            connected_lines.push_back(mouse_points);
                            node_index.push_back(index);
                            sprite_selected = true;
                        }
                    }
                    else {
                        sf::Sprite sprite = create_sprite(texture, mouse);
                        sprites.push_back(sprite);
                        node vertice;
                        vertice.id = vertices.size();
                        vertice.x = mouse.x;
                        vertice.y = mouse.y;
                        vertice.root_id = -1;
                        vertices.push_back(vertice);
                    }
                }

                else{
                    sf::Sprite sprite = create_sprite(texture, mouse);
                    sprites.push_back(sprite);
                    node vertice;
                    vertice.id = vertices.size();
                    vertice.x = mouse.x;
                    vertice.y = mouse.y;
                    vertice.root_id = -1;
                    vertices.push_back(vertice);
                }
            }

            ///mover nodo y las lineas de lugar
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle){
                
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mouse_button_pressed = true;

                if (sprites.size() > 0){
                    global_sprite_index = get_sprite_index(mouse, sprites);
                    if (global_sprite_index != -1){
                        std::cout << "el sprite que buscas es el " << global_sprite_index << std::endl;

                        mouse_button = "Middle";
                        if (lineas.size() > 0){
                            for (int i = 0; i < lineas.size(); ++i){
                                if (sprites[global_sprite_index].getGlobalBounds().contains(lineas[i].position))
                                    modified_lines_index.push_back(i);
                            }
                        }

                        sprites[global_sprite_index].setPosition(mouse);
                        vertices[global_sprite_index].x = mouse.x;
                        vertices[global_sprite_index].y = mouse.y;

                        if(modified_lines_index.size() > 0){
                            for (int i = 0; i < modified_lines_index.size(); ++i)
                                lineas[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
                        }
                        sprite_selected = true;
                    }
                    else{
                        std::cout << "aqui no hay nada mi chavo" << std::endl; 
                        mouse_button_pressed = false;
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
                    sprites[global_sprite_index].setPosition(new_position);
                    vertices[global_sprite_index].x = new_position.x;
                    vertices[global_sprite_index].y = new_position.y;
                    if(modified_lines_index.size() > 0){
                        for (int i = 0; i < modified_lines_index.size(); ++i)
                            lineas[modified_lines_index[i]].position = sprites[global_sprite_index].getPosition();
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased && mouse_button == "Middle"){
                mouse_button = "";
                sprite_selected = false;
                global_sprite_index = -1;
                if(modified_lines_index.size() > 0)
                    modified_lines_index.clear();
            }

        window.clear();
        if (lineas.size() > 0)
            window.draw(&lineas[0],lineas.size(), sf::Lines);

        if(lineas_coloreadas.size() > 0)
            window.draw(&lineas_coloreadas[0], lineas_coloreadas.size(), sf::Lines);
        
        for (auto &s: sprites)
            window.draw(s);

        window.display();
        }
    }
    return 0;
}