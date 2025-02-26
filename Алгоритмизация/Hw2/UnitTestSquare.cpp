#include "pch.h"
#include "CppUnitTest.h"
#include "../Hw2/Hw2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSquare
{
	TEST_CLASS(UnitTestSquare)
	{

	public:

		TEST_METHOD(TestMethod1)
		{
			int num_points(100);
			double result = monte_carlo_circle_area(num_points);
			Assert::AreEqual(1.2788, result, 0.001, L"значения совпали с точностью: ");
		}

		TEST_METHOD(TestMethod2)
		{
			int num_points(10000);
			double result = monte_carlo_circle_area(num_points);
			Assert::AreEqual(1.2788, result, 0.001, L"значения совпали с точностью: ");
		}

		TEST_METHOD(TestMethod3)
		{
			int num_points(200000000);
			double result = monte_carlo_circle_area(num_points);
			Assert::AreEqual(1.2788, result, 0.0001, L"значения совпали с точностью: ");
		}
	};
}
