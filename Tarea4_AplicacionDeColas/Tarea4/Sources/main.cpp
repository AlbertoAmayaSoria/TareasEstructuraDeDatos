#include <ctime>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include "../Headers/Cola.h"

using namespace std;

// Listas de nombres y apellidos para generar clientes aleatorios
vector<string> nombres = {"Ana", "Pablo", "Laura", "Javier", "Marta", "Luis", "Sofia", "Juan", "Carlos", "Elena",
                          "Dino", "Isabel", "Sergio", "Maria", "Jose", "Rosa", "David", "Lucia", "Manuel", "Raquel"};

vector<string> apellidos = {"Garcia", "Lopez", "Martinez", "Perez", "Sanchez", "Rodriguez", "Gonzalez",
                            "Fernandez", "Gomez", "Diaz", "Alvarez", "Jimenez", "Romero", "Muñoz", "Ruiz"};

// Genera un nombre aleatorio combinando un nombre y un apellido
string generarNombreAleatorio() {
    int indiceNombre = rand() % nombres.size();
    int indiceApellido = rand() % apellidos.size();
    return nombres[indiceNombre] + " " + apellidos[indiceApellido];
}

// Limpia la pantalla según el sistema operativo
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Espera a que el usuario presione una tecla antes de continuar
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

int main() {
    srand(time(nullptr)); // Inicializa la semilla aleatoria
    limpiarPantalla(); // Limpia la pantalla antes de empezar

    try {
        Cola<string> colaClientes; // Cola de clientes en espera
        Cola<string> cajas[3]; // Tres colas para cada caja de atención
        
        // Duración total de atención del banco (entre 120 y 240 segundos)
        int tiempoAtencionBanco = (rand() % (240 - 120 + 1)) + 120;
        
        int tiempoAtencionCajas[3] = {0}; // Tiempo en que cada caja terminará de atender
        int inicioAtencionCajas[3] = {0}; // Momento en que cada caja comenzó a atender
        bool cajasOcupadas[3] = {false}; // Estado de cada caja (ocupada o libre)
        string clientesActuales[3] = {""}; // Clientes atendidos en cada caja

        for (int i = 0; i < tiempoAtencionBanco; ++i) {
            cout << "Las cajas atenderán a cuantas personas puedan en " << tiempoAtencionBanco << " minutos." << endl;
            cout << "Banco" << endl;
            cout << "Reloj: " << i + 1 << " minutos" << endl;
            cout << "\n\n";

            // Itera sobre las 3 cajas para manejar la atención de los clientes
            for (int caja = 0; caja < 3; ++caja) {
                // Si la caja terminó de atender a un cliente, lo almacena en su historial y queda libre
                if (cajasOcupadas[caja] && i >= tiempoAtencionCajas[caja]) {
                    cajas[caja].Encolar(clientesActuales[caja]);
                    clientesActuales[caja] = "";
                    cajasOcupadas[caja] = false;
                }

                // Si la caja está libre y hay clientes en espera, atiende a uno nuevo
                if (!cajasOcupadas[caja] && !colaClientes.EstaVacia()) {
                    clientesActuales[caja] = colaClientes.ConocerPrim();
                    colaClientes.Desencolar();
                    int duracionAtencion = (rand() % 15) + 1; // Tiempo aleatorio de atención (1-15 seg)
                    tiempoAtencionCajas[caja] = i + duracionAtencion;
                    inicioAtencionCajas[caja] = i;
                    cajasOcupadas[caja] = true;
                }

                // Muestra el estado de cada caja
                if (cajasOcupadas[caja]) {
                    int tiempoAtendido = i - inicioAtencionCajas[caja];
                    cout << "\tCaja " << caja + 1 << ": Atendiendo a " << clientesActuales[caja]
                         << " (Tiempo atendido: " << tiempoAtendido << " min)" << endl;
                } else {
                    cout << "\tCaja " << caja + 1 << ": Está vacía" << endl;
                }
            }

            // Posibilidad de que llegue un nuevo cliente cada segundo
            if (rand() % 2 == 0) {
                string nuevoCliente = generarNombreAleatorio();
                colaClientes.Encolar(nuevoCliente);
                cout << "\n\n\tNuevo cliente: " << nuevoCliente << endl;
            } else {
                cout << "\n\n\n";
            }

            // Muestra los clientes en espera
            if (!colaClientes.EstaVacia()) {
                cout << "\n\nClientes en espera: " << endl;
                colaClientes.Imprimir();
            } else {
                cout << "\n\nClientes en espera: Ninguno" << endl;
            }

            this_thread::sleep_for(chrono::seconds(1)); // Pausa para simular tiempo real
            limpiarPantalla(); // Limpia la pantalla para actualizar la simulación
        }
        
        cout << "DEBUG: Mostrando resumen final de clientes atendidos y en espera..." << endl;
        

        // Al final de la simulación, se almacenan los clientes en proceso de atención
        for (int caja = 0; caja < 3; ++caja) {
            if (cajasOcupadas[caja]) {
                cajas[caja].Encolar(clientesActuales[caja]);
                clientesActuales[caja] = "";
                cajasOcupadas[caja] = false;
            }
        }

        limpiarPantalla();
        this_thread::sleep_for(chrono::seconds(1)); 

        // Se muestra el resumen de atención de cada caja
        for (int caja = 0; caja < 3; ++caja) {
            cout << "La caja " << caja + 1 << " atendió a " << cajas[caja].ObtenerCantElem() << " personas:" << endl;
            cajas[caja].Imprimir();
            cout << endl;
            this_thread::sleep_for(chrono::seconds(1)); //sin esta pausa el programa comienza a hacer impresiones raras
        }

        // Se muestra la cantidad de clientes que quedaron en espera
        cout << "\n\nQuedaron " << colaClientes.ObtenerCantElem() << " clientes en la cola de espera:" << endl;
        colaClientes.Imprimir();

    } catch (const char* mensaje) {
        cerr << "\nError: " << mensaje << endl;
    }

    waitForKeyPress(); // Espera la interacción del usuario antes de cerrar
    return 0;
}

