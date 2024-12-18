#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include "vertex.h"
#include "matrix.h"
#include "QColor"

class Surface
{
public:
    QColor color;
    std::vector<Vertex> vertices;
    Surface();
    Surface(QColor& color);

    void addVertex(const Vertex& toAdd);
    void addRectangleOnXY(float x, float y, float z, float sizex, float sizey);
    void transform(const Matrix& matrixInput);
    Surface copy() const;
};

#endif // SURFACE_H
