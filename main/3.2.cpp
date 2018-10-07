#include "pch.h"
#include <iostream>

int main()
{
	const int maxEuler = 4'000'000;
	int iMinusTwo = 0;
	int iMinusOne = 0;
	int sumTotal = 0;
	for (int i = 1; i < maxEuler; i = iMinusOne + iMinusTwo) {
		if (i % 2 == 0) {
			sumTotal += i;
		}
		iMinusTwo = iMinusOne;
		iMinusOne = i;
	}
	std::cout << "The sum of even numbers of Fibonnaci sequence up until " << maxEuler << " is : " << sumTotal << std::endl;
	system("pause");
	return 0;
}