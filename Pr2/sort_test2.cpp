#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>

using namespace std;

const int BASE = 10; //< Number of buckets on Radix Sort
const bool SHOW_UNSORTED = false; //< Muestra el array antes de ser ordenado
const bool SHOW_SORTED = false; //< Muestra el array después de ser ordenado
const int SIZE = 1000;
const int MAX = 65535;
struct Value {
    int key;
    char other[100];
};

void countSort(vector<Value> &v, int MAX); // Working
void radixSort(vector<Value> &v, int MAX); // Working
void radixSortList(list<Value> &l, int MAX); // Working
void base10RadixSort_classic(vector<Value> &v, int MAX);
int digit(int pos, int n);

void base16RadixSort(vector<Value> &v, int MAX); // Working
void base16RadixSortList(list<Value> &l, int MAX);

void base10RadixSort_opt(vector<Value> &v, int MAX);

void countBucketSort(vector<Value> &v, int MAX);

void test(int SIZE, int MAX, void (*sort)(vector<Value> &, int), mt19937  &gen);

void testList(int SIZE, int MAX, void (*sort)(list<Value> &, int), mt19937  &gen);

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    cout << "SORT_TEST2"<<endl;

    cout << "\n 1) CountSort\n";
    test(SIZE, MAX, countSort, gen);

    cout << "\n 1) CountBucketSort\n";
    test(SIZE, MAX, countBucketSort, gen);

    cout << "\n 2) RadixSort\n";
    test(SIZE, MAX, radixSort, gen);

    cout << "\n 2) RadixSort Optimizado\n";
    test(SIZE, MAX, base10RadixSort_opt, gen);

    cout << "\n 3) RadixSortList \n";
    testList(SIZE, MAX, radixSortList, gen);

    cout << "\n 4) Base16RadixSort \n";
    test(SIZE, MAX, base16RadixSort, gen);

    cout << "\n 5) Base16RadixSortList \n";
    testList(SIZE, MAX, base16RadixSortList, gen);

    cout << "\n 6) Base10RadixSort sin optimizar \n";
    test(SIZE, MAX, base10RadixSort_classic, gen);

    return 0;
}

/**
 * Genera un vector de números pseudoaleatorios que posteriormente es ordenado, y mostrar el tiempo que ha llevado dicha
 * ordenación
 * @param SIZE Tamaño del vector
 * @param MAX Máximo del conjunto que queremos ordenar
 * @param sort Algoritmo de ordenación a correr
 */
void test(const int SIZE, int MAX, void (*sort)(vector<Value> &, int), mt19937  &gen) {

    std::uniform_int_distribution<> distrib(0, MAX);
    // Create and show all the unsorted vector
    if (SHOW_UNSORTED)
        cout << "UNSORTED\n" << endl;

    vector<Value> v(SIZE); // Rellendo del Vector
    for (int i = 0; i < SIZE; i++) {
        int randKey = distrib(gen);
        if (SHOW_UNSORTED)
            cout << i << " : " << randKey << endl;
        v[i] = Value{randKey, ""};
    }

    // Medir el tiempo
    auto start = chrono::steady_clock::now();
    sort(v, MAX);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\t> Tiempo = " << (double) diff.count() / 1000;

    if (SHOW_SORTED) {
        cout << "\nSORTED\n";
        for (int i = 0; i < SIZE; i++)
            cout << i << " : " << v[i].key << endl;
    }
}

/**
 * Genera un vector de números pseudoaleatorios que posteriormente es ordenado, y mostrar el tiempo que ha llevado dicha
 * ordenación
 * @param SIZE Tamaño del vector
 * @param MAX Maximo del conjunto que queremos ordenar
 * @param sort Metodo a correr
 */
void testList(const int SIZE, int MAX, void (*sort)(list<Value> &, int), mt19937  &gen) {

    std::uniform_int_distribution<> distrib(0, MAX);
    // Create and show all the unsorted vector
    if (SHOW_UNSORTED)
        cout << "UNSORTED\n";
    list<Value> l;
    for (int i = 0; i < SIZE; i++) {
        int randKey = distrib(gen);
        if (SHOW_UNSORTED)
            cout << i << " : " << randKey << endl;
        l.push_back(Value{randKey, ""});
    }

    // Medir el tiempo
    auto start = chrono::steady_clock::now();
    sort(l, MAX);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\t> Tiempo = " << (double) diff.count() / 1000;


    // Show the sorted vector
    if (SHOW_SORTED) {
        cout << "\nSORTED\n";
        int i = 0;
        for (auto e: l) {
            cout << i << " : " << e.key << endl;
            i++;
        }
    }
}

