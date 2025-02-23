#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication_UnitTests_hw1/Stack.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTime
{
	TEST_CLASS(UnitTestTime)
	{

	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 1000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
			
		}
		TEST_METHOD(TestMethod2)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 10000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod3)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 100000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod4)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 1000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod5)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 2000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod6)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 3000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod7)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 4000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod8)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 10000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod9)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 20000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}
		TEST_METHOD(TestMethod10)
		{
			std::stack <int> st;
			int i = 0;
			while (i != 50000000) {
				st.push(i);
				i++;
			}
			auto execution_time = measure_execution_time(find_element, st, 5);
		}

	};
}
