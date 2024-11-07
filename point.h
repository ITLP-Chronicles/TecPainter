#ifndef POINT_H
#define POINT_H
#include "matrix.h"

class Point
{
public:
    float x;
    float y;
    float z;

    Point();
    Point(float x, float y, float z);

    // void desplegar(QPainter *); maybe make an obj for this
    Point copy() const;

    bool isSelected(float, float);

    void transform(const Matrix&);
};

#endif // POINT_H
