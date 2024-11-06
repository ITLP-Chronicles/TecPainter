#include "matriz.h"
#include <stdexcept>


/// Inicia la matriz en 0's
Matriz::Matriz(int rows, int columns)
    : filas(rows), columnas(columns), data(rows, std::vector<int>(columns, 0)) {}

Matriz::Matriz(int rows, int columns, const std::vector<std::vector<int>>& rawData)
    : filas(rows), columnas(columns), data(rawData) {
    if (rawData.empty() || (int)rawData.size() != rows || (int)rawData[0].size() != columns) {
        throw std::invalid_argument("Invalid dimensions for raw data.");
    }
}

Matriz Matriz::operator*(const Matriz& other) const {
    if (this->columnas != other.filas) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matriz result(this->filas, other.columnas);

    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < other.columnas; j++) {
            result.data[i][j] = 0; // Initialize to 0
            for (int k = 0; k < this->columnas; k++) {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matriz Matriz::operator*(const double& scalar) const {
    Matriz result = this->clonar();

    for (auto& row : result.data) {
        for (auto& element : row)
            element *= scalar;
    }

    return result;
}


Matriz Matriz::clonar() const {
    return Matriz(filas, columnas, data); // Utilize the constructor for cloning
}

Matriz Matriz::generarMatrizGraficableCuadrada(int cuadraticSize, const std::vector<std::vector<int>>& rawData){
    if (cuadraticSize <= 1) throw std::invalid_argument("Invalid cuadratic size");

    ///Las dimensiones tienen que concordar para que quepa el 0,0,...1 como última fila
    if (rawData.empty() || ((int)rawData.size() != cuadraticSize - 1 && (int)rawData[0].size() != cuadraticSize))
        throw std::invalid_argument("Dimensions of matrix to create a graphicable matrix are invalid");

    std::vector<std::vector<int>> copy(rawData);

    std::vector<int> ultimaFila(cuadraticSize - 1, 0);
    ultimaFila.push_back(1);

    copy.push_back(ultimaFila);

    return Matriz(cuadraticSize, cuadraticSize, copy);
}
