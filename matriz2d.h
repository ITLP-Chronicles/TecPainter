#ifndef MATRIZ2D_H
#define MATRIZ2D_H

#include "punto.h"

class Matriz2D
{
public:
    float datos[3][3];
    Matriz2D();
    Matriz2D(float);
    Matriz2D(float[3][3]);
    Matriz2D(float,float,float,float,float,float);
    Matriz2D(Punto*);
    Matriz2D *mult(Matriz2D*);
    void multThis(Matriz2D*);

    Punto* matrizAPunto();
    void trasladar(float,float);
    void rotar(float,float,float);
    void escalar(float,float,float,float);

    void thisEquals(Matriz2D*);
};

#endif // MATRIZ2D_H
