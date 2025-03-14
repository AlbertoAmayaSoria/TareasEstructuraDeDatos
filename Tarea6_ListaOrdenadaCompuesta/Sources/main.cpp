#include <iostream>
#include "../Headers/ListaOrdenadaCompuesta.hpp"

int main() {
    // Crear una prueba ordenada compuesta de enteros
    ListaOrdenadaCompuesta<int> prueba;

    std::cout << prueba.tamaño() << std::endl;

    // Insertar algunos elementos
    std::cout << "Insertando elementos en la lista ordenada:" << std::endl;
    prueba.insertar(5);
    prueba.insertar(1);
    prueba.insertar(3);
    prueba.insertar(7);
    prueba.insertar(2);
    prueba.insertar(6);

    // Imprimir la prueba en orden
    std::cout << "Lista en orden: ";
    prueba.imprimir();

    // Imprimir la prueba en orden inverso
    std::cout << "Lista en orden inverso: ";
    prueba.imprimirReversa();

    // Buscar un elemento en la prueba
    int valorBuscar = 3;
    std::cout << "¿El valor " << valorBuscar << " está en la lista? ";
    if(prueba.buscar(valorBuscar)) 
    {
        std::cout << "Sí" << std::endl;
    }else std::cout << "No" << std::endl;

    // Eliminar un elemento (primera ocurrencia)
    int valorEliminar = 3;
    std::cout << "Eliminando el valor " << valorEliminar << " de la lista." << std::endl;
    prueba.eliminar(valorEliminar);

    // Imprimir la prueba después de eliminar
    std::cout << "Lista después de eliminar " << valorEliminar << ": ";
    prueba.imprimir();

    // Eliminar un valor que no existe en la prueba
    int valorInexistente = 100;
    std::cout << "Intentando eliminar el valor " << valorInexistente << " (que no está en la lista)." << std::endl;
    prueba.eliminar(valorInexistente);

    // Verificar si la prueba está vacía
    std::cout << "¿Está la lista vacía? ";
    std::cout << (prueba.estaVacia() ? "Sí" : "No") << std::endl;

    // Vaciar la prueba
    std::cout << "Vaciando la lista..." << std::endl;
    prueba.vaciar();

    // Verificar el tamaño de la prueba después de vaciarla
    std::cout << "Tamaño de la prueba después de vaciarla: " << prueba.tamaño() << std::endl;

    // Imprimir la prueba después de vaciarla
    std::cout << "Lista vacía: ";
    prueba.imprimir();

    return 0;
}

