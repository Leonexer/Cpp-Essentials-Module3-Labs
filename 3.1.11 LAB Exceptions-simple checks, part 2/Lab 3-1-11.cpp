#include <iostream>
#include <string>

class BoundaryException {
private:
    std::string message;
public:
    BoundaryException(const std::string& msg) : message(msg) {}
    const char* what() const { return message.c_str(); }
};

class LimitedValue {
private:
    int value;
    int minLimit;
    int maxLimit;

public:
    LimitedValue(int initial, int minL, int maxL)
        : value(initial), minLimit(minL), maxLimit(maxL)
    {
        if (minL >= maxL)
            throw BoundaryException("Invalid limits: minimum must be less than maximum.");
        if (initial < minL || initial > maxL)
            throw BoundaryException("Initial value out of limits.");
    }

    void add(int amount) {
        if (value + amount > maxLimit)
            throw BoundaryException("Addition exceeds upper limit!");
        value += amount;
    }

    void subtract(int amount) {
        if (value - amount < minLimit)
            throw BoundaryException("Subtraction goes below lower limit!");
        value -= amount;
    }

    void print() const {
        std::cout << "Current value: " << value
            << " (Limits: " << minLimit
            << " to " << maxLimit << ")" << std::endl;
    }
};

int main() {
    try {
        LimitedValue counter1(10, 0, 20);
        LimitedValue counter2(5, -5, 10);

        std::cout << "Initial values:" << std::endl;
        counter1.print();
        counter2.print();

        std::cout << "\nTesting counter1:" << std::endl;
        counter1.add(5);
        counter1.print();

        // Primera prueba de excepcion (excede 20)
        counter1.add(10);

        std::cout << "\nTesting counter2:" << std::endl;
        counter2.subtract(3);
        counter2.print();

        // Segunda prueba de excepcion (bajo -5)
        counter2.subtract(10);
    }
    catch (BoundaryException& e) {
        std::cout << "Boundary error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error occurred." << std::endl;
    }

    std::cout << "\nProgram ended..." << std::endl;
    return 0;
}
