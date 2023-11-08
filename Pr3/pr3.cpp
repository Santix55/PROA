#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <unordered_map>
#include <tuple>
#include <algorithm>

using namespace std;

const int N_TEST = 30;

/**
 * Obtiene todas las palabras conformadas únicamente por caracteres alfabéticos españoles (el resto son considerado
 * separadores), de un fichero
 * @param fileName nombre del fichero
 * @return vector de wstring con cada palabra almacenada en un elemento
 */
vector<wstring> getWords (const string & fileName);

/**
 * Cuenta las repeticiones de palabras de un conjunto estos, usando la clase map
 * @param v vector de palabras cual se quieren contar los elementos
 * @return mapa con clave palabra y vector repeticiones
 */
map<wstring,unsigned> countRepetitions (const vector<wstring> & v);

/**
 * Cuenta las repeticiones de palabras de un conjunto estos, usando la clase unordered map
 * @param v vector de palabras cual se quieren contar los elementos
 * @return mapa con clave palabra y vector repeticiones
 */
unordered_map<wstring,unsigned> countRepetitions_um (const vector<wstring> & v);

/**
 * Muestra las 30 palabras por orden más repetidas en un texto
 * @param v vector de palabras
 */
void mostFrequent30 (const vector<wstring> &v);

/**
 * Función auxiliar de mostFrequent30, su objetivo es insertar de forma ordenada el valor nuevo en el vector
 * @param v vector de 30 elementos con el valor más frecuente
 * @param nuevo par clave-valor a insertar en v
 * @return nueva frecuencia mínima
 */
int ordenar(vector<pair<wstring, int>> &v, pair<wstring, int> nuevo);

int main() {
    // Poner el idioma en español
    locale::global(locale("es_ES.utf8"));

    wcout << L"### TEST 1 ###" << endl;
    // Contar las repeticiones de palabras del texto usando map e imprimir
    auto words = getWords("texto1.txt");
    auto map = countRepetitions(words);
    for(const auto & p: map)
        wcout << p.first << L": " << p.second << endl;

    wcout << endl;

    wcout << L"### TEST 2 ###" << endl;
    // Medir el tiempo del algoritmo de contado
    words = getWords("texto2.txt");
    long sum = 0;
    for(int i=0; i<N_TEST; i++) {
        auto ini = chrono::steady_clock::now();
        countRepetitions(words);
        auto fin = chrono::steady_clock::now();
        auto dif =  chrono::duration_cast <chrono::microseconds> (fin - ini).count();
        wcout << L"t" << i << L" = " << dif << L" μs" << endl;
        sum += dif;
    }
    wcout << endl << L"tμ = " << (double) sum / 1e6 / N_TEST << L"s" << endl;

    wcout << endl;

    wcout << L"### TEST 3 ###" << endl;
    // Medir el tiempo del algoritmo de contado
    words = getWords("texto2.txt");
    sum = 0;
    for(int i=0; i<N_TEST; i++) {
        auto ini = chrono::steady_clock::now();
        countRepetitions_um(words);
        auto fin = chrono::steady_clock::now();
        auto dif =  chrono::duration_cast <chrono::microseconds> (fin - ini).count();
        wcout << L"t" << i << L" = " << dif << L" μs" << endl;
        sum += dif;
    }
    wcout << endl << L"tμ = " << (double) sum / 1e6 / N_TEST << L"s" << endl;

    wcout << endl;

    wcout << L"### TEST 4 ###" << endl;
    // Mostrar las 30 palabras más frecuente del texto 2
    mostFrequent30(words);

    cout << endl << endl;

    return 0;
}

vector<wstring> getWords (const string &fileName) {
    locale loc("es_ES.utf8");

    // Abrir el archivo usando la variable wif, si no se abre notifica y cierra
    wifstream wif(fileName, ios::in);
    if(!wif.is_open()) {
        wcout << L"El archivo no se ha podido abrir \n";
        return {};
    }


    // Añadir las palabras del texto, en minúscula, al vector words
    // Nota: los wcout es para ver como funciona la detección de palabras

    wstring word;           // posible palabra actual a añadir
    vector<wstring> words;  // contiene todas las palabras del texto

    while (wif.good()) {
        wchar_t c = wif.get();          // Leer todos los caracteres c del texto

        if (isalpha(c, loc))
            word.push_back(tolower(c,loc));
        else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    wif.close();
    return words;
}

map<wstring,unsigned> countRepetitions (const vector<wstring> & v) {
    map<wstring,unsigned> m;

    for(const wstring & key: v) {
        auto it = m.find(key);    // buscar duo clave-valor y guardar puntero en it
        if (it==m.end())                       // Si no se encuentra
            m[key] = 1;                        //   incluir en el mapa
        else                                   // Si se encuentra
            it->second++;                      //   contar la nueva repetición
    }

    return m;
}

unordered_map<wstring,unsigned> countRepetitions_um(const vector<wstring> & v) {
    unordered_map<wstring,unsigned> m;

    for(const wstring & key: v) {
        auto it = m.find(key);    // buscar duo clave-valor y guardar puntero en it
        if (it==m.end())                       // Si no se encuentra
            m[key] = 1;                        //   incluir en el mapa
        else                                   // Si se encuentra
            it->second++;                      //   contar la nueva repetición
    }

    return m;
}

int ordenar(vector<pair<wstring, int>> &v, pair<wstring, int> nuevo){

    int val_nuevo = nuevo.second;
    pair<wstring, int> aux;
    pair<wstring, int> aux2;

    // Buscar elemento del que empezaremos a desplazar
    for(unsigned i = 0; i < v.size(); i++){
        if(v[i].second <= val_nuevo){
            aux = nuevo;
            // Desplazar elementos a la derecha
            for (unsigned j = i; j < v.size(); ++j) {
                aux2 = v[j];
                v[j] = aux;
                aux = aux2;
            }

            return v[v.size()-1].second;
        }
    }
    return 0;
}

void mostFrequent30 (const vector<wstring> & v) {
    map<wstring, int> m;
    map<wstring, int>::iterator it;

    // Almacenar todas las palabras en un unordered_map : coste O(n)
    for(const wstring & key: v) {
        it = m.find(key);                   // buscar duo clave-valor y guardar puntero en it
        if (it==m.end())                       // Si no se encuentra
            m[key] = 1;                        //   incluir en el mapa
        else                                   // Si se encuentra
           it->second++;                       //   contar la nueva repetición
    }

    // Lo que tengo en mente es:
    //      Solo ordenar los elementos del vector cuando sea mas grande que el minimo
    //      Acotar por busqueda binarea
    //      Ordenar solo el tramo necesario

    vector<pair<wstring, int>> v_mejores (30, make_pair(L"",0));
    int frecuencia_minima = -1;
    int ultima_pos = 0;

    for(auto it: m){
        if(it.second > frecuencia_minima){ // Miramos a ver si podemos añadir el elemento

            // Ordenar y devolver la nueva frecuencia minima
            frecuencia_minima = ordenar(v_mejores,  it);

            if (ultima_pos < 29) { // Limitar en tamaño del vector
                ultima_pos++;
                frecuencia_minima = 0;
            }

        }

    }


    // Mostrar resultado
    for(auto it: v_mejores){
        std::wcout << it.first << " Aparece: " << it.second << " veces." << endl;
    }

}