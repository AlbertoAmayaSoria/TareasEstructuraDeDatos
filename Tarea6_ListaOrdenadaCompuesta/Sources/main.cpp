#include <iostream>
#include "../Headers/ListaOrdenadaCompuesta.hpp"

int main() {
    // Crear una lista ordenada compuesta de enteros
    ListaOrdenadaCompuesta<int> lista;

    // Insertar algunos elementos
    std::cout << "Insertando elementos en la lista ordenada:" << std::endl;
    lista.insertar(5);
    lista.insertar(1);
    lista.insertar(3);
    lista.insertar(7);
    lista.insertar(2);
    lista.insertar(6);

    // Imprimir la lista en orden
    std::cout << "Lista en orden: ";
    lista.imprimir();

    // Imprimir la lista en orden inverso
    std::cout << "Lista en orden inverso: ";
    lista.imprimirReversa();

    // Buscar un elemento en la lista
    int valorBuscar = 3;
    std::cout << "¿El valor " << valorBuscar << " está en la lista? ";
    if(lista.buscar(valorBuscar)) 
    {
        std::cout << "Sí" << std::endl;
    }else std::cout << "No" << std::endl;

    // Eliminar un elemento (primera ocurrencia)
    int valorEliminar = 3;
    std::cout << "Eliminando el valor " << valorEliminar << " de la lista." << std::endl;
    lista.eliminar(valorEliminar);

    // Imprimir la lista después de eliminar
    std::cout << "Lista después de eliminar " << valorEliminar << ": ";
    lista.imprimir();

    // Eliminar un valor que no existe en la lista
    int valorInexistente = 100;
    std::cout << "Intentando eliminar el valor " << valorInexistente << " (que no está en la lista)." << std::endl;
    lista.eliminar(valorInexistente);

    // Verificar si la lista está vacía
    std::cout << "¿Está la lista vacía? ";
    std::cout << (lista.estaVacia() ? "Sí" : "No") << std::endl;

    // Vaciar la lista
    std::cout << "Vaciando la lista..." << std::endl;
    lista.vaciar();

    // Verificar el tamaño de la lista después de vaciarla
    std::cout << "Tamaño de la lista después de vaciarla: " << lista.tamaño() << std::endl;

    // Imprimir la lista después de vaciarla
    std::cout << "Lista vacía: ";
    lista.imprimir();

    return 0;
}

