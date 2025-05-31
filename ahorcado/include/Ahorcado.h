#ifndef AHORCADO_H
#define AHORCADO_H

#include "Juego.h"
#include <vector>

class Ahorcado : public Juego {
private:
    string palabralSecreta;
    string palabraAdivinada;
    int intentos;
    vector<string> palabras;
    
    void seleccionarPalabra();
    bool verificarLetra(char letra);

public:
    Ahorcado(string nombre);
    void jugar();
    void mostrarInstrucciones();
    void cargarPalabras(string archivo);
};

#endif