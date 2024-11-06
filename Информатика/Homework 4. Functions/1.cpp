#include <iostream>
#include <Windows.h>
using namespace std;

void countPositive(const int* arr, int size, int& counterPositive) {
    counterPositive = 0; // ������������� �����
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            counterPositive += 1;
        }
    }
}

void findArrayWithMinPositiveElements(const int* arrA, const int* arrB, int size) {
    int counterA = 0, counterB = 0;

    // ��������� ����� ��������
    countPositive(arrA, size, counterA);
    countPositive(arrB, size, counterB);

    // ���������� ����� � ������� ������ � ���������� ������
    if (counterA <= counterB) {
        std::cout << "������ A ����� ���������� ����� ������������� ���������: " << counterA << std::endl;
        std::cout << "�������� ������� A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
    }
    else {
        std::cout << "������ B ����� ���������� ����� ������������� ���������: " << counterB << std::endl;
        std::cout << "�������� ������� B: ";
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
    int N; // ������ ��������

    // ���� ������� ��������
    std::cout << "������� ������ �������� (N): ";
    std::cin >> N;

    int* A = new int[N]; // ������������ ��������� ������ ��� ������� A
    int* B = new int[N]; // ������������ ��������� ������ ��� ������� B

    // ���� ��������
    std::cout << "������� " << N << " ��������� ��� ������� A:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cout << "������� " << N << " ��������� ��� ������� B:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> B[i];
    }

    // ����� ������� � ���������� ������
    findArrayWithMinPositiveElements(A, B, N);

    // ������������ ���������� ������
    delete[] A;
    delete[] B;

    return 0;
}