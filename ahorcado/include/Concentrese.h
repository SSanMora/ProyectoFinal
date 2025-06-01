/*
#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"
#include <vector>

using namespace std;

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
*/

#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"
#include <string>
#include <vector>

using namespace std;

class Concentrese : public Juego {
private:
    vector<vector<char>> tablero;
    vector<vector<bool>> descubiertas;
    int filas;
    int columnas;

public:
    Concentrese();

    void jugar() override;
    void guardarHistorial(const string& jugador, bool gano, int puntuacion) override;

    void cargarSimbolosDesdeArchivo(const string& rutaArchivo);
    void mostrarTablero();
};

#endif
