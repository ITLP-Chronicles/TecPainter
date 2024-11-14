#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

enum Axis { X_AXIS, Y_AXIS, Z_AXIS, NO_AXIS };

/// Clase genérica, auto-administrable en memoria y flexible para todos los casos de uso para
/// matrices con números y fácil de usar
class Matrix {

private:
    ///Don't recommended to use publicly, just for internal use.
    Matrix(int rows, int columns, double** rawDataUnsafePointer);

public:
    ///Facilidad para indicar el número de rows que tiene
    int rows;

    ///Facilidad para indicar el número de columns que tiene
    int columns;

    /// Double dimensional array
    double** data; // Changed to avoid raw pointer

    ///Constructor
    /// Puedes iniciarlizar la clase así de simple
    /// Matrix* myMatriz = new Matrix(2,2, {{1,2},{3,4}});
    /// Indica el número de filas y columnas y consecuentemente pasa el vector bidimensional entre
    /// corchetes. Si el tamaño dado y el arreglo no concuerdan en tamaño, se dará una excepción.
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, const std::vector<std::vector<double>>& rawData);
    Matrix(const Matrix& other);
    ~Matrix();


    /// Sobrecarga de operador para multiplicar fácil con otra matriz sin usar notación específica
    /// de métodos (Facilidad)
    Matrix operator*(const Matrix& other) const;

    /// Sobrecarga de operator para multiplicar fácil con un escalar
    /// Matrix myMatriz = 3 * {{1,2,3},{4,5,6}} por ejemplo
    Matrix operator*(const double& other) const;

    Matrix& operator=(const Matrix& other);

    Matrix copy() const;
    Matrix inverse() const;

    Matrix getMinor(int row, int col) const;
    float determinant() const;

    /// Genera una matriz de tamaño cuadrático de cualquier tamaño incluyendo en la última fila
    /// los valores 0,0,..,1
    static Matrix generateGraphicableSquareMatrix(int cuadraticSize, const std::vector<std::vector<double>>& dataCruda);
    static Matrix generateIdentityMatrix(int cuadraticSize);
    static Matrix getRotationMatrix(float angle, Axis axis);

    static std::vector<std::vector<double>*>* debug(const Matrix& toDebug);
};

#endif // MATRIX_H
