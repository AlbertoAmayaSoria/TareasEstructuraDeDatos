#include <iostream>
#include "../Headers/ArbolB.hpp"

/*void imprimirEstado(const ArbolB<int, 5>& arbol, const std::string& mensaje = "") {
    if (!mensaje.empty()) {
        std::cout << "\n--- " << mensaje << " ---\n";
    }
    std::cout << "Elementos: " << arbol.CantElem() << std::endl;
    std::cout << "Ascendente: ";
    arbol.ImprimirAsc();
    std::cout << "Descendente: ";
    arbol.ImprimirDes();
    std::cout << "Por niveles:\n";
    arbol.ImprimirNiveles();
}

void pruebaBusqueda(const ArbolB<int, 5>& arbol, int valor) {
    std::cout << "Buscando " << valor << ": " 
              << (arbol.Buscar(valor) ? "Encontrado" : "No encontrado") 
              << std::endl;
}*/

int main() {
    // Prueba 1: Creación e inserción
    ArbolB<int, 5> arbol;
    for(int i = 1; i <= 5; ++i) {
        arbol.Agregar(i);
    }

    arbol.ImprimirNiveles();
    //imprimirEstado(arbol, "Después de inserciones iniciales");

    // Prueba 2: Búsquedas
    /*pruebaBusqueda(arbol, 5);
    pruebaBusqueda(arbol, 15);

    // Prueba 3: Eliminaciones
    for(int i : {1, 10, 2, 3, 4}) {
        arbol.Eliminar(i);
        imprimirEstado(arbol, "Después de eliminar " + std::to_string(i));
    }*/

    // Prueba 4: Insertar elementos desordenados
    /*for(int i : {15, 12, 18, 11, 13}) {
        arbol.Agregar(i);
    }
    imprimirEstado(arbol, "Después de inserciones adicionales");

    // Prueba 5: Más búsquedas
    pruebaBusqueda(arbol, 12);
    pruebaBusqueda(arbol, 7);

    // Prueba 6: Eliminar elementos no existentes
    std::cout << "\nIntentando eliminar elementos no existentes:\n";
    arbol.Eliminar(100);
    arbol.Eliminar(1);  // Ya fue eliminado antes
    imprimirEstado(arbol, "Después de intentar eliminar elementos no existentes");

    // Prueba 7: Vaciar el árbol
    arbol.Vaciar();
    imprimirEstado(arbol, "Después de vaciar");

    // Prueba 8: Insertar después de vaciar
    arbol.Agregar(100);
    arbol.Agregar(50);
    arbol.Agregar(150);
    imprimirEstado(arbol, "Después de nuevas inserciones en árbol vaciado");*/

    return 0;
}
