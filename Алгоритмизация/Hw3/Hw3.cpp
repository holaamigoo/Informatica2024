// Поразрядная сортировка	Сортировка Шелла	Быстрая сортировка
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>


using namespace std;

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами без сохранения результата
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return duration.count();  // Возвращаем результат и время выполнения
}

// Function to get maximum value in arr[]
int getMax(vector<int> arr)
{
    int mx = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
//-------- Radix Sort -------------------------------------

vector<int> MergeBins(vector<vector<int>> bins) {
    vector<int> mergedArr;
    for (int i = 0; i < bins.size(); i++) {
        mergedArr.insert(mergedArr.end(), bins[i].begin(), bins[i].end());
    }
    return mergedArr;
}


void SortByDigits(vector<int> &arr, int digit) {
    vector<vector<int>> bins(10);
    for (int i = 0; i < arr.size(); i++) {
        int index = (arr[i] / digit) % 10;
        bins[index].push_back(arr[i]);
    }
    arr = MergeBins(bins);
}


void RadixSort(vector<int> &arr) {
	int max_num = getMax(arr);
    int digit = 1;
    while (max_num / digit > 0) {
        SortByDigits(arr, digit);
        digit = digit * 10;
    }
}

//-----------------------------------------------------

//-------------------Shell Sort----------------------
void ShellSort(vector<int>& arr) {
    int n = arr.size();
    int step = n / 2;

    while (step > 0){
        for (int i = step; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while ((j >= step) && (arr[j - step] > temp)) {
                arr[j] = arr[j - step];
                j = j - step;
            }
            arr[j] = temp;
        }
        step = step / 2;
    }
}
//------------------------------------------------------

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
        int pi = partition(arr, low, high);

        // Рекурсивный вызов для сортировки двух частей
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
//-------------------------------------------------------
std::vector<int> generateRandomVector(int n, int minValue, int maxValue) {
    // Создаем генератор случайных чисел и распределение
    std::random_device rd; // Получаем случайное число от устройства
    std::mt19937 gen(rd()); // Инициализируем генератор
    std::uniform_int_distribution<> distrib(minValue, maxValue); // Установим распределение от minValue до maxValue

    std::vector<int> vec;
    vec.reserve(n); // Резервируем память под n элементов

    // Заполняем вектор случайными числами
    for (int i = 0; i < n; ++i) {
        vec.push_back(distrib(gen)); // Генерируем и добавляем случайное число
    }

    return vec;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<int> test1 = { 27, 456, 137, 100780, 9683, 8 };
    vector<int> test2 = { 27, 456, 137, 100780, 9683, 8 };
    vector<int> test3 = { 27, 456, 137, 100780, 9683, 8 };

    int n = 1000000;            // Количество чисел в векторе
    int minValue = 1;     // Минимальное значение
    int maxValue = 10000;   // Максимальное значение

    std::vector<int> randomNumbers = generateRandomVector(n, minValue, maxValue);

    // Печатаем сгенерированные случайные числа
    /*std::cout << "Случайные числа: ";
    for (int num : randomNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/

    for (int i : test1)
        cout << i << " ";
    cout << endl;

    RadixSort(test1);
    ShellSort(test2);
    quickSort(test3, 0, test3.size() - 1);

    for (int i : test1)
        cout << i << " ";
    cout << endl;

    for (int i : test2)
        cout << i << " ";
    cout << endl;

    for (int i : test3)
        cout << i << " ";
    cout << endl;

    auto execution_time = measure_execution_time(RadixSort, randomNumbers);
    //auto execution_time = measure_execution_time(quickSort, randomNumbers, 0, randomNumbers.size() -1);
    //quickSort(randomNumbers);
    /*cout << "Результат: ";
    for (int i : randomNumbers)
        cout << i << " ";
    cout << endl;*/
    std::cout << "Время выполнения: " << execution_time << " мс" << std::endl;

    return 0;
}



