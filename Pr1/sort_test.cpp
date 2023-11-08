#include <iostream>
#include <vector>
#include <list>
#include <random>

using namespace std;

const int BASE = 10; //< Number of buckets on Radix Sort

struct Value {
    int key;
    char other[100];
};

void countSort(vector <Value> &v, int MAX); // Working
void radixSort(vector <Value> &v, int MAX); // Working
void radixSortList(list <Value> &l, int MAX); // Working

void test(int SIZE, int MAX, void (*sort)(vector <Value> &, int));
void testList(int SIZE,  int MAX, void (*sort)(list <Value> &, int));

int randInt(int MIN, int MAX, int SEED);

int main() {

    cout << "\n 1) Countsort [0, 255] \n";
    test(20, 255, countSort);

    cout << "\n 2) Countsort [0, 65535] \n";
    test(20, 65535, countSort);

    cout << "\n 3) Radixsort [0, 255] \n";
    test(20, 255, radixSort);

    cout << "\n 4) Radixsort [0, 65535] \n";
    test(20, 65535, radixSort);

    cout << "\n 5) RadixsortList [0, 255] \n";
    testList(20, 255, radixSortList);

    cout << "\n 6) RadixsortList [0, 65535] \n";
    testList(20, 65535, radixSortList);

    return 0;
}

/**
 * @param SIZE Tamaño del vector
 * @param MAX Maximo del conjunto que queremos ordenar
 * @param sort Metodo a correr
 */
void test(const int SIZE,  int MAX, void (*sort)(vector <Value> &, int)) {

    // Create and show all the unsorted vector
    cout << "UNSORTED\n";
    vector <Value> v(SIZE);
    for (int i = 0; i < SIZE; i++) {
        int randKey = randInt(0, MAX, i);
        cout << i << " : " << randKey << endl;
        v[i] = Value{randKey, ""};
    }

    // Show the sorted vector
    sort(v, MAX);
    cout << "\nSORTED\n";
    for (int i = 0; i < SIZE; i++)
        cout << i << " : " << v[i].key << endl;
}
/**
 *
 * @param SIZE Tamaño del vector
 * @param MAX Maximo del conjunto que queremos ordenar
 * @param sort Metodo a correr
 */
void testList(const int SIZE,  int MAX, void (*sort)(list <Value> &, int)) {

    // Create and show all the unsorted vector
    cout << "UNSORTED\n";
    list <Value> l;
    for (int i = 0; i < SIZE; i++) {
        int randKey = randInt(0, MAX, i);
        cout << i << " : " << randKey << endl;
        l.push_back(Value{randKey, ""});
    }

    // Show the sorted vector
    sort(l, MAX);
    cout << "\nSORTED\n";
    int i = 0;
    for (auto e: l) {
        cout << i << " : " << e.key << endl;
        i++;
    }
}

/**
 * @param MIN Nº por el que empieza la secuencia
 * @param MAX Nº por el que termina la secuencia
 * @param SEED Semilla con la que genera los numeros
 * @return
 */
int randInt(const int MIN, const int MAX, const int SEED) {
    mt19937 randGen(SEED);
    return MIN + randGen() % (MAX - MIN);
}
/**
 * @param v Vector para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void countSort(vector <Value> &v,  const int MAX) {

    // c stores the quantity of repetitions of each element on v
    vector<unsigned> c(MAX);
    for (Value e: v)
        c[e.key]++;

    // c now stores the index of each value
    for (int i = 1; i < MAX; i++)
        c[i] += c[i - 1];

    /*
    // DEBUG: Show c vector
    for (int i=0; i<c.size(); i++)
        cout << "c["<<i<<"]="<<c[i]<<endl;
    */

    // put each value on the index marked by c[i]
    vector <Value> v2(v.size());
    for (int i = v.size() - 1; i >= 0; i--) {
        //cout << i << " " << v[i].key << " " << c[v[i].key ] - 1 << endl;
        v2[c[v[i].key] - 1] = v[i];
        c[v[i].key]--;
    }
    v = v2;
}

/**
 * @param v Vector para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void radixSort(vector <Value> &v,  const int MAX) {
    int qInf = 1, qSup = BASE;                  //< quotaSuperior = quotaInferior * BASE
    vector <vector<Value>> buckets(BASE); //< the elements are qualified by their value in the digit qInf

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
 *
 * @param l Lista para ordenar
 * @param MAX Maximo del conjunto que queremos ordenar
 */
void radixSortList(list <Value> &l,  const int MAX) {
    int qInf = 1, qSup = BASE;                  //< quotaSuperior = quotaInferior * BASE
    vector <vector<Value>> buckets(BASE); //< the elements are qualified by their value in the digit qInf

    // The loop will iterate log(BASE, MAX-MIN) times, until the qInf<MAX
    while (qInf < MAX) {
        // Put every element on his bucket
        for (auto e: l)
            buckets[(e.key % qSup) / qInf].push_back(e); // position = digit of quotaInf

        // l will be the concatenation of all buckets.and each bucket will be clean
        l.clear();
        for (auto b: buckets)
            l.insert(l.end(), b.begin(), b.end());

        // Create a new empty buckets, (v is using the addresses to the buckets as their elements)
        buckets.clear();
        buckets.resize(BASE);

        // Update the quotes
        qInf = qSup;
        qSup *= BASE;
    }

}