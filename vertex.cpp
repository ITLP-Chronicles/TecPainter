#include "vertex.h"
#include "point.h"

Vertex::Vertex() : x(0), y(0), z(0) {}
Vertex::Vertex(double x, double y, double z) : x(x), y(y), z(z){}
Vertex::Vertex(const Point& newPoint) : x(newPoint.x), y(newPoint.y), z(newPoint.z){}

Vertex Vertex::copy() const {
    return Vertex(x,y,z);
}
void Vertex::transform(const Matrix& matrixInput){
    Matrix thisToMatrix(4,1, {{this->x}, {this->y}, {this->z}, {1}});
    Matrix result = matrixInput * thisToMatrix;
    this->x = result.data[0][0];
    this->y = result.data[1][0];
    this->z = result.data[2][0];
}
