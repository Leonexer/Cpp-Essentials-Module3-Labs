#include <iostream>

using namespace std;
//add your own exception class here
class NegativeValuesException : public std::exception {
public:
	const char* what()
	{
		return "Your input is not valid, this parameter does not allow negative values.";
	}
};
//add functions code here

float square_area(float side)
{
	if (side < 0) throw NegativeValuesException();
	return side * side;
}

float rectangle_area(float side, float height) 
{
	if (side < 0 || height < 0) throw NegativeValuesException();
	return side * height;
}

int main(void) {
	float side, height, result;
	cin >> side;
	cin >> height;
	try
	{
		float rsquare = square_area(side);
		float rrectangle = rectangle_area(side, height);
		cout << rsquare << endl << rrectangle << endl;
	}
	//add a suitable catch block here
	catch (std::exception &exc) {
		std::cout << exc.what() << std::endl;
	}
	return 0;
}