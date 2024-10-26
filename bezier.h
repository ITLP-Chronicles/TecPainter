#ifndef BEZIER_H
#define BEZIER_H

#include "punto.h"

class Bezier
{
public:
    int numeroPuntosControl;
    int numeroPuntosCurva;

    Punto **puntosControl;
    Punto **puntosCurva;

    float *coeficientes;

    Bezier(Punto**,int,int);

    void obtenerCoeficientes();
    float bezier(int,float);
    void calcular();
    int factorial(int);

    void desplegar(QPainter*);
};

#endif // BEZIER_H
