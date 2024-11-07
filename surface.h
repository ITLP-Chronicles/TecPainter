#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include "vertex.h"
#include "matrix.h"

class Surface
{
public:
    std::vector<Vertex> vertices;
    Surface();

    void addVertex(const Vertex& toAdd);
    void transform(const Matrix& matrixInput);
};

#endif // SURFACE_H
