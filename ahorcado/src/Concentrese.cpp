/*
#include "Concentrese.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

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

*/

#include "Concentrese.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Concentrese::Concentrese() {
    filas = 4;
    columnas = 4;

    tablero.resize(filas, vector<char>(columnas, '*'));
    descubiertas.resize(filas, vector<bool>(columnas, false));
}

void Concentrese::cargarSimbolosDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    vector<char> simbolos;

    if (archivo.is_open()) {
        char simbolo;
        while (archivo >> simbolo) {
            simbolos.push_back(simbolo);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de símbolos.\n";
        return;
    }

    if (simbolos.size() < (filas * columnas) / 2) {
        cout << "No hay suficientes símbolos en el archivo.\n";
        return;
    }

    vector<char> pares;
    for (int i = 0; i < (filas * columnas) / 2; i++) {
        pares.push_back(simbolos[i]);
        pares.push_back(simbolos[i]);
    }

    srand(time(0));
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int indice = rand() % pares.size();
            tablero[i][j] = pares[indice];
            pares.erase(pares.begin() + indice);
        }
    }
}

void Concentrese::mostrarTablero() {
    cout << "\n   ";
    for (int j = 0; j < columnas; j++) cout << j << " ";
    cout << "\n";

    for (int i = 0; i < filas; i++) {
        cout << i << "  ";
        for (int j = 0; j < columnas; j++) {
            if (descubiertas[i][j]) {
                cout << tablero[i][j] << " ";
            } else {
                cout << "* ";
            }
        }
        cout << "\n";
    }
}

void Concentrese::jugar() {
    string jugador;
    cout << "Ingresa tu nombre: ";
    cin.ignore();
    getline(cin, jugador);

    cargarSimbolosDesdeArchivo("simbolos.txt");

    int parejasEncontradas = 0;
    int intentos = 0;

    while (parejasEncontradas < (filas * columnas) / 2) {
        mostrarTablero();

        int f1, c1, f2, c2;

        // Primer casilla
        cout << "\nSelecciona la primera casilla (primero la fila, luego la columna): \n";
        cin >> f1 >> c1;

        if (f1 < 0 || f1 >= filas || c1 < 0 || c1 >= columnas || descubiertas[f1][c1]) {
            cout << "Selección inválida. Intenta de nuevo.\n";
            continue;
        }

        descubiertas[f1][c1] = true;
        mostrarTablero();

        // Segunda casilla
        cout << "\nSelecciona la segunda casilla (primero la fila, luego la columna): \n";
        cin >> f2 >> c2;

        if (f2 < 0 || f2 >= filas || c2 < 0 || c2 >= columnas ||
            (f1 == f2 && c1 == c2) || descubiertas[f2][c2]) {
            cout << "Selección inválida. Intenta de nuevo.\n";
            descubiertas[f1][c1] = false; // ocultar de nuevo si la segunda es inválida
            continue;
        }

        descubiertas[f2][c2] = true;
        mostrarTablero();

        cout << "Observa las fichas... presiona Enter para continuar.\n";
        cin.ignore();
        cin.get();

        if (tablero[f1][c1] == tablero[f2][c2]) {
            cout << "¡Pareja encontrada!\n";
            parejasEncontradas++;
        } else {
            cout << "No son iguales. Intenta otra vez.\n";
            descubiertas[f1][c1] = false;
            descubiertas[f2][c2] = false;
        }

        intentos++;
    }

    cout << "\n¡Felicidades! Has completado el juego en " << intentos << " intentos.\n";
    guardarHistorial(jugador, true, intentos);
}

void Concentrese::guardarHistorial(const string& jugador, bool gano, int puntuacion) {
    ofstream archivo("historial.txt", ios::app);
    if (archivo.is_open()) {
        time_t now = time(0);
        tm* localtm = localtime(&now);

        archivo << (1900 + localtm->tm_year) << "-"
                << (1 + localtm->tm_mon) << "-"
                << localtm->tm_mday << " "
                << jugador << " MEM "
                << (gano ? "G" : "P") << " "
                << puntuacion << "\n";

        archivo.close();
    }
}
