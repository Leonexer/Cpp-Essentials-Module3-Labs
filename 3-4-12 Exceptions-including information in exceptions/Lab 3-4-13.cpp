#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

class InvalidIPException {
public:
    InvalidIPException(const std::string& message) : msg(message) {}
    const char* what() const { return msg.c_str(); }
private:
    std::string msg;
};

class IPHeader {
public:
    IPHeader(const std::string& IPSource, const std::string& IPDestination, const std::string& otherData)
        : IPSource(IPSource), IPDestination(IPDestination), otherData(otherData)
    {
        check(IPSource, "Source");
        check(IPDestination, "Destination");
    }

private:
    void check(const std::string& address, const std::string& type) const {
        std::stringstream parts(address);
        std::string part;
        int count = 0;

        while (std::getline(parts, part, '.')) {
            if (part.empty() || part.length() > 3) {
                throw InvalidIPException("Invalid " + type + " IP Address - wrong format.");
            }

            for (char c : part) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw InvalidIPException("Invalid " + type + " IP Address - only digits and dots allowed.");
                }
            }

            int value = std::stoi(part);
            if (value < 0 || value > 255) {
                throw InvalidIPException("Invalid " + type + " IP Address - number out of range (0–255).");
            }

            if (++count > 4) {
                throw InvalidIPException("Invalid " + type + " IP Address - too many parts.");
            }
        }

        if (count != 4) {
            throw InvalidIPException("Invalid " + type + " IP Address - incorrect parts count.");
        }
    }

    std::string IPSource, IPDestination, otherData;
};

int main() {
    std::string inputSourceIP;
    std::string inputDestinationIP;

    std::getline(std::cin, inputSourceIP);
    std::getline(std::cin, inputDestinationIP);

    try {
        IPHeader headerValid(inputSourceIP, inputDestinationIP, "data");
        std::cout << "Valid IP Header." << std::endl;
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Invalid IP Header - " << ex.what() << std::endl;
    }

    std::getline(std::cin, inputSourceIP);
    std::getline(std::cin, inputDestinationIP);

    try {
        IPHeader headerInvalid(inputSourceIP, inputDestinationIP, "data");
        std::cout << "Valid IP Header." << std::endl;
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Invalid IP Header - " << ex.what() << std::endl;
    }

    return 0;
}