/**
 * Algoritmo de ordenación que cuenta la cantidad de repeticiones de claves para indicar su posición
 * @param v Vector para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void countSort(vector<Value> &v, const int MAX) {

    // Vector de freceuncias
    vector<unsigned> frec(MAX);
    for (Value e: v){
        frec[e.key]++;
    }

    // Vector Suma acumulada
    for (int i = 1; i <= MAX; i++){
        frec[i] += frec[i-1];
    }

    // Colocación
    vector <Value> v2(v.size());
    for (int i = v.size() - 1; i >= 0; i--) {
        v2[frec[v[i].key] - 1] = v[i];
        frec[v[i].key]--;
    }
    v = v2;
}

/**
 * Implementación del radix sort base 10 de la práctica 1
 * @param v Vector para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void radixSort(vector<Value> &v, const int MAX) {
    int qInf = 1, qSup = BASE;                  //< quotaSuperior = quotaInferior * BASE
    vector<vector<Value>> buckets(BASE); //< the elements are qualified by their value in the digit qInf

    // The loop will iterate log(BASE, MAX-MIN) times, until the qInf<MAX
    while (qInf < MAX) {
        // Put every element on his bucket
        for (auto e: v)
            buckets[(e.key % qSup) / qInf].push_back(e); // position = digit of quotaInf

        /*
        // DEBUG: Show the values of the quotes and buckets on each iteration
        cout<<endl;
        cout << "qInf = " << qInf << "\t";
        cout << "qSup = " << qSup << endl;
        for(int i=0; i<BASE; i++) {
            cout << "b[" << i << "] = ";
            for(auto e: buckets[i])
                cout << e.key << " ";
            cout<<endl;
        }
        cout<<endl;
        */

        // v will be the concatenation of all buckets.and each bucket will be clean
        v.clear();
        for (auto b: buckets)
            v.insert(v.end(), b.begin(), b.end());

        // Create a new empty buckets, (v is using the addresses to the buckets as their elements)
        buckets.clear();
        buckets.resize(BASE);

        // Update the quotes
        qInf = qSup;
        qSup *= BASE;
    }

}

/**
 * Implementación del radix sort base 10 para listas
 * @param l Lista para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void radixSortList(list<Value> &l, const int MAX) {
    int qInf = 1, qSup = BASE;                  //< quotaSuperior = quotaInferior * BASE
    vector<list<Value>> buckets(BASE); //< the elements are qualified by their value in the digit qInf

    // The loop will iterate log(BASE, MAX-MIN) times, until the qInf<MAX
    while (qInf < MAX) {
        // Put every element on his bucket
        for (auto e: l)
            buckets[(e.key % qSup) / qInf].push_back(e); // position = digit of quotaInf

        // l will be the concatenation of all buckets.and each bucket will be clean
        l.clear();
//        auto it = l.begin();
        for (auto b: buckets)
            l.splice(l.end(), b);
//            l.insert(l.end(), b.begin(), b.end());

        // Create a new empty buckets, (v is using the addresses to the buckets as their elements)
        buckets.clear();
        buckets.resize(BASE);

        // Update the quotes
        qInf = qSup;
        qSup *= BASE;
    }
}
/**
 * Implementación del RadixSort en base 16, optimizado utilizando máscaras para calcular el dígito
 * @param v vector a ordenar
 * @param MAX valor máximo del vector
 */
