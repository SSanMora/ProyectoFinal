// este es el include guard
#ifndef JUEGO_H
#define JUEGO_H

#include <string>

class Juego {
    public:
        virtual void jugar() = 0;
        /* esto hace que todas las clases hijas definan una versión propia del método */
        virtual void guardarHistorial(const std::string& jugador, bool gano, int puntuacion) = 0;
        /* esto es para que cada juego guarde el historial de forma personalizada */
        virtual ~Juego() {} 
        /* esto es el destructor virtual, asegura que las clases hijas se destruyan correctamente */
};

/* este "juego.h" es una clase abstracta, 
tiene métodos virtuales puros "=0". de aquí,
los juegos "ahorcado" y "concentrece" van a heredar
la clase y definir versionas propias (^ω^)*/

#endif 