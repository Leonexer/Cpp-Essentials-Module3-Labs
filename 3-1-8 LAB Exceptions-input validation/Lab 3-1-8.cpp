#include <iostream>

class DivideByZeroException : public std::exception {
public:
    const char* what()
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

float internaldiv(float arg1, float arg2) // Código base de Cisco
{
    if (0 == arg2)
        throw DivideByZeroException();
    return arg1 / arg2;
}

float divide(float num, float den)
{
    if (den == 0) // Valida los argumentos para la excepcion
        throw DivideByZeroException(); 
    return num / den;  
}

float divide2(float num, float den) {
    try
    {
        return internaldiv(num, den); // La excepcion se valida dentro de la funcion interna
    }
    catch (int ex)
    {
        throw ex;
    }

}


int main()
{
    double numerator;
    double denominator;

    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        float result = divide(numerator, denominator); 
        std::cout << result << std::endl;
    }
    catch (const char* exc) 
    {
        std::cout << "Error: " << exc << std::endl;
    }

    try {
        float result = divide2(numerator, denominator);
        std::cout << result << std::endl;
    }
    catch (const char* exc)
    {
        std::cout << "Error: " << exc << std::endl;
    }

    return 0;
}
