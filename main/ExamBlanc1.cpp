#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	double radius = 0;
	std::cout << "please enter the radius of a sphere : ";
	std::cin >> radius;
	std::cout << "the surface of this sphere is : " << (4.0 * M_PI * pow(radius, 2)) <<
		" and the volume of this sphere is : " << ((4.0 / 3.0) * M_PI * pow(radius, 3)) << std::endl;

	system("pause");
	return 0;
}
