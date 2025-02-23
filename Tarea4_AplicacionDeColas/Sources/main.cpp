#include <ctime>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #include <conio.h> // Para Windows
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include "../Headers/Cola.hpp"

using namespace std;

// Listas de nombres y apellidos
vector<string> nombres = {"Ana", "Pablo", "Laura", "Javier", "Marta", "Luis", "Sofia", "Juan", "Carlos", "Elena",
                                    "Diego", "Isabel", "Sergio", "Maria", "Jose", "Rosa", "David", "Lucia", "Manuel", "Raquel",
                                    "Jorge", "Carmen", "Alberto", "Patricia", "Ricardo", "Teresa", "Fernando", "Beatriz",
                                    "Francisco", "Gloria", "Eduardo", "Teresa", "Sergio", "Pilar", "Vicente", "Yolanda", "Antonio",
                                    "Victoria", "Felipe", "Marta", "Ruben", "Alicia", "Guillermo", "Clara", "Enrique", "Rosa",
                                    "Javier", "Andrea", "Guillermo", "Blanca"};

vector<string> apellidos = {"García", "López", "Martínez", "Pérez", "Sánchez", "Rodríguez", "González",
                                      "Fernández", "Gómez", "Díaz", "Álvarez", "Jiménez", "Romero", "Muñoz", "Ruiz",
                                      "Hernández", "Moreno", "Martín", "Castro", "López", "Torres", "Navarro", "Díaz",
                                      "Vázquez", "Jiménez", "García", "Ortega", "Delgado", "Ramos", "Sánchez", "Moreno",
                                      "García", "Pérez", "Gómez", "Molina", "Álvarez", "Ruiz", "Torres", "Fernández", "Romero",
                                      "Díaz", "Soto", "Aguilar", "González", "Martín", "Hernández", "Navarro", "Castillo",
                                      "Herrera", "Paredes"};

string generarNombreAleatorio(); 

void limpiarPantalla();

void waitForKeyPress();

int main() {
    srand(time(nullptr));  // ✅ Semilla de números aleatorios solo una vez en `main()`

    limpiarPantalla();

    try {
        /*Cola<string> nombresCola;

        for (int i = 0; i < 10; ++i) { 
            string nombreCompleto = generarNombreAleatorio();
            nombresCola.Encolar(nombreCompleto);
        }

        nombresCola.Imprimir();*/
        for(int i = 0; i < 10; ++i)
            {
                cout << "Banco" << endl;
                cout << "Reloj: " << i+1 << endl;
                this_thread::sleep_for(chrono::seconds(1));
                limpiarPantalla();
            }
    } catch (const char* mensaje) {
        cerr << "\nError: " << mensaje << endl;
    }


    waitForKeyPress();
    return 0;
}

// ✅ Corrección: Eliminamos `srand(time(0))`
string generarNombreAleatorio() {
    int indiceNombre = rand() % nombres.size();
    int indiceApellido = rand() % apellidos.size();
    return nombres[indiceNombre] + " " + apellidos[indiceApellido];
}


void limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Comando para limpiar en Windows
#else
    system("clear");  // Comando para limpiar en Linux/macOS
#endif
}

void waitForKeyPress() {
    cout << "Presiona una tecla para continuar..." << flush;

#ifdef _WIN32
    _getch();
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

