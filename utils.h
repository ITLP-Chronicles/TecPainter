#ifndef UTILS_H
#define UTILS_H
#include "punto.h"

class Utils
{
public:
    static double distanciaPuntoALinea(int, int, int, int, int, int);
    static double distancia2Puntos(Punto*, Punto*);
};

#endif // UTILS_H
