#include <iostream>
#include <fstream> //Para el uso de archivos (files)
#include <string>

class FileException {
private:
    std::string message;
public:
    FileException(const std::string& msg) : message(msg) {}
    const char* what() const { return message.c_str(); }
};

class Matrix2x2 {
private:
    double matrix[2][2];
public:
    Matrix2x2() {
        // Inicializa con ceros por seguridad
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                matrix[i][j] = 0;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "[Error] Cannot open file for reading: " << filename << std::endl;
            throw FileException("File not found or cannot be opened: " + filename);
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (!(file >> matrix[i][j])) {
                    std::cout << "[Error] File read error: " << filename << std::endl;
                    throw FileException("Invalid matrix data format in file: " + filename);
                }
            }
        }

        file.close();
        std::cout << "Matrix successfully loaded from: " << filename << std::endl;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "[Error] Cannot open file for writing: " << filename << std::endl;
            throw FileException("No permission or invalid path for file: " + filename);
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
        std::cout << "Matrix successfully saved to: " << filename << std::endl;
    }

    void print() const {
        std::cout << "Matrix contents:" << std::endl;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrix2x2 matrix;
    std::string loadFilename = "nonexistent_file.txt";  // Prueba de archivo inexistente
    std::string saveFilename = "/root/matrix.txt";       // Prueba de ruta sin permisos (La mas facil es root)

    try {
        matrix.loadFromFile(loadFilename);
    }
    catch (FileException& e) {
        std::cout << "Caught exception during load: " << e.what() << std::endl;
        throw; // re-throw para simular manejo superior
    }
    catch (...) {
        std::cout << "Unknown error while loading file." << std::endl;
    }

    try {
        matrix.saveToFile(saveFilename);
    }
    catch (FileException& e) {
        std::cout << "Caught exception during save: " << e.what() << std::endl;
        throw; // re-throw para simular manejo superior
    }
    catch (...) {
        std::cout << "Unknown error while saving file." << std::endl;
    }

    return 0;
}
