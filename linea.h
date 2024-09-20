#ifndef LINEA_H
#define LINEA_H

#include "punto.h"
#include <tuple>

class Linea
{
public:
    Punto *p1;
    Punto *p2;
    Linea *sig;
    Linea();
    ~Linea();
    Linea *copia();
    Linea(Punto *,Punto *);
    Linea(float,float,float,float);
    void desplegar(QPainter *);
    std::tuple<bool, Punto*> esSeleccionada(int, int);
};

#endif // LINEA_H
