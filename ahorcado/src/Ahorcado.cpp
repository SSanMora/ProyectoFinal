// include guard
#include "Ahorcado.h" // el archivo de cabecera del juego ahorcado
#include <iostream> // para manejar la entrada y salida estándar
#include <fstream> // para manejar archivos
#include <ctime> // para manejar el tiempo (para el historial)
#include <cctype> // para manejar caracteres (como tolower)

using namespace std;

Ahorcado::Ahorcado() {
    /* este es el constructor por defecto
    inicializa los atributos de la clase ahorcado */
    intentosMaximos = 6;
    intentosUsados = 0;
}

void Ahorcado::inicializarPalabra(const string& palabra) {
    palabraSecreta = palabra;
    palabraAdivinada = string(palabra.length(), '_');
}

void Ahorcado::cargarPalabraDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    vector<string> palabras;

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            palabras.push_back(linea);
        }
        archivo.close();

        if (palabras.empty()) {
            cout << "El archivo está vacío. Agrega palabras a palabras.txt.\n";
            palabraSecreta = "";
            return;
        }

        srand(time(0));
        int indice = rand() % palabras.size();
        inicializarPalabra(palabras[indice]);
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}

void Ahorcado::jugar() {
    string jugador;
    cout << "Ingresa tu nombre: ";
    getline(std::cin, jugador);

    cargarPalabraDesdeArchivo("palabras.txt");

    if (palabraSecreta.empty()) {
        cout << "No se pudo cargar ninguna palabra. Terminando el juego.\n";
        return;
    }

    cout << "La palabra tiene " << palabraSecreta.length() << " letras.\n";

    char letra;
    bool gano = false;

    while (intentosUsados < intentosMaximos && palabraAdivinada != palabraSecreta) {
        cout << "\nPalabra: " << palabraAdivinada << "\n";
        cout << "Intentos restantes: " << (intentosMaximos - intentosUsados) << "\n";
        cout << "Ingresa una letra: ";
        cin >> letra;
        letra = tolower(letra);

        bool acierto = false;
        for (size_t i = 0; i < palabraSecreta.length(); i++) {
            if (tolower(palabraSecreta[i]) == letra && palabraAdivinada[i] == '_') {
                palabraAdivinada[i] = palabraSecreta[i]; // se conserva la letra original
                acierto = true;
            }
        }

        if (!acierto) {
            intentosUsados++;
        }
    }

    if (palabraAdivinada == palabraSecreta) {
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << "\n";
        gano = true;
    } else {
        cout << "\nPerdiste. La palabra era: " << palabraSecreta << "\n";
    }

    guardarHistorial(jugador, gano, intentosMaximos - intentosUsados);
}

void Ahorcado::guardarHistorial(const string& jugador, bool gano, int puntuacion) {
    ofstream archivo("historial.txt", ios::app);
    if (archivo.is_open()) {
        time_t now = time(0);
        tm* localtm = localtime(&now);

        archivo << (1900 + localtm->tm_year) << "-"
                << (1 + localtm->tm_mon) << "-"
                << localtm->tm_mday << " "
                << jugador << " AH "
                << (gano ? "G" : "P") << " "
                << puntuacion << "\n";

        archivo.close();
    }
}

/* esta es la implementacion del juego ahorcado */
