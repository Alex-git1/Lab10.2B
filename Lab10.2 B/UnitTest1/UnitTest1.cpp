#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.2 B/Lab10.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student students[3] = {
				{"Перший", 1, KN, 5, 5, 4},
				{"Другий", 2, PZ, 3, 4, 5},
				{"Третій", 3, IP, 4, 4, 3}
			};
			int size = 3;
			bool found = true;
			BinarySearchBySpecialtyAndGrade(students, size, PZ, 5, "Перший");
			Assert::IsTrue(found);
		}
	};
}
