#ifndef UTILS_H
#define UTILS_H
#include "punto.h"

class Utils
{
public:
    static double distanciaPuntoALinea(int, int, double, double, double, double);
    static double distancia2Puntos(Punto*, Punto*);
    static double distancia2Puntos(double, double, double, double);
};

#endif // UTILS_H
