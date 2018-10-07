#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	int radius;
	std::cout << "Please enter the radius of the circle (an integer) : ";
	std::cin >> radius;
	std::cout << "The perimeter of that circle is : " << (2 * M_PI*radius) << std::endl;
	system("pause");
	return 0;
}