#include "utils.h"
#include <cmath>

Utils::Utils() {}

double Utils::distanciaPuntoALinea(int px, int py, int x1, int y1, int x2, int y2) {
    double num = std::abs((y2 - y1) * px - (x2 - x1) * py + x2 * y1 - y2 * x1);
    double den = std::sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
    return num / den;
}
