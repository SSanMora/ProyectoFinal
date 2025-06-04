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
    intentosMaximos = 6; /* el número máximo de intentos es 6 */
    intentosUsados = 0; /* y el número de intentos usados comienza en 0 */
}

void Ahorcado::inicializarPalabra(const string& palabra) { 
    /* este es el método que se va a ejecutar al inicializar la palabra */
    palabraSecreta = palabra; /* la palabra secreta es la que se pasa como parámetro */
    palabraAdivinada = string(palabra.length(), '_'); 
    /* crea una cadena de guiones bajos del mismo largo que la palabra secreta */
}

void Ahorcado::cargarPalabraDesdeArchivo(const string& rutaArchivo) {
    /* este es el método que se va a ejecutar al cargar la palabra desde un archivo */
    ifstream archivo(rutaArchivo);
    /* esto abre el archivo en modo lectura */
    vector<string> palabras;
    /* y este es un vector que va a almacenar las palabras leídas del archivo */

    if (archivo.is_open()) { /* si el archivo se abre correctamente */
        string linea; /* una variable para almacenar cada línea leída */
        while (getline(archivo, linea)) {  /* lee el archivo línea por línea */
            palabras.push_back(linea); /* agrega cada línea al vector de palabras */
        }
        archivo.close(); /* cierra el archivo después de leerlo */

        if (palabras.empty()) { /* si el vector de palabras está vacío */
            cout << "El archivo está vacío. Agrega palabras a palabras.txt.\n"; 
            palabraSecreta = ""; /* no hay palabra secreta */
            return; /* termina el método */
        }

        srand(time(0)); 
        /* inicializa la semilla del generador de números aleatorios con el tiempo actual */
        int indice = rand() % palabras.size(); 
        /* elige un índice aleatorio dentro del rango del vector de palabras */
        inicializarPalabra(palabras[indice]); 
        /* inicializa la palabra secreta con la palabra elegida al azar */
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}

void Ahorcado::escribirPalabraDesdeConsola(const string& palabra) {
    /* este es el método que se va a ejecutar al elegir una palabra desde la consola */
    if (palabra.empty()) { /* si la palabra está vacía */
        cout << "No se ingresó ninguna palabra.\n"; 
        return; /* termina el método */
    }
    inicializarPalabra(palabra); /* inicializa la palabra secreta con la palabra ingresada */

}

void Ahorcado::jugar() { /* este es el método que se va a ejecutar al jugar */
    string jugador; /* esta es la variable que va a almacenar el nombre del jugador */
    string jugador2; /* esta es la variable que va a almacenar el nombre del jugador 2 (si aplica) */
    
    /* el jugador debe elegir el modo de juego, jugador vs cpu (para cargar las
    palabras desde archivo) o jugador1 vs jugador2 (escribir palabra por pantalla)*/
    
    cout << "\nElige el modo de juego:" << endl;
    cout << "1. Jugador vs CPU." << endl;
    cout << "2. Jugador 1 vs Jugador 2." << endl;
    
    int modalidadDeJuego;
    cout << "Selecciona una opción (1/2): ";
    cin >> modalidadDeJuego; /* recibe la elección del jugador */
    cin.ignore(); /* para limpiar el buffer de entrada */
    
    if (modalidadDeJuego == 1) {
        /* si el jugador elige la primera opción... */
        cout << "\nIngresa tu nombre: "; 
        getline(cin, jugador); /* lee el nombre del jugador desde la entrada estándar */
        cargarPalabraDesdeArchivo("palabras.txt");
        /* carga las palabras desde el archivo palabras.txt */
        if (palabraSecreta.empty()) { /* si no se pudo cargar ninguna palabra */
            cout << "No se pudo cargar ninguna palabra. Terminando el juego.\n";
            return; /* termina el método */
        }
    } else if (modalidadDeJuego == 2) {
        /* si el jugador elige la segunda opción... */
        cout << "\nJugador 1, por favor ingresa tu nombre: ";
        getline(cin, jugador); /* lee el nombre del jugador 1 */
        cout << "Jugador 2, por favor ingresa tu nombre: ";
        getline(cin, jugador2); /* lee el nombre del jugador 2 */
        cout << "Jugador 1, por favor escribe la palabra secreta: ";
        string palabra;
        getline(cin, palabra); /* lee la palabra ingresada por el jugador 1 */
        escribirPalabraDesdeConsola(palabra); /* inicializa la palabra secreta con la palabra ingresada */
        if (palabraSecreta.empty()) { /* si la palabra está vacía */
            cout << "No se ingresó ninguna palabra. Terminando el juego.\n";
            return; /* termina el método */
        }
    }

    cout << jugador << ", la palabra tiene " << palabraSecreta.length() << " letras.\n";
    /* esto informa al jugador cuántas letras tiene la palabra secreta */

    char letra; /* esta es la variable que va a almacenar la letra ingresada por el jugador */
    bool gano = false; /* esta es la variable que va a indicar si el jugador ganó o no */

    while (intentosUsados < intentosMaximos && palabraAdivinada != palabraSecreta) {
        /* este es el bucle principal del juego !!!!!!!!
        se ejecuta mientras el jugador tenga intentos restantes y no haya adivinado la palabra */
        cout << "\nPalabra: " << palabraAdivinada << "\n";
        /* muestra la palabra adivinada hasta el momento */
        cout << "Intentos restantes: " << (intentosMaximos - intentosUsados) << "\n";
        /* muestra el número de intentos restantes */
        cout << "Ingresa una letra: ";
        cin >> letra;
        /* lee la letra ingresada por el jugador */
        letra = tolower(letra);
        /* convierte la letra a minúscula para evitar problemas de mayúsculas y minúsculas */

        bool acierto = false;
        /* esta es la variable que va a indicar si el jugador acertó o no */
        for (size_t i = 0; i < palabraSecreta.length(); i++) {
            /* este es el bucle que recorre cada letra de la palabra secreta */
            if (tolower(palabraSecreta[i]) == letra && palabraAdivinada[i] == '_') {
                /* eso dice que si la letra ingresada coincide con una letra de la palabra secreta
                y esa letra aún no ha sido adivinada... */
                palabraAdivinada[i] = palabraSecreta[i]; // entonces se conserva la letra original
                acierto = true; /* y se marca como acierto */
            }
        }

        if (!acierto) {
            /* si no hubo acierto... */
            intentosUsados++;
            /* se incrementa el número de intentos usados */
        }
    }

    if (palabraAdivinada == palabraSecreta) { 
        /* si la palabra adivinada es igual a la palabra secreta... */
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << "\n";
        gano = true;
        /* se informa al jugador que ganó y se marca como verdadero */
    } else {
        cout << "\nPerdiste. La palabra era: " << palabraSecreta << "\n";
        /* si no, se informa al jugador que perdió y se muestra la palabra secreta */
    }

    guardarHistorialAhorcado(jugador, jugador2, gano, intentosMaximos - intentosUsados);
    /* guarda el historial del juego con el nombre del jugador, si ganó o no,
    y la puntuación (intentos restantes) */
}

void Ahorcado::guardarHistorial(const string& jugador, bool gano, int puntuacion) {
    ofstream archivo("historial_ahorcado.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << ", Resultado: " << (gano ? "Ganó" : "Perdió") << ", Puntos: " << puntuacion << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de historial para escribir." << endl;
    }
}

void Ahorcado::guardarHistorialAhorcado(const string& jugador, const string& jugador2, bool gano, int puntuacion) {
    /* este es el método que se va a ejecutar al guardar el historial */
    ofstream archivo("historial.txt", ios::app);
    /* abre el archivo historial.txt en modo append (agregar al final) */
    if (archivo.is_open()) {
        /* si el archivo se abre correctamente */
        time_t now = time(0);
        /* obtiene el tiempo actual */
        tm* localtm = localtime(&now);
        /* convierte el tiempo actual a la hora local */

        archivo << (1900 + localtm->tm_year) << "-"
                << (1 + localtm->tm_mon) << "-"
                << localtm->tm_mday << " "
                << jugador << "-" << jugador2 << " AH "
                << (gano ? "G" : "P") << " "
                << puntuacion << "\n";
        /* escribe la fecha, el nombre del jugador, si ganó o perdió (G o P),
        y la puntuación en el archivo historial.txt */

        archivo.close();
        /* cierra el archivo después de escribir */
    }
}

/* esta es la implementacion del juego ahorcado */
