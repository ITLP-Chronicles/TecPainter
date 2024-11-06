#include "punto3d.h"

Punto3D::Punto3D(float x, float y, float z): x(x), y(y), z(z) {}

Punto3D Punto3D::clonar(){
    return Punto3D(this->x, this->y, this->z);
};

void Punto3D::transformar(const Matriz& toMultiply){
    Matriz thisToMatrix(1,3, {{this->x, this->y, this->z}});

    Matriz result = toMultiply * thisToMatrix;
    this->x = result.data.at(0).at(0);
    this->y = result.data.at(0).at(0);
    this->z = result.data.at(0).at(0);
}
