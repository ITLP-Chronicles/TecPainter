#include "matrix.h"
#include <stdexcept>
#include <math.h>

/// Private
/// Create a quick matrix without validate anything Possible DANGEROUS
/// Doesn't validate anything, just creates a quick matrix. For internal use only
Matrix::Matrix(int rows, int columns, double** rawDataUnsafe):rows(rows), columns(columns){
    this->data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        this->data[i] = new double[columns];
        for (int j = 0; j < columns; ++j) {
            this->data[i][j] = rawDataUnsafe[i][j];
        }
    }
}

///Public

/// Creates an empty matrix filled with 0's
Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns){
    this->data = new double*[rows];

    for (int i = 0; i < rows; i++)
        this->data[i] = new double[columns]();
}

Matrix::Matrix(int rows, int columns, const std::vector<std::vector<double>>& rawData) : rows(rows), columns(columns){
    if (rawData.empty() || (int)rawData.size() != rows || (int)rawData[0].empty() || (int)rawData[0].size() != columns) {
        throw std::invalid_argument("Invalid dimensions for raw data.");
    }

    this->data = new double*[this->rows];

    for (int i = 0; i < this->rows; i++){
        this->data[i] = new double[this->columns]();
        for (int j = 0; j < this->columns; j++){
            data[i][j] = rawData[i][j];
        }
    }
}

Matrix::~Matrix(){
    for (int actualRow = 0; actualRow < this->rows; ++actualRow) {
        delete[] this->data[actualRow];
    }
    delete[] this->data;
}

Matrix Matrix::operator*(const Matrix& other) const {
    //This matrix * otherMatrix. From left to right

    if (this->columns != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(this->rows, other.columns);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            result.data[i][j] = 0; // Initialize to 0 (maybe not neccesary)
            for (int k = 0; k < this->columns; k++) {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator*(const double& scalar) const {
    Matrix result = this->copy();

    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.columns; ++j) {
            result.data[i][j] *= scalar;
        }
    }

    return result;
}


Matrix Matrix::copy() const {
    return Matrix(this->rows, this->columns, this->data); // Utilize the constructor for cloning
}

Matrix Matrix::generateGraphicableSquareMatrix(int cuadraticSize, const std::vector<std::vector<double>>& rawData) {
    if (cuadraticSize <= 1)
        throw std::invalid_argument("Invalid cuadratic size");

    // Validate the dimensions: the rawData should have one less row than the cuadratic size,
    // and the number of columns should match the cuadratic size
    if (rawData.empty() || ((int)rawData.size() != cuadraticSize - 1) || (int)rawData[0].size() != cuadraticSize) {
        throw std::invalid_argument("Dimensions of matrix to create a graphicable matrix are invalid");
    }

    // Make a copy of the rawData
    std::vector<std::vector<double>> copy(rawData);

    // Create the last row (cuadraticSize-1 zeroes followed by a 1)
    std::vector<double> ultimaFila(cuadraticSize - 1, 0); ultimaFila.push_back(1);

    // Add the last row to the copied data
    copy.push_back(ultimaFila);

    // Return a new Matrix, passing the validated data
    return Matrix(cuadraticSize, cuadraticSize, copy);
}

Matrix Matrix::generateIdentityMatrix(int cuadraticSize) {
    if (cuadraticSize <= 1)
        throw std::invalid_argument("Invalid cuadratic size");

    std::vector<std::vector<double>> data;
    for (int i = 0; i < cuadraticSize; ++i) {
        std::vector<double> row;
        data.push_back(row);
        for (int j = 0; j < cuadraticSize; ++j) {
            if (i == j) data.at(i).push_back(1);
            else data.at(i).push_back(0);
        }
    }

    return Matrix(cuadraticSize, cuadraticSize, data);
}

std::vector<std::vector<double>*>* Matrix::debug(const Matrix& toDebug) {
    auto v = new std::vector<std::vector<double>*>();

    for (int i = 0; i < toDebug.rows; ++i) {
        // Create a new vector for each row and push it to the outer vector
        v->push_back(new std::vector<double>());

        for (int j = 0; j < toDebug.columns; ++j) {
            // Add data to the inner vector (use push_back, not a())
            v->at(i)->push_back(toDebug.data[i][j]);
        }
    }

    return v;
}

Matrix::Matrix(const Matrix& other) {
    // Suponiendo que tu clase Matrix tiene un arreglo 2D `data`
    this->rows = other.rows;
    this->columns = other.columns;
    this->data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        this->data[i] = new double[columns];
        for (int j = 0; j < columns; ++j) {
            this->data[i][j] = other.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    // Avoid self-assignment
    if (this != &other) {
        // Delete the old data to avoid memory leak
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->data[i];
        }
        delete[] this->data;

        // Allocate new memory for the data
        this->rows = other.rows;
        this->columns = other.columns;
        this->data = new double*[this->rows];

        // Copy the data from the other matrix
        for (int i = 0; i < this->rows; ++i) {
            this->data[i] = new double[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::getRotationMatrix(float angle, Axis axis) {
    switch (axis) {
    case X_AXIS:

        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {1, 0,        0,         0},
                                                           {0, cos(angle), -sin(angle), 0},
                                                           {0, sin(angle), cos(angle),  0}});
    case Y_AXIS:

        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {cos(angle), 0, sin(angle), 0},
                                                           {0,        1, 0,        0},
                                                           {-sin(angle), 0, cos(angle), 0}});
    case Z_AXIS:

        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {cos(angle), -sin(angle), 0, 0},
                                                           {sin(angle), cos(angle),  0, 0},
                                                           {0,        0,         1, 0}});
    case NO_AXIS:
        return Matrix::generateIdentityMatrix(4);
    }
}
