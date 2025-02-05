#ifndef PILA_HPP_INCLUDED
#define PILA_HPP_INCLUDED

/**
 * \file Pila.hpp
 * \brief Definición de la clase plantilla Pila (LIFO).
 * 
 * Esta clase representa una pila genérica de tipo LIFO (Last In, First Out).
 * Permite almacenar elementos de un tipo determinado y proporciona métodos 
 * para agregar, eliminar y consultar elementos, así como verificar su estado.
 * 
 * \author Amaya Soria Angel Alberto
 * \author Altamirano Ocejo Michell Berenice 
 * \date 01/02/2025
 */

#include <iostream>

/**
 * \class Pila
 * \brief Contenedor LIFO de datos con capacidad dinámica.
 * 
 * Esta clase implementa una pila con almacenamiento dinámico y capacidad ajustable.
 * Se redimensiona automáticamente cuando se llena.
 * 
 * \tparam Tipo Tipo de dato a almacenar en la pila.
 */
template <typename Tipo>
class Pila {
public:
    /** 
     * \brief Constructor por defecto. 
     * 
     * Crea una pila vacía con una capacidad inicial predeterminada. 
     */
    Pila(); 

    /** 
     * \brief Constructor de copia.
     * 
     * Crea una nueva pila como copia exacta de otra, incluyendo sus elementos y capacidad.
     * \param p Pila a copiar.
     */
    Pila(const Pila &p);

    /** 
     * \brief Sobrecarga del operador de asignación.
     * 
     * Copia los elementos y la capacidad de una pila a otra, asegurando una gestión 
     * adecuada de la memoria dinámica.
     * \param p Pila a asignar.
     * \return Referencia a la pila actual tras la asignación.
     */
    Pila &operator=(const Pila &p);

    /** 
     * \brief Destructor de la pila.
     * 
     * Libera la memoria dinámica utilizada por la pila.
     */
    ~Pila();

    /** 
     * \brief Agrega un elemento a la pila.
     * 
     * Inserta un nuevo elemento en la parte superior de la pila. 
     * Si la pila está llena, se redimensiona automáticamente.
     * \param valor Elemento a agregar.
     */
    void Apilar(Tipo valor);

    /** 
     * \brief Elimina el elemento en el tope de la pila.
     * 
     * Reduce el tamaño de la pila eliminando el elemento superior.
     * \throw const char* Excepción si la pila está vacía.
     */
    void Desapilar();

    /** 
     * \brief Obtiene el elemento en el tope de la pila sin eliminarlo.
     * 
     * \return Elemento en la cima de la pila.
     * \throw const char* Excepción si la pila está vacía.
     */
    Tipo ObtenerTope() const;

    /** 
     * \brief Verifica si la pila está vacía.
     * 
     * \return true si la pila no tiene elementos, false en caso contrario.
     */
    bool EstaVacia() const; 

    /** 
     * \brief Vacía la pila eliminando todos sus elementos.
     */
    void Vaciar();

    /** 
     * \brief Obtiene la cantidad de elementos en la pila.
     * 
     * \return Número de elementos almacenados en la pila.
     */
    int ElementosPila() const;

    /** 
     * \brief Obtiene la capacidad actual de la pila.
     * 
     * \return Capacidad máxima de la pila antes de necesitar redimensionarse.
     */
    int CapacidadPila() const;

    /** 
     * \brief Imprime los elementos de la pila en orden de inserción.
     */
    void Imprimir() const;

private:
    Tipo *elemento;  /// Puntero dinámico para almacenar los elementos de la pila.
    int tope;        /// Índice del elemento en la cima de la pila.
    int capacidad;   /// Capacidad actual de la pila.

    /** 
     * \brief Redimensiona la pila cuando se llena.
     * 
     * Duplica la capacidad de la pila para permitir más inserciones.
     */
    void Redimensionar(); 

    /** 
     * \brief Verifica si la pila está llena.
     * 
     * \return true si la pila alcanzó su capacidad máxima, false en caso contrario.
     */
    bool EstaLlena() const; 
};


#include "../Templates/Pila.tpp"

#endif // PILA_HPP_INCLUDED
