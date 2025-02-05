#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <stdexcept>

class Matriz {

   double CapturaSeguraM(); 

    // Operadores de flujo
    friend std::istream& operator>>(std::istream& cin, Matriz& mat);
    friend std::ostream& operator<<(std::ostream& cout, const Matriz& mat);

    // Operador no miembro para producto por escalar conmutativo
    friend Matriz operator*(int escalar, const Matriz& mat);

public:
    // Constructor por defecto
    Matriz(unsigned int r = 1, unsigned int c = 1);

    // Destructor
    ~Matriz();

    // Constructor de copia
    Matriz(const Matriz& otra);

    // Operador de asignación
    Matriz& operator=(const Matriz& otra);

    // Operadores para:
    Matriz operator+(const Matriz& otra) const;
    Matriz operator-(const Matriz& otra) const;
    Matriz operator*(const Matriz& otra) const;
    Matriz operator*(int escalar) const;

    // Métodos
    Matriz transpuesta() const;
    Matriz inversa() const;  // Inversa de una matriz cuadrada
    Matriz redimensionar(unsigned int nuevas_renglones, unsigned int nuevas_columnas) const;

    // Métodos para obtener el número de filas y columnas
    unsigned int getRenglones() const { return renglones; }
    unsigned int getColumnas() const { return columnas; }

private:
    // Atributos privados
    unsigned int renglones;  // Número de filas
    unsigned int columnas;   // Número de columnas
    double** datos;          // Datos de la matriz (usando double para precisión)
};



#endif
