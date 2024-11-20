#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <vector>
#include "surface.h"
#include "matrix.h"
#include "line.h"

class Object3D
{
public:
    Object3D();
    ~Object3D();
    Line* ejex;
    Line* ejey;
    Line* ejez;
    float x, y, z;
    float sizex, sizey, sizez;
    std::vector<Surface> surfaces;
    std::vector<Surface> originalSurfaces;
    void addSurface(const Surface& toAdd);
    void transform(const Matrix& transformy);
    void addPrism(float x, float y, float z, float width, float height, float depth);
    void addPrism(int x, int y, int z, int xDif, int yDif, int zDif, QColor& color);
    void rotar(float theta, Line* eje);
    Line* getCurrentAxis(Axis);
    Vertex calculateCentroid() const;
    Object3D* copy();
    void reset();
};

#endif // OBJECT3D_H
