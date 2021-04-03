#pragma once

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "edge.hpp"
#include "globals.hpp"
#include "event_handler.hpp"


void visualizer(){
    // SFML declarations
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Visualizador de grafos");

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                    window.close();
            else
                interactivity(event, window);
            
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
}