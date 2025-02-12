#include <iostream>
#include <cmath>
#include "../Headers/Vector.hpp"


using std::cout;
using std::cin;

//Vector::Vector()
//{
//    EstablecerDim(10);
//    for(int i = 0; i < dim; ++i){
//        componente[i] = 0;
//    }
//}
//*****************************************************************************************
//Vector::Vector(int dimension)
//{
//    EstablecerDim(dimension);
//    for(int i = 0; i < dim; ++i){
//        componente[i] = 0;
//    }
//}
//*****************************************************************************************
Vector::Vector(int dimension /* = 1 */, double valor /* = 0*/)
{
    EstablecerDim(dimension);
    try{
        componente = new double[dim];
        for(int i = 0; i < dim; ++i){
        componente[i] = valor;
        }
    }catch (std::bad_alloc &){
    throw "Problemas de asignaci\242n de memoria";
    }
}
//El metodo destructor no tiene tipo de valor devuelto igual que el constructor, se llama igual que la clase pero con un tilde al inicio, representa una negacion, se invoca automaticamente al terminar el ambito del objeto, no recibe parametros, por lo tanto no pueden ser sobrecargados, y sirven para regresar o reestablacer el sistema o los recursos que el constructor asigno
//*****************************************************************************************
Vector::Vector(const Vector &v) : componente(NULL)
{
    *this = v;
}
//*****************************************************************************************
Vector::~Vector()
{
    delete [] componente;
}
//*****************************************************************************************
Vector & Vector::operator=(const Vector &v)
{
    if(this == &v) return *this;
    delete [] componente;
    dim = v.dim;
    try{
        componente = new double[dim];
        for(int i = 0; i < dim; ++i){
        componente[i] = v.componente[i];
        }
    }catch (std::bad_alloc &){
    throw "Problemas de asignaci\242n de memoria";
    }
    return *this;
}


//*****************************************************************************************
void Vector::Imprimir() const
{
    cout << "(";
    for(int i = 0; i < dim; ++i){
        cout << componente[i] << ", ";
    }
    cout << "\b\b)";
}
//*****************************************************************************************
void Vector::Capturar()
{
    for(int i = 0; i < dim; ++i){
        cout << "componente " << i+1 << ": ";
        cin >> componente[i];
    }
}
//*******************************************************************************************
int Vector::ObtenerDim() const
{
    return dim;
}


//*****************************************************************************************
Vector Vector::operator+(const Vector v) const
{
    if(dim != v.dim) throw "Vectores incompatibles para la suma";
    Vector s(dim);
    for(int i = 0; i < dim; ++i){
        s.componente[i] = componente[i] + v.componente[i];
    }
    return s;
}
//*****************************************************************************************
Vector Vector::operator-(const Vector v) const
{
  if(dim != v.dim) throw "Vectores incompatibles para la resta";
  Vector r(dim);
  for(int i = 0; i < dim; ++i){
    r.componente[i] = componente[i] - v.componente[i];
  }
  return r;
}
//*****************************************************************************************
int Vector::operator*(const Vector v) const
{
   if(dim != v.dim) throw "Vectores incompatibles para realizar el producto punto";
   int resultado = 0;
   for(int i = 0; i < dim; ++i){
    resultado = resultado + (componente[i] * v.componente[i]);
  }
  return resultado;
}
//*****************************************************************************************
Vector Vector::operator*(double esc) const
{
  Vector res(dim);
  for(int i = 0; i < dim; ++i){
    res.componente[i] = esc * componente[i];
  }
  return res;
}
//*****************************************************************************************
double Vector::Norma(Vector v) const
{
  double nor = 0;
  for(int i = 0; i < dim; ++i){
    nor = nor + (v.componente[i] * v.componente[i]);
  }
  nor = sqrt(nor);
  return nor;
}
//*******************************************************************************************

double Vector::operator[](int i) const
{
    if(i < 0 || i >= dim) throw "\326ndice inv\240lido";
        return componente[i];
}
//*******************************************************************************************

double & Vector::operator[](int i)
{
        if(i < 0 || i >= dim) throw "\326ndice inv\240lido";
        return componente[i];
}
//*******************************************************************************************
// Métodos externos de la clase
//*******************************************************************************************
Vector operator*(double escalar, const Vector v)
{
    Vector r(v.ObtenerDim());
    for(int i = 0; i < v.ObtenerDim(); ++i){
        r.componente[i] = v.componente[i] * escalar;
    }
    return r;
}
//*******************************************************************************************









//*******************************************************************************************
//Métodos de utileria
//*******************************************************************************************
void Vector::EstablecerDim(int dimension)
{
    if(dimension < 1){
        throw "Dimensi\242n inv\240lida";
    }
    dim = dimension;
}
//*******************************************************************************************

std::ostream & operator<<(std::ostream &salida, const Vector v)
{
    salida << "(";
    for(int i = 0; i < v.dim; ++i){
        salida << v.componente[i] << ", ";
    }
    salida << "\b\b)";
    return salida;
}
//*******************************************************************************************

std::istream & operator>>(std::istream &entrada, Vector &v)
{
    for(int i = 0; i < v.dim; ++i){
        cout << "componente " << i+1 << ": ";
        entrada >> v.componente[i];
    }
    return entrada;
}
