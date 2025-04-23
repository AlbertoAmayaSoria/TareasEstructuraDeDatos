/**
 * \file Vector.hpp
 * Contiene la definici&oacute;n de una clase que representa un vector algebraico
 * \author Oiram Alberto Figueroa Torres
 * \date 24/01/2025
*/


#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include <iostream>

//#define MAX_DIM 10



/**
* Vector es una clase para el manejo de vectores algebraicos
*/
class Vector{
    /** \brief Operador de multiplicacion de escalar por Vector
     *
     * \param escalar   Escalar por el que se multiplica un vector
     * \param v     Vector a multiplicar
     * \return Vector resultante de la multiplicacio&oacute;n
     *
     */

    friend Vector operator*(double escalar, const Vector v);
    friend std::ostream & operator<<(std::ostream &salida, const Vector v);
    friend std::istream & operator>>(std::istream &entrada, Vector &v);
public:

    //Vector();
   // explicit Vector(int dimension); //se vuelve explicito para impedir que un entero se vuelva automaticamente en vector
    explicit Vector(int dimensnion = 1, double valor = 0);
    Vector(const Vector &v);
    ~Vector();
    Vector & operator=(const Vector &v);

    int ObtenerDim() const;


    void Imprimir() const;
    void Capturar();


    Vector operator+(const Vector v) const;
    Vector operator-(const Vector v) const;
    int operator*(const Vector v) const;//*****************
    Vector operator*(double esc) const;
    double Norma(Vector v) const;


    double operator[](int i) const;
    double & operator[](int i);


private:
    int dim;
    double *componente;
    //Métodos de utileria
    void EstablecerDim(int dimension);
};







#endif // VECTOR_HPP_INCLUDED
