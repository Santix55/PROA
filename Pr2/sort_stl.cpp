#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

struct Value {
    int key;
    char other[100];
};
const int BASE = 10; //< Number of buckets on Radix Sort
const bool SHOW_UNSORTED = false; //< Muestra el array antes de ser ordenado
const bool SHOW_SORTED = false; //< Muestra el array después de ser ordenado

void stl(vector<Value>& v, int MAX);
void stlList(list<Value> &v, int MAX);

void countSort(vector<Value> &v, int MAX);

void radixSort(vector<Value> &v, int MAX);

void radixSortList(list<Value> &l, int MAX);

void base16RadixSort(vector<Value> &v, int MAX);

void base16RadixSortList(list<Value> &l, int MAX);

void countBucketSort(vector<Value> &v, const int MAX);

vector<Value> generadorVectores(int size, int max, mt19937 &gen);

list<Value> generadorListas(int size, int max, mt19937 &gen);

int main() {
    int size = 0;
    int max1 = 255;
    int max2 = 65535;

    for (int i = 1000; i <= 100000; i *= 10) {
        size = i;

        std::random_device rd;
        std::mt19937 gen(rd());

        vector<Value> v1 = generadorVectores(size, max1, gen);
        vector<Value> v2 = generadorVectores(size, max2, gen);

        list<Value> v3 = generadorListas(size, max1, gen);
        list<Value> v4 = generadorListas(size, max2, gen);

        cout << "STL con 255 y size: " << size << endl;
        auto start = chrono::steady_clock::now();
        stl(v1, max1);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "STL con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        stl(v2, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "STL List con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        stlList(v3, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "STL List con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        stlList(v4, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "Count Sort con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        countSort(v1, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "Count Sort con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        countSort(v2, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "Radix Sort con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        radixSort(v1, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "Radix Sort con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        radixSort(v2, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "radixSortList con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        radixSortList(v3, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "Radix SortList con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        radixSortList(v4, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "base16RadixSort con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        base16RadixSort(v1, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "base16RadixSort con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        base16RadixSort(v2, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "base16RadixSortList con 255 y size: " << size << endl;
        start = chrono::steady_clock::now();
        base16RadixSortList(v3, max1);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

        cout << "base16RadixSortList con 65535 y size: " << size << endl;
        start = chrono::steady_clock::now();
        base16RadixSortList(v4, max2);
        end = chrono::steady_clock::now();
        diff = end - start;
        cout << "\t> Tiempo = " << (double) diff.count() / 1000 << endl;

    }

    return 0;
}

vector<Value> generadorVectores(int size, int max, mt19937 &gen) {
    std::uniform_int_distribution<> distrib(0, max);

    vector<Value> v(size); // Rellendo del Vector
    for (int i = 0; i < size; i++) {
        int randKey = distrib(gen);
        if (SHOW_UNSORTED)
            cout << i << " : " << randKey << endl;
        v[i] = Value{randKey, ""};
    }
    return v;
}

list<Value> generadorListas(int size, int max, mt19937 &gen) {
    std::uniform_int_distribution<> distrib(0, max);

    list<Value> l;
    for (int i = 0; i < size; i++) {
        int randKey = distrib(gen);
        if (SHOW_UNSORTED)
            cout << i << " : " << randKey << endl;
        l.push_back(Value{randKey, ""});
    }
    return l;
}

void stl(vector<Value> &s, int MAX){
    std::sort(s.begin(), s.end(), [](const Value &a, const Value &b) {
        return a.key < b.key;
    });
}

void stlList(list<Value> &s, int MAX){

    s.sort([](const Value & a, const Value & b) { return a.key < b.key; });
}

void countSort(vector<Value> &v, const int MAX) {

    // Vector de freceuncias
    vector<unsigned> frec(MAX);
    for (Value e: v) {
        frec[e.key]++;
    }

    // Vector Suma acumulada
    for (int i = 1; i <= MAX; i++) {
        frec[i] += frec[i - 1];
    }

    // Colocación
    vector<Value> v2(v.size());
    for (int i = v.size() - 1; i >= 0; i--) {
        v2[frec[v[i].key] - 1] = v[i];
        frec[v[i].key]--;
    }
    v = v2;

}

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
//            l.insert(l.end(), b.begin(), b.end());

        // reasignar nuevas posiciones de memoria para las cubetas, porque las actuales son utilizadas por v
        buckets.clear();
        buckets.resize(16);
    }
}

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

void countBucketSort(vector<Value> &v, const int MAX) {
    vector<vector<Value>> buckets(MAX);
    for (auto e: v)
        buckets[e.key].push_back(e);
    for (auto b: buckets)
        v.insert(v.end(), b.begin(), b.end());
}