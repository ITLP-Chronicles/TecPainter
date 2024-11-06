#ifndef PUNTO3D_H
#define PUNTO3D_H
#include "matriz.h"

class Punto3D
{
public:
    float x;
    float y;
    float z;

    Punto3D(float x, float y, float z);

    // void desplegar(QPainter *); maybe make an obj for this
    Punto3D clonar();

    bool esSeleccionado(float, float);

    void transformar(const Matriz&);
};

#endif // PUNTO3D_H
