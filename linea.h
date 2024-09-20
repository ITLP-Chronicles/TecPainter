#ifndef LINEA_H
#define LINEA_H

#include "punto.h"

class Linea
{
public:
    Punto *p1;
    Punto *p2;
    Linea *sig;
    Linea();
    ~Linea();
    Linea(Punto *,Punto *);
    Linea(float,float,float,float);
    void desplegar(QPainter *);
    Linea *copia();
    bool esSeleccionada(int, int);
};

#endif // LINEA_H
