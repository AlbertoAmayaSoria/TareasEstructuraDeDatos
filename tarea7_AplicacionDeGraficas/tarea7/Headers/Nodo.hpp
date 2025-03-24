/**
 * @file Nodo.hpp
 * @brief Definición de la estructura Nodo para representar un vértice en una gráfica.
 */

#ifndef NODO_HPP_INCLUDED
#define NODO_HPP_INCLUDED

#include "../Headers/Arista.hpp"

/**
 * @struct Nodo
 * @brief Representa un nodo en una gráfica.
 */
struct Nodo {
    char nombre;       /**< Nombre del nodo. */
    int grado;         /**< Grado del nodo (cantidad de aristas incidentes). */
    Arista *primera;   /**< Puntero a la primera arista del nodo. */
    Arista *ultima;    /**< Puntero a la última arista del nodo. */
    Nodo *siguiente;   /**< Puntero al siguiente nodo en la lista de nodos. */
    bool visitado;     /**< Indica si el nodo ha sido visitado en recorridos. */

    /**
     * @brief Constructor de la estructura Nodo.
     * @param nom Nombre del nodo.
     * @param sig Puntero al siguiente nodo (por defecto es NULL).
     */
    Nodo(char nom, Nodo *sig = NULL);

    /**
     * @brief Agrega una arista entre este nodo y otro nodo adyacente.
     * @param ady Puntero al nodo adyacente.
     */
    void Agregar(Nodo *ady);

    /**
     * @brief Elimina una arista entre este nodo y otro nodo adyacente.
     * @param ady Puntero al nodo adyacente.
     */
    void Eliminar(Nodo *ady);

    /**
     * @brief Vacía todas las aristas del nodo.
     * @return Número de aristas eliminadas.
     */
    int Vaciar();

    /**
     * @brief Busca si existe una arista entre este nodo y otro nodo adyacente.
     * @param ady Puntero al nodo adyacente.
     * @return true si la arista existe, false en caso contrario.
     */
    bool Buscar(Nodo *ady) const;

    /**
     * @brief Imprime la información del nodo y sus aristas.
     */
    void Imprimir() const;

    /**
     * @brief Busca la dirección de una arista en la lista de adyacencia.
     * @param ady Puntero al nodo adyacente.
     * @param ant Puntero a un puntero que almacenará la dirección de la arista anterior (opcional).
     * @return Puntero a la arista encontrada o NULL si no existe.
     */
    Arista * BuscarDireccion(Nodo *ady, Arista **ant = NULL) const;
};

#endif // NODO_HPP_INCLUDED
