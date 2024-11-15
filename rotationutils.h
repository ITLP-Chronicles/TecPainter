// RotationUtils.h
#ifndef ROTATIONUTILS_H
#define ROTATIONUTILS_H

#include "matrix.h"
#include "vertex.h"
#include <cmath>

class RotationUtils {
public:
    static bool isRotationMatrix(const Matrix& R);
    static Vertex rotationMatrixToEulerAngles(const Matrix& R);
    static Matrix eulerAnglesToRotationMatrix(const Vertex& angles);
};

#endif // ROTATIONUTILS_H
