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

vector<string> nombres = {"Ana", "Pablo", "Laura", "Javier", "Marta", "Luis", "Sofia", "Juan", "Carlos", "Elena",
                          "Dino", "Isabel", "Sergio", "Maria", "Jose", "Rosa", "David", "Lucia", "Manuel", "Raquel"};

vector<string> apellidos = {"Garcia", "Lopez", "Martinez", "Perez", "Sánchez", "Rodriguez", "González",
                            "Fernández", "Gómez", "Diaz", "Álvarez", "Jimenez", "Romero", "Muñoz", "Ruiz"};

string generarNombreAleatorio() {
    int indiceNombre = rand() % nombres.size();
    int indiceApellido = rand() % apellidos.size();
    return nombres[indiceNombre] + " " + apellidos[indiceApellido];
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
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

int main() {
    srand(time(nullptr));
    limpiarPantalla();

    try {
        Cola<string> colaClientes;
        Cola<string> cajas[3];
        int tiempoAtencionBanco = (rand() % (240 - 120 + 1)) + 120;
        int tiempoAtencionCajas[3] = {0};
        int inicioAtencionCajas[3] = {0};
        bool cajasOcupadas[3] = {false};
        string clientesActuales[3] = {""};

        for (int i = 0; i < tiempoAtencionBanco; ++i) {
            cout << "Las cajas atenderan a cuantas personas puedan en " << tiempoAtencionBanco << endl;
            cout << "Banco" << endl;
            cout << "Reloj: " << i + 1 << endl;
            cout << "\n\n";

            for (int caja = 0; caja < 3; ++caja) {
                if (cajasOcupadas[caja] && i >= tiempoAtencionCajas[caja]) {
                    cajas[caja].Encolar(clientesActuales[caja]);
                    clientesActuales[caja] = "";
                    cajasOcupadas[caja] = false;
                }

                if (!cajasOcupadas[caja] && !colaClientes.EstaVacia()) {
                    clientesActuales[caja] = colaClientes.ConocerPrim();
                    colaClientes.Desencolar();
                    int duracionAtencion = (rand() % 15) + 1;
                    tiempoAtencionCajas[caja] = i + duracionAtencion;
                    inicioAtencionCajas[caja] = i;
                    cajasOcupadas[caja] = true;
                }

                if (cajasOcupadas[caja]) {
                    int tiempoAtendido = i - inicioAtencionCajas[caja];
                    cout << "\tCaja " << caja + 1 << ": Atendiendo a " << clientesActuales[caja]
                         << " (Tiempo atendido: " << tiempoAtendido << " seg)" << endl;
                } else {
                    cout << "\tCaja " << caja + 1 << ": Está vacía" << endl;
                }
            }

            if (rand() % 2 == 0) {
                string nuevoCliente = generarNombreAleatorio();
                colaClientes.Encolar(nuevoCliente);
                cout << "\n\n\tNuevo cliente: " << nuevoCliente << endl;
            } else cout << "\n\n\n";

            if (colaClientes.ObtenerCantElem() != 0) {
                cout << "\n\nClientes en espera: " << endl;
                colaClientes.Imprimir();
            } else cout << "\n\nClientes en espera: " << endl;

            this_thread::sleep_for(chrono::seconds(1));
            limpiarPantalla();
        }

        for (int caja = 0; caja < 3; ++caja) {
            if (cajasOcupadas[caja]) {
                cajas[caja].Encolar(clientesActuales[caja]);
                clientesActuales[caja] = "";
                cajasOcupadas[caja] = false;
            }
        }

        for (int caja = 0; caja < 3; ++caja) {
            cout << "La caja " << caja + 1 << " atendió a " << cajas[caja].ObtenerCantElem() << " personas:" << endl;
            cajas[caja].Imprimir();
            cout << endl;
        }

        cout << "\n\nQuedaron " << colaClientes.ObtenerCantElem() << " clientes en la cola de espera:" << endl;
        colaClientes.Imprimir();

    } catch (const char* mensaje) {
        cerr << "\nError: " << mensaje << endl;
    }

    waitForKeyPress();
    return 0;
}

