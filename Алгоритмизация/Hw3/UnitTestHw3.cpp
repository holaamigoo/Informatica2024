#include "pch.h"
#include "CppUnitTest.h"
#include "../Hw3/Hw3.cpp"
#include <vector>
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHw3 {
    // Функция для превращения std::vector<int> в std::wstring
    std::wstring ToString(const std::vector<int>& vec) {
        std::wostringstream ss;
        ss << L"[ ";
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << vec[i];
            if (i < vec.size() - 1) {
                ss << L", ";
            }
        }
        ss << L" ]";
        return ss.str();
    }

    TEST_CLASS(UnitTestHw3) {
public:
    std::vector<int> sortedTest = { 8, 27, 137, 456, 9683, 100780 };
    TEST_METHOD(TestMethodRadixSort) {
        
        std::vector<int> test1 = { 27, 456, 137, 100780, 9683, 8 };
        RadixSort(test1);
        Assert::AreEqual(ToString(sortedTest), ToString(test1));

    }

    TEST_METHOD(TestMethodShellSort) {
        std::vector<int> test2 = { 27, 456, 137, 100780, 9683, 8 };
        ShellSort(test2);
        Assert::AreEqual(ToString(sortedTest), ToString(test2));

    }

    TEST_METHOD(TestMethodquickSort) {
        std::vector<int> test3 = { 27, 456, 137, 100780, 9683, 8 };
        quickSort(test3, 0, test3.size() - 1);
        Assert::AreEqual(ToString(sortedTest), ToString(test3));

    }
    };
}

