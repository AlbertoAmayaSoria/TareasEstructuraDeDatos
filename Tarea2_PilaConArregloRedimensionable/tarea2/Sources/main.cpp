/*
 * \autor Amaya Soria Angel Alberto
 * \autor Altamirano Ocejo Michell Berenice 
 * \descripción: Programa de pilas, mediante el cual puedes crear una pila, anadir y quitar elementos, vaciar la pila.
 *              En general permite trabajar con pilas de diferentes tipos de datos
 * \Fecha: 02/02/2025
 */

#include <iostream>
#include <string>
#include <complex>
#include "../Headers/Pila.hpp"
#include "../Headers/Vector.hpp"

using namespace std;

int main()
{
    try {
        // Crear una pila de vectores con capacidad 5 por default
        Pila<Vector> pilaVector;

        // Comprobar si la pila est\241 vac\242\240
        if(pilaVector.EstaVacia())  
            cout << "La pila est\241 vac\242a\n";
        else                        
            cout << "La pila no est\241 vac\242a\n";

        // Apilar un objeto Vector
        pilaVector.Apilar(Vector(2,1.5));
        cout << "Capacidad pila Vector: " << pilaVector.CapacidadPila() << endl;
        pilaVector.Imprimir();
        pilaVector.Apilar(Vector(2,1.5));
        pilaVector.Apilar(Vector(2,1.5));
        pilaVector.Apilar(Vector(2,1.5));
        pilaVector.Apilar(Vector(2,1.5));
        pilaVector.Apilar(Vector(2,1.5));
        cout << "Capacidad pila Vector: " << pilaVector.CapacidadPila() << endl;
        pilaVector.Imprimir();

        // Crear otra pila de vectores con capacidad 5
        Pila<Vector> otraPilaVec;
        otraPilaVec = pilaVector; // Operador de asignacion (usara redimensionamiento si es necesario)
        cout << "Esta es otra pila vector: " << endl;
        otraPilaVec.Imprimir();

        // Desapilar un elemento
        pilaVector.Desapilar();
        
        cout << endl;
        cout << "Pila 1: " << endl;
        // Imprimir ambas pilas
        pilaVector.Imprimir();
        cout << "Pila 2: " << endl;

        otraPilaVec.Imprimir();
        cout << endl;
        pilaVector.Vaciar();
        pilaVector.Imprimir();

        // Comprobar si la pila esta vacía
        if(pilaVector.EstaVacia())  
            cout << "La pila est\241 vac\242a\n";
        else                        
            cout << "La pila no est\241 vac\242a\n";

        cout << endl;


        cout << "Pilas de enteros: " << endl;
        // Ejemplo comentado con pilas de enteros
        Pila<int> PilaEnteros;
        PilaEnteros.Apilar(1);
        PilaEnteros.Apilar(2); 
        PilaEnteros.Apilar(3);
        PilaEnteros.Imprimir();
        cout << "Capacidad pila: " << PilaEnteros.CapacidadPila() << endl;
        PilaEnteros.Apilar(4);
        PilaEnteros.Apilar(5); 
        PilaEnteros.Apilar(6);
        PilaEnteros.Imprimir();
        cout << "Capacidad pila: "<<PilaEnteros.CapacidadPila() << endl << endl;
        PilaEnteros.Desapilar();
        PilaEnteros.Imprimir();
        cout << "Capacidad pila: "<<PilaEnteros.CapacidadPila() << endl << endl;
        PilaEnteros.Vaciar();
        PilaEnteros.Imprimir();
        // Comprobar si la pila esta vacía
        if(PilaEnteros.EstaVacia())  
            cout << "La pila est\241 vac\242a\n";
        else                        
            cout << "La pila no est\241 vac\242a\n";

        cout << endl;

        cout << "Pila de numeros complejos: " << endl;
        Pila<complex<double>> PilaComplejos;
        PilaComplejos.Apilar(complex<double>(3.0,4.0));
        PilaComplejos.Apilar(complex<double>(1.0,-2.0));
        PilaComplejos.Apilar(complex<double>(2.0,4.0));
        PilaComplejos.Apilar(complex<double>(4.0,-2.0)); 
        PilaComplejos.Apilar(complex<double>(5.0,4.0));
        PilaComplejos.Apilar(complex<double>(6.0,-2.0)); 
        PilaComplejos.Imprimir();
        cout << endl;
        PilaComplejos.Desapilar();
        PilaComplejos.Desapilar();
        PilaComplejos.Imprimir();
        cout << "Capacidad pila: " << PilaEnteros.CapacidadPila() << endl << endl;
        PilaComplejos.Vaciar();
        PilaComplejos.Imprimir();

        // Comprobar si la pila esta vacía
        if(PilaComplejos.EstaVacia())  
            cout << "La pila est\241 vac\242a\n";
        else                        
            cout << "La pila no est\241 vac\242a\n";

        
    } catch (const char* mensaje) {
        cerr << "Error: " << mensaje << endl;
    }

    return 0;
}

