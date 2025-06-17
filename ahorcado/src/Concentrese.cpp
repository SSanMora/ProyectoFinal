#include "Concentrese.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Concentrese::Concentrese() { // este es el constructor por defecto
    filas = 4; // este es el número de filas del tablero
    columnas = 4; // y este es el número de columnas del tablero 

    tablero.resize(filas, vector<char>(columnas, '*'));
    /* inicializa el tablero con '*', que representa casillas ocultas */
    descubiertas.resize(filas, vector<bool>(columnas, false));
    /* inicializa el vector de descubiertas con false, 
    que indica que ninguna casilla ha sido descubierta */
}

void Concentrese::cargarSimbolosDesdeArchivo(const string& rutaArchivo) { 
    /* este método carga los símbolos desde un archivo y los prepara para el juego */
    ifstream archivo(rutaArchivo);
    /* esto abre el archivo de símbolos */
    vector<char> simbolos;
    /* y este es un vector que va a almacenar los símbolos leídos del archivo */

    if (archivo.is_open()) { /* esto verifica si el archivo se abrió correctamente */
        char simbolo; /* este es un carácter temporal para leer los símbolos */
        while (archivo >> simbolo) { /* esto lee los símbolos del archivo uno por uno */
            simbolos.push_back(simbolo); /* y los agrega al vector de símbolos */
        }
        archivo.close(); /* esto cierra el archivo después de leer todos los símbolos */
    } else {
        cout << "No se pudo abrir el archivo de símbolos.\n"; 
        /* si no se pudo abrir el archivo, muestra un mensaje de error */
        return;
    }

    if (simbolos.size() < (filas * columnas) / 2) { /* verifica si hay suficientes símbolos */
        cout << "No hay suficientes símbolos en el archivo.\n"; 
        /* si no hay suficientes símbolos, muestra un mensaje de error */
        return;
    }

    vector<char> pares; /* este es un vector que va a almacenar los pares de símbolos */
    for (int i = 0; i < (filas * columnas) / 2; i++) { 
        /* yy esto crea los pares de símbolos, duplicando cada símbolo */
        pares.push_back(simbolos[i]); /* agrega el símbolo original */
        pares.push_back(simbolos[i]); /* y agrega el símbolo duplicado */
    }

    srand(time(0)); /* esto inicializa el generador de números aleatorios con la hora actual */
    for (int i = 0; i < filas; i++) { /* este for recorre las filas del tablero */
        for (int j = 0; j < columnas; j++) { /* y este for recorre las columnas del tablero */
            int indice = rand() % pares.size(); 
            /* esto genera un índice aleatorio para seleccionar un símbolo */
            tablero[i][j] = pares[indice]; /* asigna el símbolo al tablero en la posición (i, j) */
            pares.erase(pares.begin() + indice); 
            /* y aqui elimina el símbolo seleccionado del vector de pares */
        }
    }
}

void Concentrese::mostrarTablero() { /* este método muestra el estado actual del tablero */
    cout << "\n   ";
    for (int j = 0; j < columnas; j++) cout << j << " "; /* muestra los índices de las columnas */
    cout << "\n";

    for (int i = 0; i < filas; i++) { /* este for recorre las filas del tablero */
        cout << i << "  "; /* muestra el índice de la fila */
        for (int j = 0; j < columnas; j++) { /* y este for recorre las columnas del tablero */
            if (descubiertas[i][j]) { /* si la casilla ha sido descubierta... */
                cout << tablero[i][j] << " "; /* entonces muestra el símbolo correspondiente */
            } else {
                cout << "* "; 
                /* si no, muestra un asterisco '*' para indicar que la casilla está oculta */
            }
        }
        cout << "\n";
    }
}

