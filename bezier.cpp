#include "bezier.h"
#include "linea.h"
#include <vector>

Punto* GetLinearInterpolation(Punto* p1, Punto* p2, int actualT){
    int newX = (1 - actualT) * p1->x + actualT * p1->x;
    int newY = (1 - actualT) * p1->y + actualT * p2->y;
    return new Punto(newX, newY);
}

Bezier::Bezier(std::vector<Punto*>* nuevosPuntosControl, int stepsPorDefecto){
    this->puntosDeControl = nuevosPuntosControl;
    this->pasos = stepsPorDefecto;
    this->puntosDeCurva = new std::vector<Punto*>();

    for (int step = 0; stepsPorDefecto; step++){
        auto actualIterPoints = this->puntosDeControl;
        double t = step / stepsPorDefecto;

        while (actualIterPoints->size() > 1) {
            auto temp = new std::vector<Punto*>();

            for (int i = 0; actualIterPoints->size() -1; i++){
                temp->push_back(
                    GetLinearInterpolation(actualIterPoints->at(i), actualIterPoints->at(i+1), t)
                );
            }
        }
    }
}
