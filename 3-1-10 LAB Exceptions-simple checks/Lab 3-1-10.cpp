#include <iostream>
#include <vector>


// Custom exception for matrix errors
class MatrixException : public std::exception {
    std::string message;
public:
    MatrixException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Matrix class
class Matrix {
private:
    std::vector<std::vector<float>> data;
    int rows, cols;

public:
    // Constructor
    Matrix(int r, int c) {
        if (r <= 0 || c <= 0)
            throw MatrixException("Matrix dimensions must be positive.");
        rows = r;
        cols = c;
        data.assign(r, std::vector<float>(c, 0));
    }

    // Fill the matrix with a given value
    void fill(float value) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = value;
    }

    // Add a value to every element in the matrix
    void addValue(float value) {
        if (data.empty())
            throw MatrixException("Matrix is empty. Cannot add value.");
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] += value;
    }

    // Add another matrix to this matrix
    Matrix addMatrix(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw MatrixException("Matrix sizes do not match for addition.");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Print the matrix
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

// Main function for testing
int main() {
    try {
        Matrix A(2, 2);
        Matrix B(2, 2);
        Matrix C(3, 3);

        A.fill(1.5);
        B.fill(2.0);
        C.fill(3.0);

        std::cout << "Matrix A:" << std::endl; A.print();
        std::cout << "Matrix B:" << std::endl; B.print();
        std::cout << "Matrix C:" << std::endl; C.print();

        std::cout << "\nAdding A + B:" << std::endl;
        Matrix AB = A.addMatrix(B);
        AB.print();

        std::cout << "\nAdding A + C (should throw exception):" << std::endl;
        Matrix AC = A.addMatrix(C); // size mismatch
        AC.print();
    }
    catch (const MatrixException& e) {
        std::cout << "Matrix error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "General error: " << e.what() << std::endl;
    }

    return 0;
}
