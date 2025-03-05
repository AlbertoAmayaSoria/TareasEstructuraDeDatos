#include <iostream>
#include <vector>
#include <cstdlib>
//#include <ctime>
//#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#include "../Headers/ListaDoblementeEnlazadaOrdenada.hpp"

// Lista de nombres
std::vector<std::string> nombres = {"Ana", "Pablo", "Laura", "Javier", "Marta", "Luis", "Sofia", "Juan", "Carlos", "Elena", 
                                    "Diego", "Isabel", "Sergio", "Maria", "Jose", "Rosa", "David", "Lucia", "Manuel", "Raquel", 
                                    "Jorge", "Carmen", "Alberto", "Patricia", "Ricardo", "Teresa", "Fernando", "Beatriz", 
                                    "Francisco", "Gloria", "Eduardo", "Teresa", "Sergio", "Pilar", "Vicente", "Yolanda", "Antonio", 
                                    "Victoria", "Felipe", "Marta", "Ruben", "Alicia", "Guillermo", "Clara", "Enrique", "Rosa", 
                                    "Javier", "Andrea", "Guillermo", "Blanca"};

// Lista de apellidos
std::vector<std::string> apellidos = {"García", "López", "Martínez", "Pérez", "Sánchez", "Rodríguez", "González", 
                                      "Fernández", "Gómez", "Díaz", "Álvarez", "Jiménez", "Romero", "Muñoz", "Ruiz", 
                                      "Hernández", "Moreno", "Martín", "Castro", "López", "Torres", "Navarro", "Díaz", 
                                      "Vázquez", "Jiménez", "García", "Ortega", "Delgado", "Ramos", "Sánchez", "Moreno", 
                                      "García", "Pérez", "Gómez", "Molina", "Álvarez", "Ruiz", "Torres", "Fernández", "Romero", 
                                      "Díaz", "Soto", "Aguilar", "González", "Martín", "Hernández", "Navarro", "Castillo", 
                                      "Herrera", "Paredes"};

std::string generarNombreAleatorio();
int main()
{
    /*ListaDoblementeEnlazadaOrdenada<int> Lista;
    for(int i = 0; i < 10; ++i)
    {
        Lista.insertarInicio(i+1);
    }
    Lista.imprimir();
    std::cout << "primero: " << Lista.obtenerPrimero() << std::endl;
    std::cout << "ultimo: " << Lista.obtenerUltimo() << std::endl;
    Lista.insertarFinal(4);
    Lista.insertarPosicion(6, 3);
    Lista.imprimir();
    Lista.eliminarInicio();
    Lista.imprimir();

    std::cout << "___________________________________________________" << std::endl;
    ListaDoblementeEnlazadaOrdenada<int> ListaDos;
    for(int i = 0; i < 10; ++i)
    {
        ListaDos.insertarFinal(i+1);
    }
    ListaDos.imprimir();
    std::cout << "primero: " << ListaDos.obtenerPrimero() << std::endl;
    std::cout << "ultimo: " << ListaDos.obtenerUltimo() << std::endl;
    ListaDos.insertarFinal(4);
    ListaDos.insertarPosicion(6, 0);
    ListaDos.imprimir();
    ListaDos.eliminarInicio();
    ListaDos.imprimir();*/

    ListaDoblementeEnlazadaOrdenada<std::string> listaDePersonas;
    int tiempoTotal = 5;  // 120 segundos
    int tiempoTranscurrido = 0;

    while (tiempoTranscurrido < tiempoTotal) {
        // Generamos una persona aleatoria
        std::string persona = generarNombreAleatorio();
        
        // Insertamos la persona en la lista
        listaDePersonas.insertarFinal(persona);

        // Mostramos la persona que fue añadida a la lista
        std::cout << "Persona generada y añadida a la lista: " << persona << std::endl;

        // Esperamos un tiempo aleatorio entre 1 y 3 segundos antes de generar la siguiente persona
        int tiempoEspera = /*rand() % 3 +*/ 1;  // Aleatorio entre 1 y 3 segundos
        std::this_thread::sleep_for(std::chrono::seconds(tiempoEspera));

        // Aumentamos el tiempo transcurrido
        tiempoTranscurrido += tiempoEspera;
    }

    std::cout << "\nLa generación de personas ha terminado." << std::endl;
    std::cout << "Total de personas generadas: " << listaDePersonas.obtenerTamaño() << std::endl;

    // Mostrar el contenido de la lista
    listaDePersonas.imprimir();
    std::string primeraPersona;
    primeraPersona = listaDePersonas.obtenerPrimero();
    std::cout << "la primera persona en la lista fue: " << primeraPersona << std::endl;
    std::string ultimaPersona;
    ultimaPersona = listaDePersonas.obtenerUltimo();
    std::cout << "La ultima persona en la lista fue: " << ultimaPersona << std::endl;
    std::cout << "La lista al contrario: " << std::endl;
    listaDePersonas.imprimirReversa();
    listaDePersonas.insertarFinal("Rosa Godoi");
    listaDePersonas.imprimir();
    if(listaDePersonas.buscar("Rosa Godoi")){
        std::cout << "Si llego Rosa";
    } else std::cout << "No llego Rosa";
    std::string persona = listaDePersonas.obtenerEnPosicion(4);
    std::cout << persona;

    return 0;
}


std::string generarNombreAleatorio() {
    srand(time(0));  // Inicializamos la semilla aleatoria

    int indiceNombre = rand() % nombres.size();     // Generamos un índice aleatorio para el nombre
    int indiceApellido = rand() % apellidos.size(); // Generamos un índice aleatorio para el apellido

    return nombres[indiceNombre] + " " + apellidos[indiceApellido];  // Combinamos nombre y apellido
}
