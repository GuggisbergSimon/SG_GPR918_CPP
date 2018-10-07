#include "pch.h"
#include <iostream>

int main()
{
	int width;
	int height;
	std::cout << "Please enter the width of the rectangle (an integer) : ";
	std::cin >> width;
	std::cout << "Please enter the height of the rectangle (an integer) : ";
	std::cin >> height;
	std::cout << "The perimeter of that rectangle is : " << ((2*width)+(2*height)) << std::endl;
	system("pause");
	return 0;
}