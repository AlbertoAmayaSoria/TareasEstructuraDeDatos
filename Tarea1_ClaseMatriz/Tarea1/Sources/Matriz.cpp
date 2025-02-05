#include <iomanip>  // Para std::setw en el operador de salida
#include <limits>

#include "../Headers/Matriz.h"

// Constructor por defecto
Matriz::Matriz(unsigned int r, unsigned int c) : renglones(r), columnas(c) {
    datos = new double*[renglones];
    for (unsigned int i = 0; i < renglones; ++i) {
        datos[i] = new double[columnas]();
    }
}

// Destructor
Matriz::~Matriz() {
    for (unsigned int i = 0; i < renglones; ++i) {
        delete[] datos[i];
    }
    delete[] datos;
}

// Constructor de copia
Matriz::Matriz(const Matriz& otra) : renglones(otra.renglones), columnas(otra.columnas) {
    datos = new double*[renglones];
    for (unsigned int i = 0; i < renglones; ++i) {
        datos[i] = new double[columnas];
        for (unsigned int j = 0; j < columnas; ++j) {
            datos[i][j] = otra.datos[i][j];
        }
    }
}

// Operador de asignación
Matriz& Matriz::operator=(const Matriz& otra) {
    if (this == &otra) return *this;

    for (unsigned int i = 0; i < renglones; ++i) {
        delete[] datos[i];
    }
    delete[] datos;

    renglones = otra.renglones;
    columnas = otra.columnas;
    datos = new double*[renglones];
    for (unsigned int i = 0; i < renglones; ++i) {
        datos[i] = new double[columnas];
        for (unsigned int j = 0; j < columnas; ++j) {
            datos[i][j] = otra.datos[i][j];
        }
    }
    return *this;
}

// Operador de suma
Matriz Matriz::operator+(const Matriz& otra) const {
    if (renglones != otra.renglones || columnas != otra.columnas) {
        throw std::invalid_argument("Las matrices deben tener las mismas dimensiones para sumarlas.");
    }

    Matriz resultado(renglones, columnas);
    for (unsigned int i = 0; i < renglones; ++i) {
        for (unsigned int j = 0; j < columnas; ++j) {
            resultado.datos[i][j] = datos[i][j] + otra.datos[i][j];
        }
    }
    return resultado;
}

// Operador de resta
Matriz Matriz::operator-(const Matriz& otra) const {
    if (renglones != otra.renglones || columnas != otra.columnas) {
        throw std::invalid_argument("Las matrices deben tener las mismas dimensiones para restarlas.");
    }

    Matriz resultado(renglones, columnas);
    for (unsigned int i = 0; i < renglones; ++i) {
        for (unsigned int j = 0; j < columnas; ++j) {
            resultado.datos[i][j] = datos[i][j] - otra.datos[i][j];
        }
    }
    return resultado;
}

// Operador de multiplicación de matrices
Matriz Matriz::operator*(const Matriz& otra) const {
    if (columnas != otra.renglones) {
        throw std::invalid_argument("El número de columnas de la primera matriz debe ser igual al número de filas de la segunda.");
    }

    Matriz resultado(renglones, otra.columnas);
    for (unsigned int i = 0; i < renglones; ++i) {
        for (unsigned int j = 0; j < otra.columnas; ++j) {
            resultado.datos[i][j] = 0;
            for (unsigned int k = 0; k < columnas; ++k) {
                resultado.datos[i][j] += datos[i][k] * otra.datos[k][j];
            }
        }
    }
    return resultado;
}

// Operador de producto por escalar
Matriz Matriz::operator*(int escalar) const {
    Matriz resultado(renglones, columnas);
    for (unsigned int i = 0; i < renglones; ++i) {
        for (unsigned int j = 0; j < columnas; ++j) {
            resultado.datos[i][j] = datos[i][j] * escalar;
        }
    }
    return resultado;
}

// Método para calcular la transpuesta de la matriz
Matriz Matriz::transpuesta() const {
    Matriz resultado(columnas, renglones);
    for (unsigned int i = 0; i < renglones; ++i) {
        for (unsigned int j = 0; j < columnas; ++j) {
            resultado.datos[j][i] = datos[i][j];
        }
    }
    return resultado;
}

// Método para calcular la inversa de una matriz cuadrada
Matriz Matriz::inversa() const {
    if (renglones != columnas) {
        throw std::invalid_argument("Solo las matrices cuadradas tienen inversa.");
    }

    unsigned int n = renglones;
    Matriz A(*this); // Copia de la matriz original
    Matriz I(n, n);  // Matriz identidad

    // Inicializar la identidad
    for (unsigned int i = 0; i < n; ++i) {
        I.datos[i][i] = 1;
    }

    // Aplicar el método de Gauss-Jordan
    for (unsigned int i = 0; i < n; ++i) {
        // Asegurar que el pivote no sea cero
        if (A.datos[i][i] == 0) {
            bool intercambiado = false;
            for (unsigned int k = i + 1; k < n; ++k) {
                if (A.datos[k][i] != 0) {
                    std::swap(A.datos[i], A.datos[k]);
                    std::swap(I.datos[i], I.datos[k]);
                    intercambiado = true;
                    break;
                }
            }
            if (!intercambiado) {
                throw std::runtime_error("La matriz es singular y no tiene inversa.");
            }
        }

        // Hacer el pivote igual a 1
        double pivote = A.datos[i][i];
        for (unsigned int j = 0; j < n; ++j) {
            A.datos[i][j] /= pivote;
            I.datos[i][j] /= pivote;
        }

        // Hacer ceros en la columna
        for (unsigned int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = A.datos[k][i];
                for (unsigned int j = 0; j < n; ++j) {
                    A.datos[k][j] -= factor * A.datos[i][j];
                    I.datos[k][j] -= factor * I.datos[i][j];
                }
            }
        }
    }

    return I; // La parte derecha de la matriz aumentada es la inversa
}

// Método para redimensionar la matriz
Matriz Matriz::redimensionar(unsigned int nuevas_renglones, unsigned int nuevas_columnas) const {
    Matriz nueva_matriz(nuevas_renglones, nuevas_columnas);
    for (unsigned int i = 0; i < std::min(renglones, nuevas_renglones); ++i) {
        for (unsigned int j = 0; j < std::min(columnas, nuevas_columnas); ++j) {
            nueva_matriz.datos[i][j] = datos[i][j];
        }
    }
    return nueva_matriz;
}


//
double CapturaSeguraM()
{
    double dato;
    std::cin >> dato;
    
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        std::cout << "\nIngresa una respuesta v\240lida.\n - ";
        std::cin >> dato;
    }

    return dato;

}


// Operador de entrada
std::istream& operator>>(std::istream& cin, Matriz& mat) {
    for (unsigned int i = 0; i < mat.renglones; ++i) {
        for (unsigned int j = 0; j < mat.columnas; ++j) {
            mat.datos[i][j] = CapturaSeguraM();
        }
    }
    return cin;
}

// Operador de salida
std::ostream& operator<<(std::ostream& cout, const Matriz& mat) {
    for (unsigned int i = 0; i < mat.renglones; ++i) {
        cout << "|";
        for (unsigned int j = 0; j < mat.columnas; ++j) {
            cout << std::setw(8) << mat.datos[i][j] << " ";
        }
        cout << "|" << std::endl;
    }
    return cout;
}

// Operador no miembro para el producto por escalar conmutativo
Matriz operator*(int escalar, const Matriz& mat) {
    return mat * escalar;
}
