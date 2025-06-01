#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"
#include <string>
#include <vector>

using namespace std;

class Concentrese : public Juego { // con esto hereda de la clase juego
private:
    vector<vector<char>> tablero; 
    /* este es el tablero del juego, es una matriz de caracteres */
    vector<vector<bool>> descubiertas; 
    /* este es un vector que va a indicar si una casilla ha sido descubierta */
    int filas;
    /* este es para el número de filas del tablero */
    int columnas;
    /* y pues este para es el número de columnas del tablero */

public:
    Concentrese();
    /* este es el constructor por defecto, que inicializa los atributos */

    void jugar() override;
    /* este es el método que se va a ejecutar al jugar,
    y como ya sabemos, sobrescribe el método jugar de la clase juego */
    void guardarHistorial(const string& jugador, bool gano, int puntuacion) override;
    /* este es el método que se va a ejecutar al guardar el historial,
    y también sobrescribe el método guardarHistorial de la clase juego */

    void cargarSimbolosDesdeArchivo(const string& rutaArchivo);
    /* este es el método que se va a ejecutar al cargar los símbolos desde un archivo,
    y sirve para leer los símbolos desde un archivo y cargarlos en el juego */
    void mostrarTablero();
    /* este es el método que se va a ejecutar al mostrar el tablero,
    y muestra el estado actual del tablero, con las casillas descubiertas y ocultas */
};

#endif
