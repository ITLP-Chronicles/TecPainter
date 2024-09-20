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
};

#endif // PUNTO_H
