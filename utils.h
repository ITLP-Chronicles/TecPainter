#ifndef UTILS_H
#define UTILS_H
#include "point.h"

class Utils
{
public:
    static double distancePointToLine(int, int, double, double, double, double);
    static double distance2Points(Point*, Point*);
    static double distance2Points(double, double, double, double);
};

#endif // UTILS_H
