#include <iostream>

void swap(int*& ref1, int*& ref2)
{
	int* temp = std::move(ref1);
	ref1 = std::move(ref2);
	ref2 = std::move(temp);
}

void print_values(int* ptr1, int* ptr2)
{
	std::cout << "the value a is : " << *ptr1 << " and is contained in address : " << ptr1 << std::endl;
	std::cout << "the value b is : " << *ptr2 << " and is contained in address : " << ptr2 << std::endl;
}

int main()
{
	int a = 4;
	int b = 3;
	int* ptrA = &a;
	int* ptrB = &b;
	print_values(ptrA, ptrB);
	swap(ptrA, ptrB);
	print_values(ptrA, ptrB);

	system("pause");
	return 0;
}
