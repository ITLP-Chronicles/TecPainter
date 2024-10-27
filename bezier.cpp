#include "bezier.h"
#include "linea.h"

int factorial(int num){
    if (num == 0) return 1;
    return num * factorial(num-1);
}

Bezier::Bezier(Punto** control, int n, int m) {
    puntosControl=control;
    numeroPuntosControl=n;
    numeroPuntosCurva=m;
    puntosCurva=new Punto*[m+1];
    coeficientes=new float[n+1];
    obtenerCoeficientes();
    calcular();
}

Bezier::~Bezier(){
    for (int i = 0; i <= numeroPuntosCurva; i++) {
        delete puntosCurva[i];
    }
    delete[] puntosCurva;

    delete[] coeficientes;

    Linea* current = inicio;
    while (current != nullptr) {
        Linea* next = current->sig;
        delete current;
        current = next;
    }
}

void Bezier::obtenerCoeficientes(){
    int nFactorial = factorial(numeroPuntosControl);
    for(int k = 0; k <= numeroPuntosControl; k++){
        float kFactorial = factorial(k);
        float nMenoskFactorial = factorial(numeroPuntosControl-k);
        coeficientes[k] = nFactorial / (kFactorial * nMenoskFactorial);
    }
}

float Bezier::BEZ(int k, float u) {
    return coeficientes[k]*pow(u,k)*pow(1-u,numeroPuntosControl-k);
}

Punto *Bezier::calcularPunto(float u) {
    Punto *puntoCurva=new Punto();
    for (int k = 0; k <= numeroPuntosControl; k++) {
        float bez = BEZ(k, u);
        puntoCurva->x += bez * puntosControl[k]->x;
        puntoCurva->y += bez * puntosControl[k]->y;
    }
    return puntoCurva;
}

void Bezier::calcular() {
    for (int i=0; i<=numeroPuntosCurva; i++) {
        puntosCurva[i]=calcularPunto((float)i/numeroPuntosCurva);
    }
    inicio = new Linea(puntosCurva[0], puntosCurva[1]);
    Linea* lineaActual = inicio;

    for (int i = 1; i < numeroPuntosCurva; i++) {
        Linea* siguienteLinea = new Linea(puntosCurva[i], puntosCurva[i + 1]);
        lineaActual->sig = siguienteLinea;
        lineaActual = siguienteLinea;
    }
}

void Bezier::desplegar(QPainter* painter) {
    Linea* l = inicio;
    while (l != nullptr) {
        l->desplegar(painter);
        l = l->sig;
    }
}
