#include <iostream>

#include "../Headers/ListaDoblementeEnlazadaOrdenada.hpp"

int main() {
    ListaDoblementeEnlazadaOrdenada<int> lista;

    for (int i = 10; i > 0; --i) {
        lista.insertar(i);
    }

    std::cout << "Lista en orden: ";
    lista.imprimir();

    std::cout << "Lista en reversa: ";
    lista.imprimirReversa();

    int valor = 5;
    std::cout << "\nBuscando el valor " << valor << " en la lista:" << std::endl;
    if (lista.buscar(valor)) {
        std::cout << "El valor " << valor << " se encuentra en la lista." << std::endl;
    } else {
        std::cout << "El valor " << valor << " no se encuentra en la lista." << std::endl;
    }

    std::cout << "\nEliminando el valor 5 de la lista:" << std::endl;
    lista.eliminarValor(5);
    lista.imprimir();

    std::cout << "\nTamaño de la lista después de la eliminación: " << lista.obtenerTamaño() << std::endl;

    std::cout << "\nVaciando la lista..." << std::endl;
    lista.vaciar();
    std::cout << "Tamaño de la lista después de vaciarla: " << lista.obtenerTamaño() << std::endl;

    return 0;
}

