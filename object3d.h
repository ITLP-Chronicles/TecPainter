#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <vector>
#include "surface.h"
#include "matrix.h"


class Object3D
{
public:
    Object3D();
    std::vector<Surface> surfaces;
    void addSurface(const Surface& toAdd);
    void transform(const Matrix& transformy);
};

#endif // OBJECT3D_H