#include "vertex.h"
#include "point.h"

Vertex::Vertex() : point(Point(0,0,0)) {}
Vertex::Vertex(double x, double y, double z) : point(Point(x, y,z)){}
Vertex::Vertex(const Point& newPoint) : point(Point(newPoint.x, newPoint.y, newPoint.z)){}

Vertex Vertex::copy() const {
    return Vertex(this->point.x, this->point.y, this->point.z);
}
void Vertex::transform(const Matrix& matrixInput){
    this->point.transform(matrixInput);
}
