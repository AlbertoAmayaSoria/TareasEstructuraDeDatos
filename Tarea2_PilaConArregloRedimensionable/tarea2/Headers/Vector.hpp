#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED


/**
 * \file Vector.hpp
 * \brief Definición de la clase Vector para operaciones algebraicas.
 * 
 * Esta clase representa un vector algebraico y permite realizar operaciones 
 * como suma, resta, producto escalar y multiplicación por un escalar.
 * También proporciona métodos para la captura e impresión de datos.
 * 
 * \author Amaya Soria Angel Alberto
 * \author Altamirano Ocejo Michell Berenice 
 * \date 01/02/2025
 */

#include <iostream>

/**
 * \class Vector
 * \brief Clase para la manipulación de vectores algebraicos.
 * 
 * Implementa operaciones básicas como suma, resta, producto escalar y 
 * multiplicación por un escalar, además de métodos para la impresión y captura de datos.
 */
class Vector {
    /**
     * \brief Sobrecarga del operador de multiplicación por un escalar.
     * 
     * Permite multiplicar un escalar por un vector, devolviendo un nuevo vector escalado.
     * \param escalar Valor escalar por el que se multiplica el vector.
     * \param v Vector a multiplicar.
     * \return Vector resultante de la multiplicación.
     */
    friend Vector operator*(double escalar, const Vector v);

    /**
     * \brief Sobrecarga del operador de salida.
     * 
     * Permite imprimir un vector en un flujo de salida.
     * \param salida Flujo de salida.
     * \param v Vector a imprimir.
     * \return Referencia al flujo de salida.
     */
    friend std::ostream &operator<<(std::ostream &salida, const Vector v);

    /**
     * \brief Sobrecarga del operador de entrada.
     * 
     * Permite capturar un vector desde un flujo de entrada.
     * \param entrada Flujo de entrada.
     * \param v Vector donde se almacenarán los valores ingresados.
     * \return Referencia al flujo de entrada.
     */
    friend std::istream &operator>>(std::istream &entrada, Vector &v);

public:
    /** 
     * \brief Constructor con valores predeterminados.
     * 
     * Crea un vector de la dimensión especificada con todos sus componentes inicializados 
     * a un valor determinado.
     * \param dimension Número de componentes del vector (mínimo 1).
     * \param valor Valor inicial para todas las componentes del vector (por defecto 0).
     */
    explicit Vector(int dimension = 1, double valor = 0);

    /** 
     * \brief Constructor de copia.
     * 
     * Crea una copia exacta de otro vector.
     * \param v Vector a copiar.
     */
    Vector(const Vector &v);

    /** 
     * \brief Destructor de la clase Vector.
     * 
     * Libera la memoria dinámica utilizada para almacenar las componentes del vector.
     */
    ~Vector();

    /** 
     * \brief Sobrecarga del operador de asignación.
     * 
     * Copia el contenido de un vector en otro, asegurando una correcta gestión de memoria.
     * \param v Vector a asignar.
     * \return Referencia al vector actual tras la asignación.
     */
    Vector &operator=(const Vector &v);

    /** 
     * \brief Obtiene la dimensión del vector.
     * \return Número de componentes del vector.
     */
    int ObtenerDim() const;

    /** 
     * \brief Imprime el vector en consola.
     */
    void Imprimir() const;

    /** 
     * \brief Captura los valores del vector desde la entrada estándar.
     */
    void Capturar();

    /** 
     * \brief Sobrecarga del operador de suma.
     * 
     * Realiza la suma de dos vectores del mismo tamaño.
     * \param v Vector a sumar.
     * \return Vector resultante de la suma.
     */
    Vector operator+(const Vector v) const;

    /** 
     * \brief Sobrecarga del operador de resta.
     * 
     * Realiza la resta de dos vectores del mismo tamaño.
     * \param v Vector a restar.
     * \return Vector resultante de la resta.
     */
    Vector operator-(const Vector v) const;

    /** 
     * \brief Sobrecarga del operador de producto escalar.
     * 
     * Calcula el producto escalar entre dos vectores.
     * \param v Vector con el que se realizará el producto escalar.
     * \return Resultado del producto escalar.
     */
    int operator*(const Vector v) const;

    /** 
     * \brief Sobrecarga del operador de multiplicación por un escalar.
     * 
     * Multiplica el vector por un escalar.
     * \param esc Valor escalar.
     * \return Vector resultante de la multiplicación.
     */
    Vector operator*(double esc) const;

    /** 
     * \brief Calcula la norma del vector.
     * 
     * \param v Vector del que se calculará la norma.
     * \return Valor de la norma del vector.
     */
    double Norma(Vector v) const;

    /** 
     * \brief Sobrecarga del operador de acceso por índice (lectura).
     * 
     * Permite acceder a los elementos del vector de manera segura.
     * \param i Índice del elemento a obtener.
     * \return Valor del componente en la posición i.
     */
    double operator[](int i) const;

    /** 
     * \brief Sobrecarga del operador de acceso por índice (modificación).
     * 
     * Permite modificar los elementos del vector de manera segura.
     * \param i Índice del elemento a modificar.
     * \return Referencia al componente en la posición i.
     */
    double &operator[](int i);

private:
    int dim;            ///< Dimensión del vector (número de componentes).
    double *componente; ///< Arreglo dinámico que almacena los valores del vector.

    /** 
     * \brief Establece la dimensión del vector.
     * 
     * Asigna memoria para almacenar los componentes del vector.
     * \param dimension Nueva dimensión del vector.
     */
    void EstablecerDim(int dimension);
};



#endif // VECTOR_HPP_INCLUDED
