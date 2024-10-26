#include "bezier.h"
#include "linea.h"

int Bezier::factorial(int num){
    if (num == 0) return 1;
    return num * factorial(num-1);
}

Bezier::Bezier(Punto** control,int n,int m) {
    puntosControl = control;
    numeroPuntosControl = n;
    numeroPuntosCurva = m;
    puntosCurva = new Punto*[m+1];
    coeficientes = new float[n+1];
}

void Bezier::obtenerCoeficientes(){
    for (int k = 0; k < numeroPuntosControl; k++){
        coeficientes[k] = factorial(numeroPuntosControl)/(factorial(k)*factorial((numeroPuntosControl-k)));
    }
}

float Bezier::bezier(int k, float u){
    return coeficientes[k] * pow(u,k)*pow(1-u,numeroPuntosControl-k);
}

void Bezier::calcular(){
    obtenerCoeficientes();
    for (int u = 0; u < numeroPuntosCurva; u++){
        float x = 0, y = 0;
        for (int k = 0; k < numeroPuntosCurva; k++){
            x += puntosCurva[k]->x * bezier(k, u);
            y += puntosCurva[k]->y * bezier(k, u);

        }
        puntosCurva[u]->x = x;
        puntosCurva[u]->y = y;
    }
}
void Bezier::desplegar(QPainter* painter){
    for (int i = 0; i < numeroPuntosControl; i++){
        Linea* linea = new Linea(puntosCurva[i],puntosCurva[i+1]);
        linea->desplegar(painter);
    }
}
