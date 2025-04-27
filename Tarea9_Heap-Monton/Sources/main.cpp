#include <iostream>
#include "../Headers/Heap.hpp"

int main() {
    // Crear un Max-Heap de enteros
    Heap<int, true> maxHeap;

    std::cout << "Probando Max-Heap:" << std::endl;

    // Agregar elementos al heap
    maxHeap.Agregar(8);
    maxHeap.Agregar(3);
    maxHeap.Agregar(5);
    maxHeap.Agregar(3);
    maxHeap.Agregar(2);
    maxHeap.Agregar(1);
    maxHeap.Agregar(0);

    maxHeap.ImprimirElem();

    std::cout << "Extrayendo Max-Heap en orden descendente:" << std::endl;
    while (!maxHeap.EstaVacia()) {
        std::cout << maxHeap.ObtenerFrente() << " ";
        maxHeap.Eliminar();
    }
    std::cout << "Intentando eliminar un elemento extra de Max-Heap:" << std::endl;
    maxHeap.Eliminar();
    std::cout << std::endl << std::endl;

    // Crear un Min-Heap de enteros
    Heap<int, false> minHeap;

    std::cout << "Probando Min-Heap:" << std::endl;

    // Agregar elementos al heap
    minHeap.Agregar(8);
    minHeap.Agregar(3);
    minHeap.Agregar(5);
    minHeap.Agregar(3);
    minHeap.Agregar(2);
    minHeap.Agregar(1);
    minHeap.Agregar(0);

    minHeap.ImprimirElem();

    std::cout << "Extrayendo Min-Heap en orden ascendente:" << std::endl;
    while (!minHeap.EstaVacia()) {
        std::cout << minHeap.ObtenerFrente() << " ";
        minHeap.Eliminar();
    }
    std::cout << "Intentando eliminar un elemento extra de Min-Heap:" << std::endl;
    minHeap.Eliminar();
    std::cout << std::endl;

    return 0;
}

