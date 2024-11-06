#include <iostream>
#include <Windows.h>
#include <set>
#include <algorithm>
using namespace std;

double calculateArithmeticMean(const set <int>& s) {
    int counter = 0; // Инициализация суммы
    for (int n : s) {
        counter += n;
    }
    return ((double) counter / (double) s.size());
}

void calculateIntersection(const set <int>& a, const set <int>& b, set <int>& u) {
    //Пересечение двух множеств
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(u, u.begin()));
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N; // Размер массивов

    // Ввод размера массивов
    std::cout << "Введите размер множеств: ";
    std::cin >> N;

    set<int> A{};
    set<int> B{};
    set<int> U{};

    // Ввод множеств
    std::cout << "Введите " << N << " элементов для множества A:" << std::endl;
    for (int i = 0; i < N; i++) {
        int num = 0;
        cin >> num;
        A.insert(num);
    }

    std::cout << "Введите " << N << " элементов для множества B:" << std::endl;
    for (int i = 0; i < N; i++) {
        int num = 0;
        cin >> num;
        B.insert(num);
    }

    calculateIntersection(A, B, U);
    cout << calculateArithmeticMean(U);

    return 0;
}