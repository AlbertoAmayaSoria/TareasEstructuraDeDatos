#include <ctime>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #include <conio.h> // Para detectar pulsaciones de teclas en Windows
#else
    #include <termios.h> // Para manipular el terminal en sistemas Unix-like
    #include <unistd.h>  // Para control de la entrada de usuario en sistemas Unix-like
#endif

#include "../Headers/Cola.hpp" // Suponemos que esta es la clase Cola definida en otro archivo

using namespace std;

// Listas de nombres y apellidos para generar clientes aleatorios
vector<string> nombres = {"Ana", "Pablo", "Laura", "Javier", "Marta", "Luis", "Sofia", "Juan", "Carlos", "Elena",
                          "Diego", "Isabel", "Sergio", "Maria", "Jose", "Rosa", "David", "Lucia", "Manuel", "Raquel"};

vector<string> apellidos = {"García", "López", "Martínez", "Pérez", "Sánchez", "Rodríguez", "González",
                            "Fernández", "Gómez", "Díaz", "Álvarez", "Jiménez", "Romero", "Muñoz", "Ruiz"};

// Función que genera un nombre aleatorio combinando un nombre y un apellido de las listas
string generarNombreAleatorio() {
    int indiceNombre = rand() % nombres.size();  // Selecciona un nombre aleatorio
    int indiceApellido = rand() % apellidos.size();  // Selecciona un apellido aleatorio
    return nombres[indiceNombre] + " " + apellidos[indiceApellido];  // Retorna el nombre completo
}

// Función para limpiar la pantalla, adaptada para Windows y sistemas Unix-like
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // En Windows usa "cls"
#else
    system("clear");  // En sistemas Unix-like usa "clear"
#endif
}

// Función que espera a que el usuario presione una tecla
void waitForKeyPress() {
    cout << "Presiona una tecla para continuar..." << flush;  // Muestra mensaje en consola
#ifdef _WIN32
    _getch();                                   // En Windows usa _getch() para esperar la tecla
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);             // Obtiene la configuración actual del terminal
    newt = oldt;
    newt.c_lflag &= ~ICANON;                    // Configura el terminal para no esperar por un salto de línea
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    // Cambia la configuración del terminal
    getchar();                                  // Lee un carácter del usuario
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);    // Restaura la configuración del terminal
#endif
}

int main() {
    srand(time(nullptr));   // Inicializa la semilla para la función rand() con el tiempo actual
    limpiarPantalla();      // Limpia la pantalla al inicio

    try {
        Cola<string> colaClientes;          // Cola que almacena los clientes esperando atención
        Cola<string> cajas[3];              // Tres cajas de atención
        int tiempoAtencionBanco = 30;       // Duración de la simulación (30 segundos)
        int tiempoAtencionCajas[3] = {0};   // Tiempo de atención restante para cada caja
        bool cajasOcupadas[3] = {false};    // Estado de las cajas, si están ocupadas o no
        string clientesActuales[3] = {""};  // Clientes siendo atendidos en cada caja

        // Simulación del banco durante el tiempo de atención
        for (int i = 0; i < tiempoAtencionBanco; ++i) {
            cout << "Banco" << endl;
            cout << "Reloj: " << i + 1 << endl;
            cout << "\n\n";

            // Procesa cada una de las 3 cajas
            for (int caja = 0; caja < 3; ++caja) {
                // Si la caja está ocupada y el tiempo de atención ha terminado, libera la caja
                if (cajasOcupadas[caja] && i >= tiempoAtencionCajas[caja]) {
                    cajas[caja].Encolar(clientesActuales[caja]);  // Encola al cliente de vuelta en la cola
                    clientesActuales[caja] = "";  // Limpiar cliente actual
                    cajasOcupadas[caja] = false;  // Marca la caja como libre
                }

                // Si la caja no está ocupada y hay clientes esperando, asigna un nuevo cliente
                if (!cajasOcupadas[caja] && !colaClientes.EstaVacia()) {
                    clientesActuales[caja] = colaClientes.ConocerPrim();  // Obtiene el siguiente cliente
                    colaClientes.Desencolar();  // Elimina el cliente de la cola
                    tiempoAtencionCajas[caja] = i + (rand() % 15) + 1;  // Define el tiempo de atención para esta caja
                    cajasOcupadas[caja] = true;  // Marca la caja como ocupada
                }

                // Muestra el estado de cada caja
                if (cajasOcupadas[caja]) {
                    cout << "\tCaja " << caja + 1 << ": Atendiendo a " << clientesActuales[caja] << endl;
                } else {
                    cout << "\tCaja " << caja + 1 << ": Está vacía" << endl;
                }
            }

            // Genera un nuevo cliente aleatorio con un 50% de probabilidad
            if (rand() % 2 == 0) {
                string nuevoCliente = generarNombreAleatorio();
                colaClientes.Encolar(nuevoCliente);  // Encola al nuevo cliente
                cout << "\n\n\tNuevo cliente: " << nuevoCliente << endl;
            } else cout << "\n\n\n";

            // Muestra la lista de clientes que están esperando
            if (colaClientes.ObtenerCantElem() != 0) {
                cout << "\n\nClientes en espera: " << endl;
                colaClientes.Imprimir();  // Imprime la cola de clientes
            } else cout << "\n\nClientes en espera: " << endl;

            this_thread::sleep_for(chrono::seconds(1));  // Pausa de 1 segundo
            limpiarPantalla();  // Limpia la pantalla después de cada ciclo
        }

        // Al finalizar el tiempo, procesa los clientes restantes en cada caja
        for (int caja = 0; caja < 3; ++caja) {
            if (cajasOcupadas[caja]) {
                cajas[caja].Encolar(clientesActuales[caja]);  // Encola el cliente finalizado
                clientesActuales[caja] = "";  // Limpia el cliente actual
                cajasOcupadas[caja] = false;  // Marca la caja como libre
            }
        }

        // Muestra el número de clientes atendidos por cada caja
        for (int caja = 0; caja < 3; ++caja) {
            cout << "La caja " << caja + 1 << " atendió a " << cajas[caja].ObtenerCantElem() << " personas, cuyo orden de atención fue: " << endl;
            cajas[caja].Imprimir();  // Imprime el orden de los clientes atendidos
            cout << endl;
        }

        // Muestra los clientes que aún quedan en espera
        cout << "\n\nQuedaron " << colaClientes.ObtenerCantElem() << " clientes en la cola de espera: " << endl;
        colaClientes.Imprimir();  // Imprime la cola de espera

    } catch (const char* mensaje) {
        cerr << "\nError: " << mensaje << endl;  // Muestra cualquier error capturado
    }

    waitForKeyPress();  // Espera la pulsación de una tecla antes de terminar el programa
    return 0;  // Fin del programa
}