void Concentrese::jugar() { /* este es el método que se va a ejecutar al jugar */
    string jugador; /* este es el nombre del jugador */
    cout << "\nIngresa tu nombre: "; /* pide al jugador que ingrese su nombre */
    cin.ignore(); /* limpia el buffer de entrada */
    getline(cin, jugador); /* lee el nombre del jugador */

    cargarSimbolosDesdeArchivo("simbolos.txt"); 
    /* esto carga los símbolos desde el archivo "simbolos.txt" */

    int parejasEncontradas = 0; /* este es el contador de parejas encontradas */
    int intentos = 0; /* este es el contador de intentos realizados */

    while (parejasEncontradas < (filas * columnas) / 2) { 
        /* este while se ejecuta hasta que se encuentren todas las parejas */
        mostrarTablero(); /* muestra el estado actual del tablero */

        int f1, c1, f2, c2; 
        /* estos son los índices de las casillas seleccionadas por el jugador */

        // para la primer casilla
        cout << "\nSelecciona la primera casilla (primero la fila, luego la columna): \n";
        cin >> f1 >> c1; /* pide al jugador que ingrese la fila y columna de la primera casilla */

        if (f1 < 0 || f1 >= filas || c1 < 0 || c1 >= columnas || descubiertas[f1][c1]) { 
            /* verifica si la selección es válida */
            cout << "Selección inválida. Intenta de nuevo.\n";
            /* si la selección es inválida, muestra un mensaje de error */
            continue;
        }

        descubiertas[f1][c1] = true; /* marca la casilla como descubierta */
        mostrarTablero(); /* muestra el estado del tablero después de descubrir la primera casilla */

        // para la segunda casilla
        cout << "\nSelecciona la segunda casilla (primero la fila, luego la columna): \n";
        cin >> f2 >> c2; /* pide al jugador que ingrese la fila y columna de la segunda casilla */

        if (f2 < 0 || f2 >= filas || c2 < 0 || c2 >= columnas || /* verifica si la selección es válida */
            (f1 == f2 && c1 == c2) || descubiertas[f2][c2]) { /* verifica si es la misma casilla o ya descubierta */
            cout << "Selección inválida. Intenta de nuevo.\n"; 
            descubiertas[f1][c1] = false; // esto lo oculta de nuevo si la segunda es inválida
            continue;
        }

        descubiertas[f2][c2] = true; /* marca la segunda casilla como descubierta */
        mostrarTablero(); /* muestra el estado del tablero después de descubrir la segunda casilla */

        cout << "Observa las fichas... presiona Enter para continuar.\n";
        cin.ignore(); /* limpia el buffer de entrada */
        cin.get(); /* espera a que el jugador presione enter */

        if (tablero[f1][c1] == tablero[f2][c2]) { 
            /* verifica si los símbolos de las dos casillas son iguales */
            cout << "¡Pareja encontrada!\n";
            parejasEncontradas++; /* incrementa el contador de parejas encontradas */
        } else {
            cout << "No son iguales. Intenta otra vez.\n";
            descubiertas[f1][c1] = false; /* oculta la primera casilla si no son iguales */
            descubiertas[f2][c2] = false; /* y oculta la segunda casilla si no son iguales */
        }

        intentos++; /* incrementa el contador de intentos realizados */
    }

    cout << "\n¡Felicidades! Has completado el juego en " << intentos << " intentos.\n";
    guardarHistorial(jugador, true, intentos);
    /* guarda el historial del juego, indicando que el jugador ganó */
}

void Concentrese::guardarHistorial(const string& jugador, bool gano, int puntuacion) {
    /* este método guarda el historial del juego en un archivo */
    ofstream archivo("historial.txt", ios::app); 
    /* esto abre el archivo "historial.txt" en modo append */
    if (archivo.is_open()) {
        /* verifica si el archivo se abrió correctamente */
        time_t now = time(0);
        /* obtiene la hora actual */
        tm* localtm = localtime(&now);
        /* y convierte la hora actual a la hora local */

        archivo << (1900 + localtm->tm_year) << "-"
                << (1 + localtm->tm_mon) << "-"
                << localtm->tm_mday << " "
                << jugador << " MEM "
                << (gano ? "G" : "P") << " "
                << puntuacion << "\n";
        /* y por ultimo, escribe la fecha, el nombre del jugador, el tipo de juego (MEM) */

        archivo.close(); /* cierra el archivo después de escribir */
    }
}
