/**
 * PRACTICA 4
 * @author Santiago Millan Giner
 * @author Enric Gil Gallen
 */
#include <iostream>
#include <chrono>
#include <memory>
using namespace std;

const int N_ELEMENTS = 10000;
const int N_REP = 100;

struct Prueba {
    float f1, f2;
    int i1, i2, i3;
};

int costMem1();
int costMem2();
int costMem3();
int costMem4();
void test (int(*f)());

/**
 * Parte principal del código donde se llama a los distintos métodos
 * @return
 */
int main() {

    cout << "1.- Memoria estatica" << endl;
    test(costMem1);

    cout << "2.- Memoria dinamica" << endl;
    test(costMem2);

    cout << "3.- Punteros unicos --> unique_ptr" << endl;
    test(costMem3);

    cout << "4.- Punteros compartidos --> shared_ptr" << endl;
    test(costMem4);

    cout << endl;
    return 0;
}
/**
 * Array
 * Primero for asigna al atributo i1 de cada objeto el valor de la posición en el array (v[i].i1 = i)
 * Segundo for calcula la suma de todos estos valores (suma += v[i].i1)
 * @return la suma final
 */
int costMem1() {
    Prueba v[N_ELEMENTS];
    int i;

    for (i=0; i<N_ELEMENTS; i++) {
        v[i].i1 = i;
    }

    volatile int suma = 0;
    for (i=0; i<N_ELEMENTS; i++) {
        suma += v[i].i1;
    }

    return suma;
}
/**
 * Matriz
 * Primer bucle bucle también asignará los 10.000 objetos en memoria dinámica con el operador new
 * Segundo for calcula la suma de todos estos valores (suma += v[i].i1)
 * Tercero bucle liberará todos los objetos
 * @return la suma final
 */
int costMem2 () {
    Prueba* v [N_ELEMENTS];
    int i;

    for (i=0; i<N_ELEMENTS; i++) {
        v[i] = new Prueba;
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i=0; i<N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    for (i = 0; i < N_ELEMENTS; i++) {
        delete v[i];
    }

    return suma;
}

/**
 * Metodo que basado en costeMem2 sustituyendo todos los punteros por unique_ptr.
 * @return la suma final
 */
int costMem3 () {
    unique_ptr<Prueba> v [N_ELEMENTS];
    int i;

    for (i=0; i<N_ELEMENTS; i++) {
        v[i].reset(new Prueba);
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i=0; i<N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    return suma;
}

/**
 * Metodo que basado en costeMem2 sustituyendo todos los punteros por shared_ptr.
 * @return la suma final
 */
int costMem4 () {
    shared_ptr<Prueba> v [N_ELEMENTS];
    int i;

    for (i=0; i<N_ELEMENTS; i++) {
        v[i].reset(new Prueba);
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i=0; i<N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    return suma;
}


void test (int(*f)()) {
    auto start = chrono::steady_clock::now();

    for (int i=0; i<N_REP; i++) {
        f();
    }

    auto end = chrono::steady_clock::now();

    auto diff = end - start;
    cout <<"\t> t = " << (double) diff.count() / N_REP << endl << endl;
}