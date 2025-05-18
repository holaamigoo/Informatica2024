#include "pch.h"
#include "CppUnitTest.h"
#include "../Hw7/Backtrack3.cpp"
#include "../Hw7/Divide5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHw7backtrak
{
	TEST_CLASS(UnitTestHw7backtrak)
	{
	public:
		
        TEST_METHOD(TestSubsetExists)
        {
            vector<int> nums = { 2, 4, 6, 9 };
            int k = 13;
            bool result = canSumToK(nums, k, 0);
            Assert::IsTrue(result, L"Подмножество должно существовать");
        }

        TEST_METHOD(TestSubsetNotExists)
        {
            vector<int> nums = { 1, 2, 4 };
            int k = 10;
            bool result = canSumToK(nums, k, 0);
            Assert::IsFalse(result, L"Подмножество не должно существовать");
        }

        TEST_METHOD(TestBasicInversions)
        {
            vector<int> arr = { 2, 4, 1, 3, 5 };
            long long expected = 3;
            long long actual = mergeSortAndCount(arr, 0, arr.size() - 1);
            Assert::AreEqual(expected, actual, L"������ ���� 3 ��������");
        }

        TEST_METHOD(TestMaxInversions)
        {
            vector<int> arr = { 5, 4, 3, 2, 1 };
            long long expected = 10; // n*(n-1)/2 ��� n=5
            long long actual = mergeSortAndCount(arr, 0, arr.size() - 1);
            Assert::AreEqual(expected, actual, L"������ ���� 10 ��������");
        }
	};
}
