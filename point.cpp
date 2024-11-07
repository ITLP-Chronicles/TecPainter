#include "point.h"

Point::Point(): x(0), y(0), z(0){}
Point::Point(float x, float y, float z): x(x), y(y), z(z) {}

Point Point::copy() const {
    return Point(this->x, this->y, this->z);
};

void Point::transform(const Matrix& toMultiply){
    Matrix thisToMatrix(4,1, {{this->x}, {this->y}, {this->z}, {1}});
    Matrix result = toMultiply * thisToMatrix;
    this->x = result.data[0][0];
    this->y = result.data[0][1];
    this->z = result.data[0][2];
}
