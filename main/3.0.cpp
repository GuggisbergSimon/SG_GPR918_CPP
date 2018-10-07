#include "pch.h"
#include <iostream>

int main()
{
	int numberInput;
	std::cout << "I can count until : ";
	std::cin >> numberInput;
	for (int i = 0; i <= numberInput; i++) {
		std::cout << i << std::endl;
	}
	system("pause");
	return 0;
}