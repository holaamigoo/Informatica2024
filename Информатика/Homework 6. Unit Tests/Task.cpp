#include <iostream>
#include <string>
#include <cmath>
#include <locale>
using namespace std;

float Func(float x, float y){
    if (y == 0) {
        cout << "Division by zero error" << endl;
        throw invalid_argument("Division by zero");
    }
    float R = pow(abs(sin(x) / y), 0.25);
    float S = log10(pow(2, y));
    float C = max(R, S);
    return C;
    }

int main()
{
    setlocale(LC_CTYPE, "rus");
    float x, y;
    cin >> x >> y;
    cout << Func(x, y);
    return 0;
}