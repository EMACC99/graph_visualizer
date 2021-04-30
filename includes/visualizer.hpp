#pragma once

#include "functions.hpp"
#include "globals.hpp"
#include "event_handler_class.hpp"

class visualizer : event_handler{
private:
    void draw(sf::RenderWindow &window){
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                        window.close();

                else if (event.type == sf::Event::Resized)
                    window.setView(sf::View(sf::FloatRect(0,0,event.size.width, event.size.height)));
                
                else
                    interactivity(event, window);

                window.clear();
                if (is_test){
                    display_graph(window);
                    create_text_to_display();
                    update_text_position();
                    is_test = false;
                }
                if (lineas.size() > 0)
                    window.draw(&lineas[0],lineas.size(), sf::Lines);

                if(lineas_coloreadas.size() > 0)
                    window.draw(&lineas_coloreadas[0], lineas_coloreadas.size(), sf::Lines);

                for (auto &s: sprites)
                    window.draw(s);

                for(auto &t : textos_peso)
                    window.draw(t);

                window.display();
            }
        }
    }
public:
    visualizer(/* args */);
    ~visualizer();
};

visualizer::visualizer(/* args */){
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Visualizador de grafos");
    visualizer::draw(window);
}

visualizer::~visualizer(){
}