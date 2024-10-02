#include "punto.h"
#include <math.h>

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

void Punto::trasladar(float tx, float ty){
    x += tx;
    y += ty;
}

void Punto::rotar(float xr, float yr, float angulo) {
    //int _x = x, _y = y; //Keeping original coords before translation
    //trasladar(-xr, -yr);
    x =  (x-xr) * cos(angulo) - (y-yr) * sin(angulo) ; //help it is incomplete
    y = 0; //help
    //trasladar(xr, yr);
}

void Punto::escalar(float sx, float sy, float xf, float yf) {
    trasladar(-xf, -yf);
    x = sx*(x);
    y = sy*(y);
    trasladar(xf, yf);
}
