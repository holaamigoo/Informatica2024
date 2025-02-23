#include <iostream>
#include <chrono>
#include <stack>


template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    auto result = func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return duration.count();  // Возвращаем результат и время выполнения
}

//Оценка вычислительной сложности и потребления памяти: поиск элемента в Стэке
int find_element(std::stack <int> st, int num) {
    if (st.empty())
    {
        std::cout << "stack is empty" << std::endl;
        return -1;
    }
    while (!st.empty()) {
        int result = st.top();
        if (result == num) {
            return result;
        };
        st.pop();
    }
    std::cout << "no such element" << std::endl;
    return -2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::stack <int> st;
    int i = 0;
    while (i != 50000000) {
        st.push(i);
        i++;
    }
    auto execution_time = measure_execution_time(find_element, st, 5);
    int result = find_element(st, 5);
    std::cout << "Результат: " << result << ", Время выполнения: " << execution_time << " мс" << std::endl;
    return 0;
}