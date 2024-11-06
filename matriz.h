#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

/// Clase genérica, auto-administrable en memoria y flexible para todos los casos de uso para
/// matrices con números y fácil de usar
class Matriz {
public:
    ///Facilidad para indicar el número de filas que tiene
    int filas;

    ///Facilidad para indicar el número de columnas que tiene
    int columnas;
    std::vector<std::vector<float>> data; // Changed to avoid raw pointer

    ///Constructor
    /// Puedes iniciarlizar la clase así de simple
    /// Matriz* myMatriz = new Matriz(2,2, {{1,2},{3,4}});
    /// Indica el número de filas y columnas y consecuentemente pasa el vector bidimensional entre
    /// corchetes. Si el tamaño dado y el arreglo no concuerdan en tamaño, se dará una excepción.
    Matriz(int filas, int columnas);
    Matriz(int filas, int columnas, const std::vector<std::vector<float>>& dataCruda);

    /// Sobrecarga de operador para multiplicar fácil con otra matriz sin usar notación específica
    /// de métodos (Facilidad)
    Matriz operator*(const Matriz& other) const;

    /// Sobrecarga de operator para multiplicar fácil con un escalar
    /// Matriz myMatriz = 3 * {{1,2,3},{4,5,6}} por ejemplo
    Matriz operator*(const double& other) const;

    Matriz clonar() const;

    /// Genera una matriz de tamaño cuadrático de cualquier tamaño incluyendo en la última fila
    /// los valores 0,0,..,1
    static Matriz generarMatrizGraficableCuadrada(int cuadraticSize, const std::vector<std::vector<int>>& dataCruda);
};

#endif // MATRIZ_H
