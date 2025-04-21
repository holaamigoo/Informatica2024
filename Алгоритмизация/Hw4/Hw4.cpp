// Hw4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start = chrono::high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Генератор случайных чисел
vector<int> generateRandomVector(int n, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    vector<int> vec;
    vec.reserve(n);

    for (int i = 0; i < n; ++i) {
        vec.push_back(distrib(gen));
    }
    return vec;
}

// ------------------Quick Sort--------------------------
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int part = partition(arr, low, high);
        quickSort(arr, low, part - 1);
        quickSort(arr, part + 1, high);
    }
}

void threadQuickSort(vector<int>& arr, int num_threads) {
    int size = arr.size();
    int chunk = size / num_threads;
    vector<thread> threads;
    // Разделение массива на части и сортировка в потоках
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk;
        int end = (i == num_threads - 1) ? size - 1 : start + chunk - 1;
        // emplace_back создаёт объект непосредственно в конце вектора, то есть без лишнего копирования (или перемещения)
        threads.emplace_back(quickSort, ref(arr), start, end);
        //  ref - создаёт объекты, ведущие себя как ссылки 
    }
    for (auto& thread : threads) {
        // Блокирует выполнение основного потока, пока все рабочие потоки не завершат сортировку своих частей
        thread.join();
    }
    int step = chunk;

    //слияние отсортированных частей
    while (step < size) {
        for (int i = 0; i < size - step; i += 2 * step) {
            int left = i;
            int mid = i + step;
            int right = min(i + 2 * step, size);
            // inplace_merge сливает два отсортированных подмассива [left, mid) и [mid, right) в один.
            inplace_merge(arr.begin() + left, arr.begin() + mid, arr.begin() + right);
        }
        // после каждого прохода размер блока удваивается (сливаются всё более крупные блоки).
        step *= 2;
    }
}
//-------------------------------------------------------



int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> test_sizes = { 100000, 200000, 300000, 400000, 500000, 600000, 700000 };
    vector<int> thread_counts = { 2, 4, 6, 8};
    const int minVal = 1, maxVal = 10000;

    for (int size : test_sizes) {
        cout << "\nРазмер массива: " << size << endl;
        auto nums = generateRandomVector(size, minVal, maxVal);

        // Быстрая сортировка
        auto seq_copy = nums;
        auto seq_time = measure_execution_time(
            [](vector<int>& v) {quickSort(v, 0, v.size() - 1);},
            seq_copy
        );
        cout << "Быстрая: " << seq_time << " мс" << endl;

        // Параллельная быстрая сортировка
        for (int threads : thread_counts) {
            auto par_copy = nums;
            auto par_time = measure_execution_time(
                [threads](vector<int>& v) {
                    threadQuickSort(v, threads);
                },
                par_copy
            );

            cout << threads << " потока: " << par_time << " мс";
            cout << " (ускорение: " << seq_time / (par_time + 0.000001) << ")" << endl;
        }
    }

    return 0;
}
