#ifndef VERTEX_H
#define VERTEX_H
#include "point.h"
#include "matrix.h"

class Vertex
{
public:
    double x;
    double y;
    double z;

    Vertex();
    Vertex(double x, double y, double z);
    Vertex(const Point& point);

    Vertex copy() const;
    void transform(const Matrix& matrixTransform);
};

#endif // VERTEX_H
