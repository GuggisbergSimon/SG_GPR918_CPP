#include "pch.h"
#include <iostream>
#include <vector>

int main()
{
	const int NUMBER_SAMPLES = 5;
	std::vector<int> values;
	double sum = 0.0f;
	for (int i = 0; i < NUMBER_SAMPLES; i++) {
		int input = 0;
		std::cout << "Entrez un integer svp : ";
		std::cin >> input;
		values.push_back(input);
	}
	for (auto& i : values) {
		sum += i;
	}
	std::cout << "La moyenne est de " << (sum / NUMBER_SAMPLES);

	system("pause");
	return 0;
}