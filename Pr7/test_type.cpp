#include "expresion.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    Array<double> x(10), y(10);
    cout << (1.2 * x + y ).type() << endl;
    return 0;
}
