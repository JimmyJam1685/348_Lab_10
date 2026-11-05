/*
Lab 10
Author: James Orrick
C++ Practices w/ matrixes
Created: 11/5/2026
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

class Matrix {
private:
    int rows;
    int cols;
    double** data; // Pointer to a 2D array for matrix data

public:
    // Practice 1: Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw std::invalid_argument("Matrix dimensions must be positive.");
        }
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols]();
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            Matrix copy(other);
            std::swap(rows, copy.rows);
            std::swap(cols, copy.cols);
            std::swap(data, copy.data);
        }
        return *this;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    // Data Input function
    void input(std::ifstream& file, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> data[i][j])) {
                    throw std::runtime_error("Not enough matrix data in file");
                }
            }
        }
    }



    // Practice 1: Display matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Practice 2:Overload the + operator for matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Practice 3: Overload the * operator for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices cannot be multiplied due to incompatible dimensions.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Practice 4: Sum of diagonal elements
    double sumDiagonal() const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix must be square to calculate diagonal sum.");
        }
        double sum = 0;
        for (int i = 0; i < rows; ++i) {
            sum += data[i][i];
        }
        return sum;
    }

    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
            throw std::out_of_range("Row indices are out of range.");
        }
        for (int j = 0; j < cols; ++j) {
            std::swap(data[row1][j], data[row2][j]);
        }
    }

    void swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= cols || col2 < 0 || col2 >= cols) {
            throw std::out_of_range("Column indices are out of range.");
        }
        for (int i = 0; i < rows; ++i) {
            std::swap(data[i][col1], data[i][col2]);
        }
    }

    void editElement(int row, int col, double newValue) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Row or column indices are out of range.");
        }
        data[row][col] = newValue;
    }
};

//Practice 1: Matrix Input function
std::pair<Matrix, Matrix> matrixInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file"); // Handle file opening error
    }
    int size;
    if (!(file >> size) || size <= 0) {
        throw std::runtime_error("Invalid matrix size");
    }
    Matrix matrixA(size, size); // Creates Matrix A with the specified size
    matrixA.input(file,size); // Reads data for Matrix A from the file
    Matrix matrixB(size, size);
    matrixB.input(file,size);
    return std::make_pair(matrixA, matrixB); // Returns a pair of matrices
}

// Practice 5: Swap two rows of a matrix and display the result while keeping the original matrix intact
void swapRows(Matrix& matrix, int row1, int row2) {
    matrix.swapRows(row1, row2);
    matrix.display(); // Display the matrix after swapping rows
}

// Practice 6: Swap two columns of a matrix and display the result while keeping the original matrix intact
void swapColumns(Matrix& matrix, int col1, int col2) {
    matrix.swapColumns(col1, col2);
    matrix.display(); // Display the matrix after swapping columns
}

// Practice 7: edit a specific index in the matrix permanently
void editElement(Matrix& matrix, int row, int col, double newValue) {
    matrix.editElement(row, col, newValue);
    matrix.display(); // Display the matrix after editing the element
}


int main(int argc, char* argv[]) {
    try {
        const std::string filename = argc > 1 ? argv[1] : "matrix.txt";
        std::pair<Matrix, Matrix> matrices = matrixInput(filename); // Read matrices from file
        Matrix& matrixA = matrices.first;
        Matrix& matrixB = matrices.second;
        std::cout << "Matrix A:" << std::endl;
        matrixA.display();
        std::cout << "Matrix B:" << std::endl;
        matrixB.display();

        // Practice 2: Matrix Addition
        Matrix sumMatrix = matrixA + matrixB;
        std::cout << "Sum of Matrix A and B:" << std::endl;
        sumMatrix.display();

        // Practice 3: Matrix Multiplication
        Matrix productMatrix = matrixA * matrixB;
        std::cout << "Product of Matrix A and B:" << std::endl;
        productMatrix.display();

        // Practice 4: Sum of diagonal elements
        double diagonalSum = matrixA.sumDiagonal();
        std::cout << "Sum of diagonal elements of Matrix A: " << diagonalSum << std::endl;

        // Practice 5: Swap rows
        swapRows(matrixA, 0, 1); // Swap first and second rows of Matrix A

        // Practice 6: Swap columns
        swapColumns(matrixA, 0, 1); // Swap first and second columns of Matrix A

        // Practice 7: Edit a specific index in the matrix
        editElement(matrixA, 0, 0, 99.0); // Change the element at (0,0) to 99.0

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Handle exceptions
    }

    return 0;
}