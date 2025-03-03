#include <iostream>
#include "../Headers/ListaDoblementeEnlazada.hpp"

bool condicionEliminar(int valor) {
    return valor % 2 == 0;  // Ejemplo: eliminar números pares
}

int main() {
    ListaDoblementeEnlazada<int> lista;

    // Insertar elementos
    std::cout << "Insertando elementos al inicio:" << std::endl;
    lista.insertarInicio(5);
    lista.insertarInicio(20);
    lista.insertarInicio(30);
    lista.imprimir(); // Imprime la lista

    std::cout << "Insertando elementos al final:" << std::endl;
    lista.insertarFinal(40);
    lista.insertarFinal(50);
    lista.imprimir(); // Imprime la lista

    std::cout << "Insertando en una posición específica:" << std::endl;
    lista.insertarPosicion(25, 4);  // Insertar 25 en la posición 4
    lista.imprimir(); // Imprime la lista

    // Modificar un valor
    std::cout << "Modificando el valor en la posición 2:" << std::endl;
    lista.modificarEnPosicion(2, 100);
    lista.imprimir(); // Imprime la lista

    // Eliminar elementos
    std::cout << "Eliminando el primer elemento:" << std::endl;
    lista.eliminarInicio();
    lista.imprimir(); // Imprime la lista

    std::cout << "Eliminando el último elemento:" << std::endl;
    lista.eliminarFinal();
    lista.imprimir(); // Imprime la lista

    std::cout << "Eliminando el valor 25:" << std::endl;
    lista.eliminarValor(25);
    lista.imprimir(); // Imprime la lista

    std::cout << "Eliminando todas las ocurrencias de 100:" << std::endl;
    lista.eliminarTodasOcurrencias(100);
    lista.imprimir(); // Imprime la lista

    // Buscar un valor
    std::cout << "Buscando el valor 40:" << std::endl;
    if (lista.buscar(40)) {
        std::cout << "Valor encontrado." << std::endl;
    } else {
        std::cout << "Valor no encontrado." << std::endl;
    }

    // Eliminar por condición (eliminar números pares)
    std::cout << "Eliminando números pares:" << std::endl;
    lista.eliminarPorCondicion(condicionEliminar);
    lista.imprimir(); // Imprime la lista

    // Eliminar elementos repetidos (no hay, pero sirve para probar)
    std::cout << "Eliminando elementos repetidos:" << std::endl;
    lista.insertarFinal(10);
    lista.insertarFinal(10);  // Insertamos un duplicado
    lista.eliminarElementosRepetidos();
    lista.imprimir(); // Imprime la lista

    // Obtener elementos
    std::cout << "El primer elemento es: " << lista.obtenerPrimero() << std::endl;
    std::cout << "El último elemento es: " << lista.obtenerUltimo() << std::endl;

    // Obtener el tamaño de la lista
    std::cout << "El tamaño de la lista es: " << lista.obtenerTamaño() << std::endl;

    // Vaciar la lista
    std::cout << "Vaciando la lista..." << std::endl;
    lista.vaciar();
    lista.imprimir(); // Imprime la lista vacía

    return 0;
}

