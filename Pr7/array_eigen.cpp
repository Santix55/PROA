#include <Eigen/Core>
#include <chrono>
#include <iostream>

using Eigen::ArrayXd;
using std::cout;
using std::endl;

const unsigned TAM = 1000000;
const unsigned REP = 1000;

int main()
{
    ArrayXd x(TAM), y(TAM);

    for(unsigned i = 0; i < TAM; i++)
    {
        x(i) = 2;
        y(i) = 3;
    }

    cout << " TEST APARTADO 4" << endl;
    x = ((1.2 + x) * y + (2.0 * y).pow(2.0) ) * x;

    for(unsigned i = 0; i < 10; i++)
    {
        cout << x(i) << " ";
    }
    cout << endl;

    return 0;
}
