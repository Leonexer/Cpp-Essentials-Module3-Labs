#include <iostream>

class DivideByZeroException : public std::exception {
public:
    static const char* what() 
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

int main() {
    double numerator;
    double denominator;

    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        if (denominator == 0) {
            throw DivideByZeroException();
        }
        std::cout << "Result: " << numerator / denominator << std::endl;
    }
    catch (const DivideByZeroException& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}
