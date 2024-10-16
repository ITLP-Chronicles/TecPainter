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

    //Matriz2D* puntoMatriz = this->puntoAMatriz();
    //puntoMatriz->trasladar(tx,ty);
    //Punto* nuevoPuntoMatriz = matrizAPunto(puntoMatriz);
    //this->reemplazar(nuevoPuntoMatriz);

    //delete puntoMatriz;
    //delete nuevoPuntoMatriz;
    //puntoMatriz = nullptr;

    Matriz2D *T = new Matriz2D(1,0,tx,0,1,ty);
    transformar(T);
    delete T;
    T = nullptr;
}

void Punto::rotar(float tx, float ty, float a) {
    //int ox = x;
    //x = (ox - xr) * cos(angulo) - (y - yr) * sin(angulo) + xr;
    //y = (y - yr) * cos(angulo) + (ox - xr) * sin(angulo) + yr;

    //Matriz2D* puntoMatriz = this->puntoAMatriz();
    //puntoMatriz->rotar(xr,yr,angulo);
    //Punto* nuevoPuntoMatriz = matrizAPunto(puntoMatriz);
    //this->reemplazar(nuevoPuntoMatriz);

    //delete puntoMatriz;
    //delete nuevoPuntoMatriz;
    //puntoMatriz = nullptr;

    Matriz2D *R = new Matriz2D(
        cos(a), -sin(a), tx-tx*cos(a)+ty*sin(a),
        sin(a),  cos(a), ty-ty*cos(a)-tx*sin(a)
        );
    transformar(R);
    delete R;
    R = nullptr;
}

void Punto::escalar(float sx, float sy, float tx, float ty) {
    //x = sx*(x-xf) + xf;
    //y = sy*(y-yf) + yf;

    //Matriz2D* puntoMatriz = this->puntoAMatriz();
    //puntoMatriz->escalar(sx,sy,xf,yf);
    //Punto* nuevoPuntoMatriz = matrizAPunto(puntoMatriz);
    //this->reemplazar(nuevoPuntoMatriz);

    //delete puntoMatriz;
    //delete nuevoPuntoMatriz;
    //puntoMatriz = nullptr;

    Matriz2D *E = new Matriz2D(
        sx, 0, tx-tx*sx,
        0, sy, ty-ty*sy
        );
    transformar(E);
    delete E;
    E = nullptr;
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
