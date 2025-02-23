#include <ctime>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #include <conio.h> // Para manejar entradas de teclado en Windows
#else
    #include <termios.h>  // Librerías necesarias para leer entradas sin necesidad de presionar enter en Linux/macOS
    #include <unistd.h>
#endif

#include "../Headers/Cola.hpp"  

using namespace std;

// Listas de nombres y apellidos para generar nombres aleatorios
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

// Declaración de funciones
string generarNombreAleatorio();  // Función para generar un nombre aleatorio
void limpiarPantalla();  // Función para limpiar la pantalla dependiendo del sistema operativo
void waitForKeyPress();  // Función para esperar la pulsación de una tecla

int main() {
    srand(time(nullptr));  // Inicializamos la semilla para la generación de números aleatorios, solo una vez en `main()`

    limpiarPantalla();  // Limpiamos la pantalla antes de iniciar el bucle


    try {

        Cola<string> nombresCola;
        Cola<string> cajaUno;
        string nombreCompleto;
        string personaCajaUno;
        int esperaCajaUno = 0, atencionCajaUno = 0;

        limpiarPantalla();

       

        // Bucle que simula la acción de un reloj
        for(int i = 0; i < 10; ++i)
        { 
            cout << "Banco" << endl;  // Se imprime "Banco" en cada iteración
            cout << "Reloj: " << i+1 << endl;  // Se imprime el valor del contador con un mensaje de reloj
            cout << "\n\n\n"; 

            
                if(nombresCola.EstaVacia())
                    {
                        cout << "\t\tcaja 1: esta vacia" << endl;
                    } else {
                        personaCajaUno = nombresCola.ConocerPrim();
                        cout << "\t\tcaja 1: atendiendo a " << personaCajaUno << endl;
                        cajaUno.Encolar(personaCajaUno);
                    }

                nombreCompleto = generarNombreAleatorio();
                nombresCola.Encolar(nombreCompleto);

                this_thread::sleep_for(chrono::seconds(3));  // Esperamos entre iteraciones

                // Solo limpiamos la pantalla después de un retraso adicional, dando tiempo para visualizar
                limpiarPantalla();  // Limpiamos la pantalla para simular un reloj en movimiento
            

        }    




    } catch (const char* mensaje) {
        cerr << "\nError: " << mensaje << endl;  // En caso de error, lo mostramos por consola
    }

    waitForKeyPress();  // Esperamos que el usuario presione una tecla para continuar

    return 0;  // Finalizamos la ejecución del programa
}

// ✅ Función para generar un nombre aleatorio combinando un nombre y un apellido de las listas definidas
string generarNombreAleatorio() {
    int indiceNombre = rand() % nombres.size();  // Generamos un índice aleatorio para los nombres
    int indiceApellido = rand() % apellidos.size();  // Generamos un índice aleatorio para los apellidos
    return nombres[indiceNombre] + " " + apellidos[indiceApellido];  // Devolvemos el nombre completo aleatorio
}

// Función para limpiar la pantalla dependiendo del sistema operativo
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Comando para limpiar en Windows
#else
    system("clear");  // Comando para limpiar en Linux/macOS
#endif
}

// Función para esperar la pulsación de una tecla para continuar
void waitForKeyPress() {
    cout << "Presiona una tecla para continuar..." << flush;  // Mensaje para el usuario

#ifdef _WIN32
    _getch();  // Usamos _getch() para capturar la tecla en Windows
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);  // Obtenemos la configuración actual del terminal
    newt = oldt;
    newt.c_lflag &= ~ICANON;  // Deshabilitamos el modo de línea de comando para poder leer sin Enter
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();  // Leemos un solo carácter sin necesidad de presionar Enter
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restauramos la configuración original del terminal
#endif
}
