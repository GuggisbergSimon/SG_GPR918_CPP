#include "pch.h"
#include <iostream>

int main()
{
	double numberInput;
	std::cout << "Enter a number : ";
	std::cin >> numberInput;
	if (numberInput < 0) {
		std::cout << "ERROR, the entered number is negative." << std::endl;
	}
	else {
		std::cout << pow(numberInput, 0.5) << std::endl;
	}
	system("pause");
	return 0;
}