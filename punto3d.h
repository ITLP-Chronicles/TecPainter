#ifndef PUNTO3D_H
#define PUNTO3D_H
#include "matriz.h"

class Punto3D
{
public:
    Matriz* x_y_z;

    Punto3D(int x, int y, int z);

    // void desplegar(QPainter *); maybe make an obj for this
    Punto3D clonar();

    bool esSeleccionado(int, int);

    void transformar(const Matriz&);
};

#endif // PUNTO3D_H
