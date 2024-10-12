#include "punto.h"
#include "matriz2d.h"
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
    //x += tx;
    //y += ty;

    Matriz2D* puntoMatriz = this->puntoAMatriz();
    puntoMatriz->trasladar(tx,ty);
    this->reemplazar(matrizAPunto(puntoMatriz));

    delete puntoMatriz;
    puntoMatriz = nullptr;
}

void Punto::rotar(float xr, float yr, float angulo) {
    //int ox = x;
    //x = (ox - xr) * cos(angulo) - (y - yr) * sin(angulo) + xr;
    //y = (y - yr) * cos(angulo) + (ox - xr) * sin(angulo) + yr;

    Matriz2D* puntoMatriz = this->puntoAMatriz();
    puntoMatriz->rotar(xr,yr,angulo);
    this->reemplazar(matrizAPunto(puntoMatriz));

    delete puntoMatriz;
    puntoMatriz = nullptr;
}

void Punto::escalar(float sx, float sy, float xf, float yf) {
    //x = sx*(x-xf) + xf;
    //y = sy*(y-yf) + yf;

    Matriz2D* puntoMatriz = this->puntoAMatriz();
    puntoMatriz->escalar(sx,sy,xf,yf);
    this->reemplazar(matrizAPunto(puntoMatriz));

    delete puntoMatriz;
    puntoMatriz = nullptr;
}

void Punto::transformar(Matriz2D* MTransform) {
    //Matriz2D* puntoMatriz = this->puntoAMatriz();
    //puntoMatriz = MTransform->mult(puntoMatriz);
    //this->reemplazar(matrizAPunto(puntoMatriz));

    //delete puntoMatriz;
    //puntoMatriz = nullptr;

    float xa = x;
    x = MTransform->datos[0][0] * xa + MTransform->datos[0][1] * y + MTransform->datos[0][2];
    y = MTransform->datos[1][0] * xa + MTransform->datos[1][1] * y + MTransform->datos[1][2];
}

Punto* Punto::matrizAPunto(Matriz2D* M){
    return new Punto(M->datos[0][2],M->datos[1][2]);
}
Matriz2D* Punto::puntoAMatriz(){
    return new Matriz2D(0,0,x,0,0,y);
}

void Punto::reemplazar(Punto* p){
    x = p->x;
    y = p->y;
}
