#include "Juego.h"
#include <fstream>
#include <ctime>
#include <iostream>
using namespace std;

Juego::Juego(string nombre) : nombreJugador(nombre), puntuacion(0) {}

void Juego::mostrarInstrucciones() {
    cout << "\nInstrucciones generales del juego:\n";
}

void Juego::guardarResultado(string resultadoJuego) {
    ofstream archivo("resultados.txt", ios::app);
    if (archivo.is_open()) {
        time_t ahora = time(0);
        char fecha[80];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&ahora));
        
        archivo << fecha << " " << nombreJugador << " " 
               << resultadoJuego << " " << puntuacion << endl;
        archivo.close();
    }
}

string Juego::getNombreJugador() {
    return nombreJugador;
}

int Juego::getPuntuacion() {
    return puntuacion;
}

void Juego::setPuntuacion(int puntos) {
    puntuacion = puntos;
}