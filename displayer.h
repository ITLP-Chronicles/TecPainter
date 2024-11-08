#ifndef DISPLAYER_H
#define DISPLAYER_H
#include <QPainter>
#include "line.h"
#include "vertex.h"
#include "surface.h"
#include "object3d.h"

class Displayer
{
public:
    static void vertex(QPainter* painterRef, const Vertex& vertexToDisplay);
    static void line(QPainter* painterRef, const Line& lineToDisplay);
    static void surface(QPainter* painterRef, Surface& surfaceToDisplay);
    static void object3d(QPainter* painterRef, const Object3D& objToDisplay);
};

#endif // DISPLAYER_H
