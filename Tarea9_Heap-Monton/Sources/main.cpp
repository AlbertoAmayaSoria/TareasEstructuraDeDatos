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
    maxHeap.Agregar(0);

    maxHeap.ImprimirElem();



    // Imprimir elementos del heap
    /*maxHeap.ImprimirElem();  // Deberías ver: 30 20 10 5 15

    // Obtener el frente (el valor más grande)
    std::cout << "El valor en el frente es: " << maxHeap.ObtenerFrente() << std::endl;

    // Eliminar el elemento en el frente (el más grande)
    maxHeap.Eliminar();
    std::cout << "Después de eliminar el frente (30):" << std::endl;
    maxHeap.ImprimirElem();  // Deberías ver: 20 15 10 5

    // Obtener el nuevo frente
    std::cout << "El nuevo valor en el frente es: " << maxHeap.ObtenerFrente() << std::endl;

    // Agregar más elementos
    maxHeap.Agregar(25);
    maxHeap.Agregar(35);

    // Imprimir después de agregar más elementos
    std::cout << "Después de agregar más elementos:" << std::endl;
    maxHeap.ImprimirElem();  // Deberías ver: 35 25 20 5 15 10

    // Eliminar hasta que el heap esté vacío
    while (!maxHeap.EstaVacia()) {
        std::cout << "Eliminando el frente: " << maxHeap.ObtenerFrente() << std::endl;
        maxHeap.Eliminar();
    }

    // Verificar que el heap está vacío
    if (maxHeap.EstaVacia()) {
        std::cout << "El heap está vacío." << std::endl;
    }*/

    return 0;
}

