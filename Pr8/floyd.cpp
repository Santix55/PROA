#include "graph.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <list>
#include <tuple>

using std::cout;
using std::endl;
using std::enable_if;
using std::is_integral;
using std::random_device;
using std::mt19937;
using std::list;
using std::min;


// Generador de números aleatoreos gen //
random_device rd;
mt19937 randomGen(rd());

/**
 * Generador de grafos con pesos de arcos pseudo-aleatorios acotados enteros
 * @tparam Number Tipo númerico
 * @tparam SIZE Tamaño del grafo
 * @param min Valor mínimo posible como peso de arco
 * @param min Valor máximo posible como peso de arco
 * @return grafo resultante
 */
template <typename Number, int SIZE>
typename enable_if<is_integral<Number>::value,void>::type
randomize(Number min, Number max, Graph<Number,SIZE>& g)  {
    int i, j;
    uniform_int_distribution<Number> distribution (min,max);

    // Triangulo superior (sin incluir diagonal), con valores aleatorios
    for(i=0; i<SIZE; ++i) {
        for(j=i+1; j<SIZE; ++j) {
             g(i,j) = distribution(randomGen);
             g(j,i) = g(i,j);
        }
    }

    // Triangulo inferior (incluyendo diagonal), con el valor 0
    for(i=0; i<SIZE; ++i) {
        g(i,i) = 0;
    }
}


/**
 * Generador de grafos con pesos de arcos pseudo-aleatorios acotados reales
 * @tparam Number Tipo númerico
 * @tparam SIZE Tamaño del grafo
 * @param min Valor mínimo posible como peso de arco
 * @param min Valor máximo posible como peso de arco
 * @return grafo resultante
 */
template <typename Number, int SIZE>
typename enable_if<is_floating_point<Number>::value,void>::type
randomize(Number min, Number max, Graph<Number,SIZE>& g) {
    int i, j;
    uniform_real_distribution<Number> distribution (min,max);

    // Triangulo superior (sin incluir diagonal), con valores aleatorios
    for(i=0; i<SIZE; ++i) {
        for(j=i+1; j<SIZE; ++j) {
            g(i,j) = distribution(randomGen);
            g(j,i) = g(i,j);
        }
    }

    // Triangulo inferior (incluyendo diagonal), con el valor 0
    for(i=0; i<SIZE; ++i) {
        g(i,i) = 0;
    }
}

template <typename Number, int SIZE>
void print(Graph<Number,SIZE> g){
    int i, j;

    for(i=0; i<SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            cout << g(i,j) << "\t";
        }
        cout << endl;
    }
}

template<typename Number, int SIZE>
Graph<Number,SIZE> floyd (Graph<Number,SIZE> g) {
    Graph<Number,SIZE> solucion;
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            solucion(i,j) = g(i,j);
        }
    }

    for(int k=0; k<SIZE; k++) {
        for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                solucion(i,j) = min(solucion(i,j), solucion(i,k) + solucion(k,j));
            }
        }
    }

    return solucion;
}

template<typename Number, int SIZE>
list<int> camino(int ini, int fin, Graph<Number,SIZE> & g) {
    if (ini == fin)
        return list<int> ({ini});
    else {
        auto l = camino(ini, g(ini,fin), g);
        l.push_back(fin);
        return l;
    }

}

template<typename Number, int SIZE>
auto floyd2 (Graph<Number,SIZE> g) {
    Graph<Number,SIZE> pesos;
    Graph<int,SIZE> steps;

    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            pesos(i,j) = g(i,j);
            steps(i,j) = i;
        }
    }

    for(int k=0; k<SIZE; k++) {
        for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                if (pesos(i,j) > (pesos(i,k) + pesos(k,j)) ){
                    pesos(i,j) = pesos(i,k) + pesos(k,j);
                    steps(i,j) = steps(k,j);
                }
            }
        }
    }

    return make_tuple(pesos, steps, camino(0,1,steps));
}

int main() {
    /*
    Graph<double, 6> g;
    g(0,0) = 5;
    cout << ++g(0,0)<<endl;
    cout << g(0,0)<<endl;
    cout << g(7,7);
    */
    /*
    {
        cout << endl;
        Graph<int, 5> g;
        randomize(1, 9, g);
        print(g);
    }
    {
        cout << endl;
        Graph<double, 5> g;
        randomize(1.0, 9.0, g);
        print(g);
    }
    */
    {
        cout << "PRUEBA FLOYD 1" << endl;
        const int SIZE = 6;
        Graph<double, SIZE> g;
        randomize(0.5, 5.0, g);


        uniform_int_distribution distribution(0, 1);
        for (int i = 1; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                if (distribution(randomGen)) {
                    g(i, j) *= 5;
                    g(j, i) *= 5;
                }
            }
        }

        cout << "Problema" << endl;
        print(g);

        cout << endl;

        cout << "Solucion" << endl;
        auto solucion = floyd(g);
        print(solucion);
    }

    cout << endl;

    {
        cout << "PRUEBA FLOYD 2" << endl;
        const int SIZE = 8;
        Graph<int, SIZE> g;
        randomize(1, 9, g);

        cout << "Problema" << endl;
        print(g);
        cout << endl;

        auto res = floyd2(g);

        cout << "Solucion pesos" << endl;
        print(get<0>(res));
        cout << endl;

        cout << "Solucion pasos" << endl;
        print(get<1>(res));
        cout << endl;

        cout << "Camino" << endl;
        for(auto e: get<2>(res) ) {
            cout << e << endl;
        }

    }


    return 0;
}

