/**
 * PRACTICA 4 - Parte 2
 * @author Santiago Millan Giner
 * @author Enric Gil Gallen
 */
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;

const int N_ELEMENTS = 10000;
const int N_REP = 100;

struct Prueba {
    float f1, f2;
    int i1, i2, i3;
    static int i_next;
    char c[N_REP]; // To take up space, not used
    static unsigned char pool[]; // Donde se guardan los objetos
    static bool alloc_map[]; // Indica donde se almacenana

    Prueba() { /*cout << "Prueba()\n"; */ }

    ~Prueba() { /*cout << "~Prueba() ... ";*/ }

    void *operator new(size_t);

    void operator delete(void *);
};

unsigned char Prueba::pool[N_ELEMENTS * sizeof(Prueba)];
bool Prueba::alloc_map[N_ELEMENTS] = {false};
int Prueba::i_next = 0;
queue<int> lista;
/*
//NUEVO NEW
void *Prueba::operator new(size_t) {
    // Hay espacios de memoria disponibles
    if(!lista.empty()){
        int p = lista.back();
        lista.pop();
        alloc_map[p] = true;
        return pool + p * sizeof(Prueba);
    }
    else{
        // No hay espacios disponibles --> Buscamos una posición
        for (int i = i_next; i < N_ELEMENTS; i++)
            if (!alloc_map[i]) {
                //cout << "using block " << i << " ... ";
                alloc_map[i] = true; // Mark it used
                i_next = i + 1;
                lista.push(i);
                return pool + ((i_next - 1) * sizeof(Prueba));
            }
        //cout << "out of memory" << endl;
    }
    throw bad_alloc();
}
// NUEVO DELETE
void Prueba::operator delete(void *m) {
    if (!m) return; // Check for null pointer
    // Assume it was created in the pool
    // Calculate which block number it is:
    unsigned long block = (unsigned long) m - (unsigned long) pool;
    block /= sizeof(Prueba);
    //cout << "freeing block " << block << endl; // Mark it free:
    alloc_map[block] = false;
}
*/

 //VIEJO NEW
 void* Prueba::operator new(size_t) {
    for(int i = 0; i < N_ELEMENTS; i++)
        if(!alloc_map[i]) {
            //cout << "using block " << i << " ... ";
            alloc_map[i] = true; // Mark it used
            return pool + (i * sizeof(Prueba));
        }
    //cout << "out of memory" << endl;
    throw bad_alloc();
}

// VIEJO DELETE
void Prueba::operator delete(void* m) {
    if(!m) return; // Check for null pointer
    // Assume it was created in the pool
    // Calculate which block number it is:
    unsigned long block = (unsigned long)m - (unsigned long)pool;
    block /= sizeof(Prueba);
    //cout << "freeing block " << block << endl; // Mark it free:
    alloc_map[block] = false;
}


/*
void* operator new (size_t sz) {
    return malloc(sz);
}

void operator delete (void* m) {
    free(m);
}
 */


int costMem1();

int costMem2(vector<int> &deleteOrder);

int costMem2();

int costMem3();

int costMem4();

void test(int(*f)());

void test(int(*f)(vector<int> &), vector<int> &deleteOrder);

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


    cout << "5.- Memoria dinamica, borrado de orden aleatorio" << endl;
    vector<int> deleteOrder(N_ELEMENTS);
    for (int i = 0; i < N_ELEMENTS; i++)
        deleteOrder[i] = i;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deleteOrder.begin(), deleteOrder.end(), gen);

    test(costMem2);


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

    for (i = 0; i < N_ELEMENTS; i++) {
        v[i].i1 = i;
    }

    volatile int suma = 0;
    for (i = 0; i < N_ELEMENTS; i++) {
        suma += v[i].i1;
    }

    return suma;
}

/**
 * Primer bucle bucle también asignará los 10.000 objetos en memoria dinámica con el operador new
 * Segundo calcula la suma de todos los elementos
 * Tercer borra todos los valores de memoria
 * @return la suma final
 */
int costMem2() {
    Prueba *v[N_ELEMENTS];
    int i;

    for (i = 0; i < N_ELEMENTS; i++) {
        v[i] = new Prueba;
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i = 0; i < N_ELEMENTS; i++) {
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
int costMem3() {
    unique_ptr<Prueba> v[N_ELEMENTS];
    int i;

    for (i = 0; i < N_ELEMENTS; i++) {
        v[i].reset(new Prueba);
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i = 0; i < N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    return suma;
}

/**
 * Metodo que basado en costeMem2 sustituyendo todos los punteros por shared_ptr.
 * @return la suma final
 */
int costMem4() {
    shared_ptr<Prueba> v[N_ELEMENTS];
    int i;

    for (i = 0; i < N_ELEMENTS; i++) {
        v[i].reset(new Prueba);
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i = 0; i < N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    return suma;
}


void test(int(*f)()) {
    auto start = chrono::steady_clock::now();

    for (int i = 0; i < N_REP; i++) {
        f();
    }

    auto end = chrono::steady_clock::now();

    auto diff = end - start;
    cout << "\t> t = " << (double) diff.count() / N_REP << endl << endl;
}

void test(int(*f)(vector<int> &), vector<int> &deleteOrder) {
    auto start = chrono::steady_clock::now();

    for (int i = 0; i < N_REP; i++) {
        f(deleteOrder);
    }

    auto end = chrono::steady_clock::now();

    auto diff = end - start;
    cout << "\t> t = " << (double) diff.count() / N_REP << endl << endl;
}

/**
 * Matriz
 * Primer bucle bucle también asignará los 10.000 objetos en memoria dinámica con el operador new
 * Segundo bucle liberará todos los objetos
 * Tercer bucle borra los objetos en un orden aleatorio
 * @return la suma final
 */

int costMem2(vector<int> &deleteOrder) {
    Prueba *v[N_ELEMENTS];
    int i;

    for (i = 0; i < N_ELEMENTS; i++) {
        v[i] = new Prueba;
        v[i]->i1 = i;
    }

    volatile int suma = 0;
    for (i = 0; i < N_ELEMENTS; i++) {
        suma += v[i]->i1;
    }

    for (i = 0; i < N_ELEMENTS; i++) {
        delete v[deleteOrder[i]];
    }

    return suma;
}