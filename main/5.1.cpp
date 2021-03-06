#include "pch.h"
#include <iostream>
#include <vector>

std::vector<int> fib(int n)
{
	std::vector<int> fibon;
	fibon.push_back(0);

	if (n == 0) {
		return fibon;
	}
	fibon.push_back(1);
	if (n == 1) {
		return fibon;
	}
	for (int i = 2; i < n; i++) {
		fibon.push_back(fibon[i - 2] + fibon[i - 1]);
	}
	return fibon;
}

int main()
{
	std::vector<int> fibo;
	int nImput = 0;
	std::cout << "Je souhaite connaitre le nombre de fibonnaci n : ";
	std::cin >> nImput;
	fibo = fib(nImput);
	for (auto& i : fibo) {
		std::cout << i << std::endl;
	}
	return 0;
}