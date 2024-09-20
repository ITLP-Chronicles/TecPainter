#include "punto.h"
#include "utils.h"
#include <cmath>


double Utils::distanciaPuntoALinea(int px, int py, double x1, double y1, double x2, double y2) {
    // Vector AB
    double ABx = x2 - x1;
    double ABy = y2 - y1;
    // Vector AP
    double APx = px - x1;
    double APy = py - y1;

    // Dot product of AB and AP
    double dotProduct = (ABx * APx + ABy * APy);
    double lengthSquared = ABx * ABx + ABy * ABy;

    // Projection factor t
    double t = dotProduct / lengthSquared;

    // Clamp t to [0, 1] to find closest point on segment
    t = std::max(0.0, std::min(1.0, t));

    // Closest point coordinates
    double closestX = x1 + t * ABx;
    double closestY = y1 + t * ABy;

    // Calculate distance from P to closest point
    return sqrt((px - closestX) * (px - closestX) + (py - closestY) * (py - closestY));
}


double Utils::distancia2Puntos(Punto* p1, Punto* p2){
    return std::sqrt(std::pow((p2->x - p1->y), 2) + std::pow(p2->y - p1->y, 2));
}

double Utils::distancia2Puntos(double x1, double y1, double x2, double y2){
    return std::sqrt(std::pow((x2-x1),2) + std::pow((y2-y1), 2));
}

