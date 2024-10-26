#ifndef BEZIER_H
#define BEZIER_H

#include "punto.h"
#include "linea.h"

class Bezier
{
public:
    int numeroPuntosControl = 0;
    int numeroPuntosCurva = 0;
    Punto **puntosControl;
    Punto **puntosCurva;
    float *coeficientes;
    Bezier(Punto**,int,int);
    ~Bezier();
    void obtenerCoeficientes();
    float BEZ(int,float);
    Punto *calcularPunto(float);
    void desplegar(QPainter*);
    void calcular();

    Bezier *sig;
    Linea *inicio;
};

#endif // BEZIER_H
