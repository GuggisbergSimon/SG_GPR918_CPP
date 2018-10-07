#include "pch.h"
#include <iostream>
#include <string>

int main()
{
	int numberInput = 0;
	do {
		std::string textInput;
		std::cout << "Enter an integer : ";
		std::cin >> textInput;
		numberInput = stoi(textInput);
		if (numberInput == 0 || numberInput == 1) {
			std::cout << "NO, The number entered is either 0 or 1, which are not prime." << std::endl;
		}
		else {
			bool isPrime = true;
			for (int i = 2; i < numberInput; i++) {
				//checks if the number is prime and sets i so that it exits the loop as soon as possible
				if (numberInput%i == 0) {
					isPrime = false;
					i = numberInput;
				}
			}
			if (isPrime) {
				std::cout << "YES, the number entered is a prime." << std::endl;
			}
			else {
				std::cout << "NO, the number entered is not a prime." << std::endl;
			}
		}
	} while (numberInput != -1);
	system("pause");
	return 0;
}