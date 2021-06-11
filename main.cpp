#include <cstdlib>
#include "argh/argh.h"

#include "includes/globals.hpp"
#include "includes/visualizer.hpp"

#include "tests/tests.hpp"

int main(int argc, char *argv[]){
    srand(time(NULL)); //semilla pal random

    argh::parser cmdl(argv);
    if (cmdl.size() > 1){
        if (cmdl[{"-t", "--test"}]){
            test();
            is_test = true;    
        }
        else { //si me pasas muchos argumentos o uno que no es, continua con el programa
            std::cout << "Argumentos no aceptados" << std::endl;
        }
    }

    //cargar las texturas
    if (!blue_circle.loadFromFile("Assets/blue-circle.png") || !red_circle.loadFromFile("Assets/red-circle.png")){
        std::cout << "Error con textura" << std::endl;
        return 0; // si falla al cargar las texturas, termina la ejecucion
    }

    if (!font.loadFromFile("Assets/Caskaydia Cove Nerd Font Complete.ttf")){
        std::cout << "Error al cargar la fuente" << std::endl;
        return 0;
    }
    //llamamos al visualizador
    visualizer();

    return 0;
}