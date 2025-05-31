#include "Ahorcado.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

// Constructor
Ahorcado::Ahorcado(string nombre) : Juego(nombre), intentos(6) {
    // Palabras por defecto
    palabras = {"PROGRAMACION", "COMPUTADORA", "AHORCADO", "POO", "HERENCIA"};
    seleccionarPalabra();
    palabraAdivinada = string(palabraSecreta.length(), '_');
}

// Método para seleccionar palabra aleatoria
void Ahorcado::seleccionarPalabra() {
    // Semilla para números aleatorios usando time
    static bool semillaLista = false;
    if (!semillaLista) {
        srand(time(0));
        semillaLista = true;
    }
    
    if (!palabras.empty()) {
        int indice = rand() % palabras.size();
        palabraSecreta = palabras[indice];
    } else {
        palabraSecreta = "PROGRAMACION"; // Palabra por defecto
    }
}

// Verificar si la letra está en la palabra
bool Ahorcado::verificarLetra(char letra) {
    bool encontrada = false;
    letra = toupper(letra);
    
    for (int i = 0; i < palabraSecreta.length(); i++) {
        if (palabraSecreta[i] == letra) {
            palabraAdivinada[i] = letra;
            encontrada = true;
        }
    }
    return encontrada;
}

// Mostrar instrucciones del juego
void Ahorcado::mostrarInstrucciones() {
    cout << "\n=== INSTRUCCIONES DEL AHORCADO ===" << endl;
    cout << "Adivina la palabra letra por letra" << endl;
    cout << "Tienes " << intentos << " intentos fallidos permitidos" << endl;
    cout << "La palabra tiene " << palabraSecreta.length() << " letras" << endl;
}

// Método principal del juego
void Ahorcado::jugar() {
    mostrarInstrucciones();
    
    while (intentos > 0 && palabraAdivinada != palabraSecreta) {
        cout << "\nPalabra: ";
        for (char c : palabraAdivinada) {
            cout << c << " ";
        }
        cout << "\nIntentos restantes: " << intentos << endl;
        
        char letra;
        cout << "Ingresa una letra: ";
        cin >> letra;
        
        if (!verificarLetra(letra)) {
            cout << "La letra no está en la palabra!" << endl;
            intentos--;
        } else {
            cout << "Correcto!" << endl;
        }
    }
    
    // Resultado final
    if (palabraAdivinada == palabraSecreta) {
        setPuntuacion(intentos * 10);
        cout << "\n¡GANASTE! Puntuación: " << getPuntuacion() << endl;
        guardarResultado("Gano");
    } else {
        cout << "\n¡PERDISTE! La palabra era: " << palabraSecreta << endl;
        guardarResultado("Perdio");
    }
}