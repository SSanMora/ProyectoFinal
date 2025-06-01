/* esta es la declaración del juego ahorcado !! */

// include guard
#ifndef AHORCADO_H
#define AHORCADO_H

#include "Juego.h"
#include <string>
#include <vector> // para manejar listas de palabras (cuando se lean del archivo)

using namespace std;

class Ahorcado :
    public Juego { // hereda de la clase juego
        private:
            // atributos privados de la clase ahorcado
            string palabraSecreta; // esta es la palabra que el jugador tiene que adivinar
            string palabraAdivinada; // este es el proceso de adivinación de la palabra
            int intentosMaximos; // este es el número máximo de intentos antes de perder (6)
            int intentosUsados; // y este es el número de intentos que el jugador ha usado
        
        public:
            Ahorcado(); // este es el constructor por defecto, inicializa los atributos

            void jugar() override; 
            /* esto sobrescribe el método jugar de la clase juego y 
            es el método que se va a ejecutar al jugar */
            void guardarHistorial(const string& jugador, bool gano, int puntuacion) override;
            // este es el método que se va a ejecutar al guardar el historial

            void cargarPalabraDesdeArchivo(const string& rutaArchivo);
            /* este es el método que se va a ejecutar al cargar la palabra desde un archivo
            este método sirve para leer palabras desde el archivo y elegir una al azar */
            void inicializarPalabra(const string& palabra);
            /* este es el método que se va a ejecutar al inicializar la palabra,
            y prepara la palabra secreta, creando una cadena como ____ del mismo largo */
    };

#endif
