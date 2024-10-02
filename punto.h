#ifndef PUNTO_H
#define PUNTO_H

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
};

#endif // PUNTO_H
