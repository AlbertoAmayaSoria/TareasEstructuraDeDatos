#include <cstdlib>
//#include <ctime>

#include "../Headers/ListaDoblementeEnlazadaOrdenada.hpp"

int main()
{
    ListaDoblementeEnlazadaOrdenada<int> lista;
    
    for(int i = 10 ; i > 0 ; --i)
    {
        lista.insertar(i);
    }
    lista.imprimir();

    return 0;
}


