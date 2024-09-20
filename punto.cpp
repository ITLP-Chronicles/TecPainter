#include "punto.h"

Punto::Punto() {
    x=0;
    y=0;
}

Punto::Punto(float x,float y) {
    this->x=x;
    this->y=y;
}

void Punto::desplegar(QPainter *painter) {
    painter->drawPoint(x,y);
}

Punto* Punto::copia(){
    Punto *pCopia = new Punto(x,y);
    return pCopia;
}

bool Punto::esSeleccionado(int x, int y){
    int margenPx = 5;
    return (std::abs(this->x - x) < margenPx && std::abs(this->y - y) < margenPx);
}
