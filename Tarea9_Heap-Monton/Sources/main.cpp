#include <iostream>
#include "../Headers/Heap.hpp"

int main() {
    // Crear un Max-Heap de enteros
    Heap<int, true> maxHeap;
    Heap<int, false> minHeap;

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

    return 0;
}

