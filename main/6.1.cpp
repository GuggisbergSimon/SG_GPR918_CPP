#include "pch.h"
#include <iostream>
#include <vector>

int input() {
	int value = 0;
	std::cout << "Entrez un integer : ";
	std::cin >> value;
	return value;
}

int max(std::vector<int>& numbers) {
	int currentmax = numbers[0];
	for (auto& value : numbers) {
		if (value > currentmax) {
			currentmax = value;
		}
	}
	return currentmax;
}

int min(std::vector<int>& numbers) {
	int currentmin = numbers[0];
	for (auto& value : numbers) {
		if (value < currentmin) {
			currentmin = value;
		}
	}
	return currentmin;
}

int main()
{
	const int NUMBER_SAMPLES = 10;
	std::vector<int> values;

	for (int i = 0; i < NUMBER_SAMPLES; i++) {
		values.push_back(input());
	}
	std::cout << "Le maximum est : " << max(values);
	std::cout << "Le minimum est : " << min(values);

	system("pause");
	return 0;
}