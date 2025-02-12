/*
Descripción: Programa que utiliza la clase Pila para redimensionarla al doble de su capacidad cuando se llena
Autor: Amaya Soria Angel Alberto
Fecha: 04 de Febrero de 2025
*/



#include <iostream>
#include "../Headers/Pila.hpp"

using namespace std;

int main()
{
    try {
        Pila<char> Operadores;
        string Cadena;

        cout << "Ingresa la operación: " << endl;
        getline(cin, Cadena);

        //Hacer el metodo para invocar y verificar la apertura y clausura de operaciones
        /*for(size_t i = 0; i < Cadena.size(); ++i) {
            if(Cadena[i] == '{' || Cadena[i] == '[' || Cadena[i] == '(') {
                Operadores.Apilar(Cadena[i]);
            }

            //Operadores.Imprimir(); //pruebas  de captura

            // !Operadores.EstaVascia() verifica que la pila no esté vacía antes de obtener el tope
            if (!Operadores.EstaVacia() && 
                ((Cadena[i] == ')' && Operadores.ObtenerTope() == '(') ||
                 (Cadena[i] == ']' && Operadores.ObtenerTope() == '[') ||
                 (Cadena[i] == '}' && Operadores.ObtenerTope() == '{'))) 
            {
                Operadores.Desapilar();
            } 
            else if (Cadena[i] == ')' || Cadena[i] == ']' || Cadena[i] == '}') {
                throw "Error: Operaci\242n mal escrita";
            }
        }

        // Validar que no queden paréntesis sin cerrar
        if (!Operadores.EstaVacia()) {
            throw "Error: Operaci\242n mal escrita";
        }

        cout << "Expresión correcta." << endl;*/

    } catch(const char *mensaje) {
        cerr << "\n" << mensaje << endl;
    }

    cout << "Presiona ENTER para continuar...";
    cin.get();
    return 0;
}

