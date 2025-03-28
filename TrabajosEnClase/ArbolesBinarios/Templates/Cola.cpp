/**
*   \file   LinkedQueue.tpp
*   \author Angel Fernando Borquez Guerrero
*   \author Javier Leonardo Miranda Sanchez
*   \date   03/02/2025
*/

#include "../Headers/Cola.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// template <typename T>
// --------------------------------------------
//
// ----- Constructores ------------------------
//
// --------------------------------------------
template <typename Type>
Queue<Type>::Queue() : size(0), frontElement(NULL), rearElement(NULL) {  }

template <typename Type>
Queue<Type>::Queue(const Queue &s) : size(0), frontElement(NULL), rearElement(NULL)
{
    *this = s;
}

template<typename Type>
Queue<Type> & Queue<Type>::operator=(const Queue<Type> &s)
{
    if(this == &s) return *this;

    ClearQueue();

    if(!s.IsEmpty())
    {
        Push(s.Front());

        Element *aux = frontElement;
        Element *aux2 = s.frontElement -> nextElement;

        while (aux2 != nullptr)
        {
            aux -> nextElement = new Element;
            aux -> nextElement -> value = aux2 -> value;
            aux = aux -> nextElement;
            aux2 = aux2 -> nextElement;
        }
    }

    size = s.size;
    return *this;
}
// ----------------------
// ----- Destructor -----
// ----------------------
template<typename Type>
Queue<Type>::~Queue()
{
    ClearQueue();
}



// --------------------------------------------



// --------------------------------------------
//
// ----- Métodos públicos ---------------------
//
// --------------------------------------------
template<typename Type>
void Queue<Type>::Enqueue(Type val)
{
    Element *newElement = new Element;
    newElement -> value = val;
    newElement -> nextElement = NULL;

    if(IsEmpty())
    {
        frontElement = newElement;
    }
    else
    {
        rearElement -> nextElement = newElement;
    }

        rearElement = newElement;

    ++size;
}

template<typename Type>
void Queue<Type>::Dequeue()
{
    if(IsEmpty()) throw "Fila vac\241";

    Element *deleteElement = frontElement;
    frontElement = frontElement -> nextElement;
    delete deleteElement;

    --size;
}

template<typename Type>
Type Queue<Type>::Front() const
{
    if(IsEmpty()) throw "Fila vac\241a";

    return frontElement -> value;
}

template<typename Type>
Type Queue<Type>::Rear() const
{
    if(IsEmpty()) throw "Fila vac\241a";

    return rearElement -> value;
}

template<typename Type>
bool Queue<Type>::IsEmpty() const
{
    return !size;
}

template<typename Type>
void Queue<Type>::ClearQueue()
{
    while(!IsEmpty()) Dequeue();
}

template<typename Type>
unsigned Queue<Type>::QueueSize() const
{
    return size;
}

template<typename Type>
void Queue<Type>::PrintElements()
{
    Element *auxElement = frontElement;

    for(unsigned i = 0; i < size; ++i)
    {
        cout << "| " << auxElement -> value << " ";

        auxElement = auxElement -> nextElement;
    }

    cout << "|";
}



// --------------------------------------------



// --------------------------------------------
//
// ----- Métodos privados ---------------------
//
// --------------------------------------------




// --------------------------------------------



// --------------------------------------------
//
// ----- Métodos de utilería ------------------
//
// ------------------------------------------




// --------------------------------------------



// --------------------------------------------
//
// ----- Métodos externos ---------------------
//
//---------------------------------------------
template<typename Type>
std::ostream & operator<<(std::ostream &output, Queue<Type> &s)
{
    for(unsigned i = 0; i < s.UsedCapacity(); ++i)
    {
        cout << s[i] << endl;
    }

    return output;
}

/*
std::istream & operator>>(std::istream &input, Queue &s)
{

}
*/
