#include <iostream>
#include "../Headers/Heap.hpp"

int main() {
    // Crear un Heap mínimo (por default)
    Heap<int> minHeap;

    std::cout << "Probando Heap Mínimo:" << std::endl;
    minHeap.Agregar(8);
    minHeap.Agregar(3);
    minHeap.Agregar(5);
    minHeap.Agregar(1);
    minHeap.Agregar(7);

    minHeap.Imprimir();

    std::cout << "Extrayendo elementos ordenados:" << std::endl;
    while (!minHeap.EstaVacio()) {
        std::cout << minHeap.ObtenerFrente() << " ";
        minHeap.Eliminar();
    }
    std::cout << std::endl;

    // Crear un Heap máximo
    Heap<int> maxHeap(maximo<int>);

    std::cout << "\nProbando Heap Máximo:" << std::endl;
    maxHeap.Agregar(8);
    maxHeap.Agregar(3);
    maxHeap.Agregar(5);
    maxHeap.Agregar(1);
    maxHeap.Agregar(7);

    maxHeap.Imprimir();

    std::cout << "Extrayendo elementos ordenados:" << std::endl;
    while (!maxHeap.EstaVacio()) {
        std::cout << maxHeap.ObtenerFrente() << " ";
        maxHeap.Eliminar();
    }
    std::cout << std::endl;

    return 0;
}
