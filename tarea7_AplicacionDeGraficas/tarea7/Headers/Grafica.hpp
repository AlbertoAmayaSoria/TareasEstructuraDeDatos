/**
 * @file Grafica.hpp
 * @brief Definición de la clase Grafica para representar un grafo.
 */

#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

#include "Nodo.hpp"
#include <map>

/**
 * @class Grafica
 * @brief Representa una estructura de datos para un grafo no dirigido.
 */
class Grafica {
public:
    /**
     * @brief Constructor por defecto.
     */
    Grafica();
    
    /**
     * @brief Constructor de copia.
     * @param g Referencia al objeto Grafica a copiar.
     */
    Grafica(const Grafica &g);
    
    /**
     * @brief Destructor de la gráfica.
     */
    ~Grafica();
    
    /**
     * @brief Sobrecarga del operador de asignación.
     * @param g Referencia al objeto Grafica a asignar.
     * @return Referencia a la instancia actual.
     */
    Grafica & operator=(const Grafica &g);

    /**
     * @brief Agrega un nodo a la gráfica.
     * @param nom Nombre del nodo a agregar.
     */
    void Agregar(char nom);
    
    /**
     * @brief Agrega una arista entre dos nodos existentes.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     */
    void Agregar(char nomInicial, char nomFinal);

    /**
     * @brief Elimina un nodo de la gráfica.
     * @param nom Nombre del nodo a eliminar.
     */
    void Eliminar(char nom);
    
    /**
     * @brief Elimina una arista entre dos nodos.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     */
    void Eliminar(char nomInicial, char nomFinal);

    /**
     * @brief Obtiene el número de nodos en la gráfica.
     * @return Cantidad de nodos en la gráfica.
     */
    int ObtenerNumNodos() const;
    
    /**
     * @brief Obtiene el número de aristas en la gráfica.
     * @return Cantidad de aristas en la gráfica.
     */
    int ObtenerNumAristas() const;
    
    /**
     * @brief Obtiene el grado de un nodo.
     * @param nom Nombre del nodo.
     * @return Grado del nodo.
     * @throws Excepción si el nodo no existe.
     */
    int ObtenerGrado(char nom) const;

    /**
     * @brief Verifica si un nodo existe en la gráfica.
     * @param nom Nombre del nodo.
     * @return true si el nodo existe, false en caso contrario.
     */
    bool Buscar(char nom) const;
    
    /**
     * @brief Verifica si una arista existe entre dos nodos.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     * @return true si la arista existe, false en caso contrario.
     */
    bool Buscar(char nomInicial, char nomFinal) const;

    /**
     * @brief Imprime la representación de la gráfica.
     */
    void Imprimir() const;

    /**
     * @brief Vacía todas las aristas de un nodo.
     * @param nom Nombre del nodo a vaciar.
     */
    void Vaciar(char nom);
    
    /**
     * @brief Vacía completamente la gráfica, eliminando todos los nodos y aristas.
     */
    void Vaciar();

    /**
     * @brief Verifica si la gráfica es conexa.
     * @return true si la gráfica es conexa, false en caso contrario.
     */
    bool EsConexa() const;
    
    /**
     * @brief Verifica si todos los nodos tienen grado par.
     * @return true si todos los nodos tienen grado par, false en caso contrario.
     */
    bool TieneGradoPar() const;

    /**
     * @brief Realiza una búsqueda en profundidad (DFS) en la gráfica.
     * @param nodo Nodo inicial para la búsqueda.
     * @param visitado Mapa que registra los nodos visitados.
     */
    void DFS(Nodo* nodo, std::map<char, bool>& visitado) const;

    /**
     * @brief Encuentra un camino euleriano en la gráfica, si existe.
     */
    void CaminoEuleriano();

private:
    Nodo *primero, *ultimo; ///< Punteros al primer y último nodo de la gráfica.
    int numNodos, numAristas; ///< Contadores de nodos y aristas.

    /**
     * @brief Busca la dirección de un nodo en la gráfica.
     * @param nom Nombre del nodo a buscar.
     * @param ant Puntero al nodo anterior (opcional).
     * @return Puntero al nodo encontrado o nullptr si no existe.
     */
    Nodo *BuscarDireccion(char nom, Nodo **ant = NULL) const;
};

#endif // GRAFICA_HPP_INCLUDED

