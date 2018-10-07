#include "pch.h"
#include <iostream>
#include <string>

int main()
{
	std::string textInput;
	std::cout << "Enter an integer : ";
	std::cin >> textInput;
	int numberInput = stoi(textInput);
	if (numberInput % 2 == 0) {
		std::cout << "This number is even." << std::endl;
	}
	else {
		std::cout << "This number is odd." << std::endl;
	}
	system("pause");
	return 0;
}