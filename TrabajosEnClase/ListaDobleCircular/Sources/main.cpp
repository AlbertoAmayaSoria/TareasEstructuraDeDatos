#include <iostream>
#include "../Headers/ListaDobleCircular.hpp"

int main()
{
    ListaDobleCircular<int> lista;

    std::cout << "Insertando elementos en la lista..." << std::endl;
    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);
    lista.insertar(50);

    std::cout << "Lista hacia adelante: ";
    lista.imprimirAdelante();

    std::cout << "Lista hacia atrás: ";
    lista.imprimirReversa();

    int buscar = 30;
    if (lista.buscar(buscar)) {
        std::cout << "El valor " << buscar << " está en la lista." << std::endl;
    } else {
        std::cout << "El valor " << buscar << " no está en la lista." << std::endl;
    }

    buscar = 100;
    if (lista.buscar(buscar)) {
        std::cout << "El valor " << buscar << " está en la lista." << std::endl;
    } else {
        std::cout << "El valor " << buscar << " no está en la lista." << std::endl;
    }

    std::cout << "Avanzando la cabeza..." << std::endl;
    lista.avanzarCabeza();
    std::cout << "La cabeza de la lista ahora tiene el valor: ";
    lista.imprimirAdelante();

    std::cout << "Retrocediendo la cabeza..." << std::endl;
    lista.retrocederCabeza();
    std::cout << "La cabeza de la lista ahora tiene el valor: ";
    lista.imprimirAdelante();

    std::cout << "Tamaño de la lista: " << lista.obtenerTamaño() << std::endl;

    std::cout << "Eliminando el primer elemento (cabeza)..." << std::endl;
    lista.eliminar();
    std::cout << "Lista después de eliminar la cabeza: ";
    lista.imprimirAdelante();

    std::cout << "Vaciando la lista..." << std::endl;
    lista.vaciar();
    std::cout << "La lista está vacía: ";
    lista.imprimirAdelante();

    return 0;
}

