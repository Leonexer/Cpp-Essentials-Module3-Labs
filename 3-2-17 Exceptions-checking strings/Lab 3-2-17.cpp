#include <iostream>
#include <string>

class InvalidIPException {
public:
    InvalidIPException(const std::string& message) : msg(message) {}
    const char* what() const { return msg.c_str(); }
private:
    std::string msg;
};

class IPAddress {
private:
    int octets[4];

    bool isValidIP(const std::string& ip) {
        int parts = 0;
        std::string temp;
        for (char c : ip) {
            if (c == '.') {
                if (temp.empty()) return false;
                int val = std::stoi(temp);
                if (val < 0 || val > 255) return false;
                temp.clear();
                parts++;
            }
            else if (isdigit(c)) {
                temp += c;
            }
            else {
                return false;
            }
        }
        if (!temp.empty()) {
            int val = std::stoi(temp);
            if (val < 0 || val > 255) return false;
            parts++;
        }
        return parts == 4;
    }

public:
    IPAddress(const std::string& ip) {
        if (!isValidIP(ip)) {
            throw InvalidIPException("Invalid IP address format: " + ip);
        }
        int idx = 0;
        std::string temp;
        for (char c : ip) {
            if (c == '.') {
                octets[idx++] = std::stoi(temp);
                temp.clear();
            }
            else {
                temp += c;
            }
        }
        octets[idx] = std::stoi(temp);
    }

    void printSubnet(int range) const {
        if (range != 1 && range != 2 && range != 4 && range != 8 && range != 16 &&
            range != 32 && range != 64 && range != 128 && range != 256) {
            throw InvalidIPException("Invalid subnet range: must be a power of 2 between 1 and 256.");
        }

        // Calcular bits sin usar <cmath>
        int bits = 0;
        int temp = range;
        while (temp > 1) {
            temp /= 2;
            bits++;
        }
        int mask = 32 - bits;

        std::cout << "IP: "
            << octets[0] << '.' << octets[1] << '.' << octets[2] << '.' << octets[3]
            << " /" << mask << std::endl;
    }
};

int main() {
    try {
        IPAddress ip1("192.168.1.10");
        ip1.printSubnet(64);

        IPAddress ip2("10.0.0.256"); // Prueba de IP inválida
        ip2.printSubnet(32);
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    try {
        IPAddress ip3("172.16.0.5");
        ip3.printSubnet(7); // Prueba de rango inválido
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