void base16RadixSort(vector<Value> &v, const int MAX) {
    vector<vector<Value>> buckets(16);

    for (int shift = 0; MAX >> shift; shift += 4) {
        // insertar cada elemento a partir del dígito hexadecimal indicado en la máscara
        for (auto e: v)
            buckets[(e.key >> shift) & 0xF].push_back(e);

        // v se sobrescribe con la concatenación de cada cubeta
        v.clear();
        for (auto b: buckets)
            v.insert(v.end(), b.begin(), b.end());

        // reasignar nuevas posiciones de memoria para las cubetas, porque las actuales son utilizadas por v
        buckets.clear();
        buckets.resize(16);
    }
}
/**
 * Implementación del RadixSort base 16 optimizado para listas
 * @param l lista con elementos de 0 a MAX para ordenar
 * @param MAX valor máximo que puede estar presente en l
 */
void base16RadixSortList(list<Value> &l, const int MAX) {
    vector<list<Value>> buckets(16);

    for (int shift = 0; MAX >> shift; shift += 4) {
        // insertar cada elemento a partir del dígito hexadecimal indicado en la máscara
        for (auto e: l)
            buckets[(e.key >> shift) & 0xF].push_back(e);

        // v se sobrescribe con la concatenación de cada cubeta
        l.clear();
        for (auto b: buckets)
            l.splice(l.end(), b);

        // reasignar nuevas posiciones de memoria para las cubetas, porque las actuales son utilizadas por v
        buckets.clear();
        buckets.resize(16);
    }
}
/**
 * Implementación del RadixSort base 10 optimizado, pero calculando la multiplicación con desplazamientos
 * @param v
 * @param MAX
 */
void base10RadixSort_opt(vector<Value> &v, const int MAX) {
    int qInf = 1, qSup = 10;                  //< quotaSuperior = quotaInferior * BASE
    vector<vector<Value>> buckets(BASE);    //< the elements are qualified by their value in the digit qInf

    // The loop will iterate log(BASE, MAX-MIN) times, until the qInf<MAX
    while (qInf < MAX) {
        // Put every element on his bucket
        for (auto e: v)
            buckets[(e.key % qSup) / qInf].push_back(e); // position = digit of quota

        // l will be the concatenation of all buckets.and each bucket will be clean
        v.clear();
        for (auto b: buckets)
            v.insert(v.end(), b.begin(), b.end());

        // Create a new empty buckets, (v is using the addresses to the buckets as their elements)
        buckets.clear();
        buckets.resize(BASE);

        // Update the quotes
        qInf = qSup;
        qSup = (qSup << 3) + (qSup << 1);  //qSup *= 10 ==> qSup*8 + qSup*2
    }
}

/**
 * Algoritmo entre el countsort y el bucketsort, que almacena cada valor del vector en una cubeta, hay tantas cubetas
 * como combinaciones de claves posibles
 * @param v vector a ordenar de 0 a MAX
 * @param MAX valor máximo posible que se puede hallar en MAX
 */
void countBucketSort(vector<Value> &v, const int MAX) {
    vector<vector<Value>> buckets(MAX);
    for (auto e: v)
        buckets[e.key].push_back(e);
    for (auto b: buckets)
        v.insert(v.end(), b.begin(), b.end());
}

/**
 * Calcula el dígito de la posición i  de n siendo el menos significativo i=0, en base 10
 * @param pos posición del dígito a calcular
 * @param n número del cual se quiere extraer el dígito
 * @return Valor del dígito
 */
int digit(int pos, int n) {
    return (n % (10^(pos+1))) / (10^pos);
}
/**
 * Algoritmo de ordenación que clasifica en cubetas cada uno de los dígitos, empezando por el menos significativo, para
 * concatenarlas todas reiterativamente hasta llegar al dígito más significativo
 * @param v Vector a ordenar que contiene elementos de 0 a MAX
 * @param MAX  Valor máximo que se puede hallar en v
 */
void base10RadixSort_classic(vector<Value> &v, const int MAX) {
    vector<vector<Value>> buckets(MAX);

    int log10max = 0;
    int max = MAX;

    // Calcular log10(MAX)
    while(max>1){
        max/=10;
        log10max++;
    }

    // Repetir tantas veces como cifras decimales
    for(int i=0; i<log10max; i++) {
        for(auto e: v)
            buckets[digit(i,e.key)].push_back(e);

        for (auto b: buckets)
            v.insert(v.end(), b.begin(), b.end());

        // Create a new empty buckets, (v is using the addresses to the buckets as their elements)
        buckets.clear();
        buckets.resize(BASE);
    }
}

