#include <iostream>
#include <string>
#include <cmath>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    float x, y, R, S, C;
    cin >> x >> y;
    R = pow(abs(sin(x) / y), 0.25);
    S = log10(pow(2, y));
    cout << R << endl << S << endl;
    C = max(R, S);
    cout << C << endl;
    //cin.get();
    return 0;
}