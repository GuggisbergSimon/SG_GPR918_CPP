#include "pch.h"
#include <iostream>
#include <vector>

int input() {
	int value = 0;
	std::cout << "Entrez un integer : ";
	std::cin >> value;
	return value;
}

int& max(std::vector<int>& numbers) {
	int currentMax = 0;
	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] > numbers[currentMax]) {
			currentMax = i;
		}
	}
	return numbers[currentMax];
}

int& min(std::vector<int>& numbers) {
	int currentMin = 0;
	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] < numbers[currentMin]) {
			currentMin = i;
		}
	}
	return numbers[currentMin];
}

int main()
{
	const int NUMBER_SAMPLES = 10;
	int maximum = 0;
	int minimum = 0;
	std::vector<int> values;

	for (int i = 0; i < NUMBER_SAMPLES; i++) {
		values.push_back(input());
	}
	maximum = max(values);
	minimum = min(values);
	std::cout << "Le maximum est : " << maximum;
	std::cout << "Le minimum est : " << minimum;

	system("pause");
	return 0;
}