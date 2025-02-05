#include <iostream>
#include <limits>

#include "../Headers/Matriz.h"

using namespace std;

int CapturaSegura();

int main() {

    try {
        int filas, columnas, NuevaFila, NuevaColumna;

        do{
        // Solicita al usuario las dimensiones de la primera matriz
        cout << "Ingrese el número de renglones para la matriz 1: ";
        filas = CapturaSegura();
        }while(filas < 1);
        do{
        cout << "Ingrese el número de columnas para la matriz 1: ";
        columnas = CapturaSegura();
        }while(columnas < 1);

        // Crea la matriz con las dimensiones ingresadas
        Matriz mat1(filas, columnas);

        // Solicita al usuario los valores de la primera matriz
        cout << "Ingrese los elementos de la matriz 1:" << endl;
        cin >> mat1;

        do{
        // Solicita al usuario las dimensiones de la segunda matriz
        cout << "Ingrese el número de renglones para la matriz 2: ";
        filas = CapturaSegura();
        }while(filas < 1);
        do{
        cout << "Ingrese el número de columnas para la matriz 2: ";
        columnas = CapturaSegura();
        }while(columnas < 1);

        // Crea la segunda matriz
        Matriz mat2(filas, columnas);

        // Solicita al usuario los valores de la segunda matriz
        cout << "Ingrese los elementos de la matriz 2:" << endl;
        cin >> mat2;

        cout << endl;

        // Muestra la matriz 1
        cout << "Matriz 1:" << endl;
        cout << mat1 << endl;

        // Muestra la matriz 2
        cout << "Matriz 2:" << endl;
        cout << mat2 << endl;

        // Realiza la suma de las matrices ingresadas
        Matriz suma = mat1 + mat2;
        cout << "Suma de las matrices:" << endl;
        cout << suma << endl;

        // Realiza la resta de las matrices ingresadas
        Matriz resta = mat1 - mat2;
        cout << "Resta de las matrices:" << endl;
        cout << resta << endl;

        // Realiza la multiplicación de las matrices ingresadas
        Matriz producto = mat1 * mat2;
        cout << "Producto de las matrices:" << endl;
        cout << producto << endl;

        // Realiza el producto escalar de la matriz 1 por 2
        Matriz producto_escalar = mat1 * 2;
        cout << "Producto de la matriz 1 por 2:" << endl;
        cout << producto_escalar << endl;

        // Realiza la matriz transpuesta de la matriz 1
        Matriz trans = mat1.transpuesta();
        cout << "Transpuesta de la matriz 1:" << endl;
        cout << trans << endl;

        // Solicita al usuario las nuevas dimensiones para redimensionar la matriz 1
        do {
            cout << "Ingresa el nuevo número de columnas de la matriz 1: ";
            NuevaColumna = CapturaSegura();
        } while (NuevaColumna < 1);

        do {
            cout << "Ingresa el nuevo número de filas de la matriz 1: ";
            NuevaFila = CapturaSegura();
        } while (NuevaFila < 1);

        // Redimensiona la matriz 1
        Matriz red = mat1.redimensionar(NuevaFila, NuevaColumna);
        cout << "Matriz 1 redimensionada a " << NuevaFila << "x" << NuevaColumna << ":" << endl;
        cout << red << endl;

        // Calcula y muestra la inversa de la matriz 1 (si es cuadrada)
        if (mat1.getRenglones() == mat1.getColumnas()) {  // Verifica que la matriz sea cuadrada
            try {
                Matriz inversa = mat1.inversa();
                cout << "Inversa de la matriz 1:" << endl;
                cout << inversa << endl;
            } catch (const std::exception& e) {
                cout << "No se puede calcular la inversa: " << e.what() << endl;
            }
        } else {
            cout << "La matriz 1 no es cuadrada, por lo cual no tiene inversa." << endl;
        }

    } catch (const std::exception& e) {  // Captura cualquier excepción que pueda ocurrir en el programa
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}


int CapturaSegura()
{
    int dato;
    cin >> dato;
    
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        cout << "\nIngresa una respuesta v\240lida.\n - ";
        cin >> dato;
    }

    return dato;

}

