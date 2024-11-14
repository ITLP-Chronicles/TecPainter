#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <vector>
#include "surface.h"
#include "matrix.h"

class Object3D
{
public:
    float degreesX;
    float degreesY;
    float degreesZ;
    Object3D();
    std::vector<Surface> surfaces;
    void addSurface(const Surface& toAdd);
    void transform(const Matrix& transformy);
    void addPrism(float x, float y, float z, float width, float height, float depth);
    void addPrism(int x, int y, int z, int xDif, int yDif, int zDif, QColor& color);
    Vertex calculateCentroid() const;
    void rotate(float angle, Axis axis, Vertex center);

    Object3D* copy();
};

#endif // OBJECT3D_H
