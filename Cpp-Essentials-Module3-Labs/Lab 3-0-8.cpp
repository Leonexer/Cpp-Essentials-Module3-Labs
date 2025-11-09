#include <iostream>

int main(void) {
	double num = 8;
	double den = 0;

	std::cin >> den;
	try {
		if (den == 0)
		{
			throw 1;
		}
		std::cout << num/den << std::endl;
	}
	catch (int ex)
	{
		if (ex == 1)
			std::cout << "Your input is not valid, you can't divide by zero." << std::endl;
	}

	return 0;
}