#include "Concentrese.h"
#include <iostream>
#include <fstream>
#include <ctime>

Concentrese::Concentrese(string nombre) : Juego(nombre), pares(0) {
    cargarSimbolos("simbolos.txt");
    mezclarSimbolos();
    descubiertas = vector<bool>(simbolos.size(), false);
}

void Concentrese::cargarSimbolos(string archivo) {
    ifstream file(archivo);
    char simbolo;
    
    while (file >> simbolo) {
        simbolos.push_back(simbolo);
        simbolos.push_back(simbolo); // Duplicamos para tener parejas
    }
    file.close();
}

void Concentrese::mezclarSimbolos() {
    // Implementación simple sin algorithm
    for (int i = 0; i < simbolos.size(); i++) {
        int j = rand() % simbolos.size();
        char temp = simbolos[i];
        simbolos[i] = simbolos[j];
        simbolos[j] = temp;
    }
}

void Concentrese::mostrarTablero() {
    cout << "\nTablero:\n";
    for (int i = 0; i < simbolos.size(); i++) {
        if (descubiertas[i]) {
            cout << simbolos[i] << " ";
        } else {
            cout << (i+1) << " "; // Mostrar posición
        }
        
        if ((i+1) % 4 == 0) cout << endl; // 4 columnas
    }
}

void Concentrese::mostrarInstrucciones() {
    cout << "\n=== INSTRUCCIONES CONCENTRESE ===" << endl;
    cout << "Encuentra todas las parejas de simbolos" << endl;
    cout << "El tablero tiene " << simbolos.size() << " casillas" << endl;
}

void Concentrese::jugar() {
    mostrarInstrucciones();
    srand(time(0));
    
    while (pares < simbolos.size()/2) {
        mostrarTablero();
        
        int pos1, pos2;
        cout << "\nSelecciona primera posicion: ";
        cin >> pos1;
        pos1--; // Ajustar a índice 0
        
        cout << "Selecciona segunda posicion: ";
        cin >> pos2;
        pos2--; // Ajustar a índice 0
        
        // Mostrar selección temporalmente
        cout << "Seleccion: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;
        
        if (simbolos[pos1] == simbolos[pos2] && pos1 != pos2) {
            cout << "¡Encontraste una pareja!" << endl;
            descubiertas[pos1] = true;
            descubiertas[pos2] = true;
            pares++;
        } else {
            cout << "No son pareja. Sigue intentando." << endl;
        }
    }
    
    setPuntuacion(pares * 10);
    cout << "\n¡FELICIDADES! Completaste el juego con " << getPuntuacion() << " puntos." << endl;
    guardarResultado("Gano");
}