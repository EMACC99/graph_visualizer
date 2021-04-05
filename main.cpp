#include <cstdlib>

#include "includes/globals.hpp"
#include "includes/visualizer.hpp"

#include "tests/tests.hpp"

int main(int argc, char *argv[]){
    srand(time(NULL)); //semilla pal random
// cosas para el unit test
    if (argc == 2){
        std::string arg = argv[1];
        if (arg == "test"){
            test();
            // return 0; //corre los test y finaliza el programa
            is_test = true;
        }   
    }
    else if (argc > 2){ //si me pasas muchos argumentos o uno que no es, continua con el programa
        std::cout << "muchos argumentos, solo quiero uno >:(" << std::endl;
    }

    //cargar las texturas
    if (!texture.loadFromFile("Assets/blue-circle.png")){
        std::cout << "Error con textura" << std::endl;
        return 0; // si falla al cargar las texturas, termina la ejecucion
    }

    if (!font.loadFromFile("Assets/Caskaydia Cove Nerd Font Complete.ttf")){
        std::cout << "Error al cargar la fuente" << std::endl;
        return 0;
    }
    //llamos al visualizador
    visualizer();

    return 0;
}