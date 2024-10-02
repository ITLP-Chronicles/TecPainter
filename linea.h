#ifndef LINEA_H
#define LINEA_H

#include "punto.h"
#include <tuple>

enum TipoLinea {
    LineaNormal,
    LineaInterlineada
};

class Linea
{
public:
    Punto *p1;
    Punto *p2;
    Linea *sig;
    int anchoInterlineado;
    TipoLinea tipoLinea;
    Linea();
    ~Linea();
    Linea *copia();
    Linea(Punto *,Punto *);
    Linea(float,float,float,float);
    void desplegar(QPainter *);
    std::tuple<bool, Punto*> esSeleccionada(int, int);
    void trasladar(float newX, float newY);
    void rotar(float xr, float yr, float ang);
    void escalar(float factorX, float factorY, float centerX, float centerY);
};

#endif // LINEA_H
