#include "punto.h"
#include "utils.h"
#include <cmath>


double Utils::distanciaPuntoALinea(int px, int py, int x1, int y1, int x2, int y2) {
    double num = std::abs((y2 - y1) * px - (x2 - x1) * py + x2 * y1 - y2 * x1);
    double den = std::sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
    return num / den;
}

double Utils::distancia2Puntos(Punto* p1, Punto* p2){
    return std::sqrt(std::pow((p2->x - p1->y), 2) + std::pow(p2->y - p1->y, 2));
}

