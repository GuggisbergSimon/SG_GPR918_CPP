#include "pch.h"
#include <iostream>

int main()
{
	const int maxEuler = 1000;
	const int firstDivider = 3;
	const int secondDivider = 5;
	int sumTotal = 0;
	for (int i = 2; i < maxEuler; i++) {
		if (maxEuler%firstDivider == 0 || maxEuler % secondDivider == 0) {
			sumTotal += i;
		}
	}
	std::cout << "The sum of the multiples of " << firstDivider << " and " << secondDivider << 
				 " under " << maxEuler << " is : " << sumTotal << std::endl;
	system("pause");
	return 0;
}