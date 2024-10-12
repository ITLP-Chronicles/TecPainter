#ifndef PUNTO_H
#define PUNTO_H

#include "matriz2d.h"
#include <QPainter>

class Punto
{
public:
    float x;
    float y;
    Punto();
    Punto(float,float);
    void desplegar(QPainter *);
    Punto *copia();
    bool esSeleccionado(int, int);
    void trasladar(float newX, float newY);
    void rotar(float xr, float yr, float ang);
    void escalar(float factorX, float factorY, float centerX, float centerY);
    void reemplazar(Punto*);
    void transformar(Matriz2D*);
    Punto *matrizAPunto(Matriz2D*);
    Matriz2D *puntoAMatriz();
};

#endif // PUNTO_H
