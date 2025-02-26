/// пусть фигура вписана в прямоугольник с координатами (4; -1) (4; 0,5) (6; -1) (6; 0,5)
// метод монте-карло
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;

// Функция, генерирующая случайное действительное число от min до max
double random(double min, double max) {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

// Функция для вычисления площади круга методом Монте-Карло
double monte_carlo_circle_area(int num_points) {
    int points_inside = 0;
    double x1 = 4.0;
    double x2 = 6.0;
    double y1 = -1.0;
    double y2 = 0.5;

    for (int i = 0; i < num_points; ++i) {
        // Генерируем случайную точку в квадрате
        double x = random(4.0, 6.0);  // Случайное число в диапазоне
        double y = random(-1, 0.5);  // Случайное число в диапазоне 

        // Проверяем, попала ли точка внутрь фигуры
        if (y >= sin(x) && y <= cos(x) && y <= (sin(0.5*x)-0.5)) {
            points_inside++;
        }
    }
    // Вычисление площади прямоугольника
    double square_area = (x2-x1)*(y2-y1);

    // Приближенная площадь фигуры
    return (points_inside / static_cast<double>(num_points)) * square_area;
}


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));  // Инициализируем генератор случайных чисел

    int num_points = 400000000;  // Количество случайных точек
    for (int i = 0; i < 9; ++i) {
        double result = monte_carlo_circle_area(num_points);
        cout << "Приближенная площадь фигуры: " << result << endl;
    }
    return 0;
}
