#include <iostream>
using namespace std;
int main() {
    locale::global(locale("es_ES.utf8"));
    wstring s = L"Holá muñdo";
    wcout << s << endl;
    return 0;
}