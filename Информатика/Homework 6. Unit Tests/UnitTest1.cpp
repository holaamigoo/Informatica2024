#include "pch.h"
#include "CppUnitTest.h"
#include "../UnitTestProject/Task.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		float x = 0;
		float y = 5;
		float R = pow(abs(sin(x) / y), 0.25);
		float S = log10(pow(2, y));
		TEST_METHOD(TestPositiveNumbers)
		{
			/*Assert::AreEqual(Func(1.0f, 3.0f), 5.00f);*/
			Assert::AreEqual(Func(1.0f, 3.0f), 0.90309f);
		}

		TEST_METHOD(TestNegativeNumbers)
		{
			Assert::AreEqual(Func(-30.0f, -2.0f), 0.838369f);
		}

		TEST_METHOD(TestDivisionByZero)
		{
			auto function = [] { Func(1.0f, 0.0f); };
			Assert::ExpectException<std::invalid_argument>(function);
		}

		TEST_METHOD(IsSMaximum)
		{
			Assert::IsTrue(Func(x, y) > R);
		}
	};
}
