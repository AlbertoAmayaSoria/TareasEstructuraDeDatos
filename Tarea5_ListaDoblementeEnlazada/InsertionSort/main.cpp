#include <iostream>
using namespace std;

int main(){
    // Lista desordenada
    int unsorted[] = {9,8,7,6,5,4,3,3,2,1};
    
    // Tamaño de la lista
    int size_unsorted = sizeof(unsorted) / sizeof(unsorted[0]); 

    // Imprimir la lista desordenada
    cout << "\nUnsorted: ";
    for(int i = 0 ; i < size_unsorted ; i++){
        cout << unsorted[i] << " ";
    } 

    int current_element, j;

    // Algoritmo de Insertion Sort
    for(int i = 1; i < size_unsorted; i++){        
        current_element = unsorted[i]; 
        j = i - 1;

        // Desplazar elementos mayores hacia la derecha
        while (j >= 0 && unsorted[j] > current_element) {
            unsorted[j+1] = unsorted[j];
            j--;
        }
        // Insertar el elemento en su posición correcta
        unsorted[j+1] = current_element;
    }

    // Imprimir la lista ordenada
    cout << "\nSorted: ";
    for(int i = 0 ; i < size_unsorted ; i++){
        cout << unsorted[i] << " ";
    } 

    return 0;
}

