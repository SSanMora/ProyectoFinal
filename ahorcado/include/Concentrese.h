#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"
#include <vector>

class Concentrese : public Juego {
private:
    vector<char> simbolos;
    vector<bool> descubiertas;
    int pares;
    
    void mezclarSimbolos();
    void mostrarTablero();

public:
    Concentrese(string nombre);
    void jugar();
    void mostrarInstrucciones();
    void cargarSimbolos(string archivo);
};

#endif