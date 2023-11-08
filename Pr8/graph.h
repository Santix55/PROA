#ifndef _GRAPH_H
#define _GRAPH_H

#include <assert.h>
#include <stdexcept>
using namespace std;
/**
 * Matriz de adyacencia de memoría estática
 * @tparam T Tipo del peso del arco
 * @tparam SIZE Número de elementos
 */
template <class T, int SIZE>
class Graph {
private:
    T m [SIZE][SIZE];
public:
    /**
     * Accede al elemento especificado
     * @param a fila
     * @param b columna
     * @return referencia al elemento
     */
    T& operator()(int a, int b)  {
        if (a>=SIZE || b>=SIZE || a<0 || b<0)
            throw out_of_range("Elemento fuera del rango de la matriz");
        return m[a][b];
    }
};
#endif
