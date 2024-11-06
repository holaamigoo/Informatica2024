#include <iostream>
#include <Windows.h>
using namespace std;

void countPositive(const int* arr, int size, int& counterPositive) {
    counterPositive = 0; // Инициализация суммы
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            counterPositive += 1;
        }
    }
}

void findArrayWithMinPositiveElements(const int* arrA, const int* arrB, int size) {
    int counterA = 0, counterB = 0;

    // Вычисляем суммы массивов
    countPositive(arrA, size, counterA);
    countPositive(arrB, size, counterB);

    // Сравниваем суммы и выводим массив с наибольшей суммой
    if (counterA <= counterB) {
        std::cout << "Массив A имеет наименьшее число положительных элементов: " << counterA << std::endl;
        std::cout << "Элементы массива A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
    }
    else {
        std::cout << "Массив B имеет наименьшее число положительных элементов: " << counterB << std::endl;
        std::cout << "Элементы массива B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N; // Размер массивов

    // Ввод размера массивов
    std::cout << "Введите размер массивов (N): ";
    std::cin >> N;

    int* A = new int[N]; // Динамическое выделение памяти для массива A
    int* B = new int[N]; // Динамическое выделение памяти для массива B

    // Ввод массивов
    std::cout << "Введите " << N << " элементов для массива A:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cout << "Введите " << N << " элементов для массива B:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> B[i];
    }

    // Поиск массива с наибольшей суммой
    findArrayWithMinPositiveElements(A, B, N);

    // Освобождение выделенной памяти
    delete[] A;
    delete[] B;

    return 0;
}