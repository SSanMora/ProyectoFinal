#include <iostream>
#include <memory>
#include "Ahorcado.h"
#include "Concentrese.h"
// #include "Concentrece.h"

using namespace std;

int main() {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\t::: MINIJUEGOS :::\n";
        cout << "1. Ahorcado\n";
        cout << "2. Concentrece\n";
        cout << "3. Salir\n";
        cout << "(^ω^) Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore();

        unique_ptr<Juego> juego;

        switch (opcion) {
            case 1:
                juego = make_unique<Ahorcado>();
                juego->jugar();
                break;
            case 2:
                juego = make_unique<Concentrese>();
                juego->jugar();
                break;
            case 3:
                salir = true;
                cout << "\nGracias por jugar! (*・ω・)ﾉ\n";
                break;
            default:
                cout << "\nOpcion no valida. Intenta de nuevo!\n";
                break;
        }
    }

    return 0;
}

/* este es el menu principal, y por ende, el selector de juegos.
ahora bien, el archivo "palabras.txt" es la lista de palabras para el ahorcado.
y el archivo "simbolos.txt" es la lista de símbolos para el juego concentrese.
y el archivo "historial.txt" se va a generar al jugar, y es el registro de partidas.*/