#include "matriz2d.h"

Matriz2D::Matriz2D() {
    datos[0][0] = 1;
    datos[0][1] = 0;
    datos[0][2] = 0;
    datos[1][0] = 0;
    datos[1][1] = 1;
    datos[1][2] = 0;
    datos[2][0] = 0;
    datos[2][1] = 0;
    datos[2][2] = 1;
}
Matriz2D::Matriz2D(float A, float B, float C, float D, float E, float F) {
    datos[0][0] = A;
    datos[0][1] = B;
    datos[0][2] = C;
    datos[1][0] = D;
    datos[1][1] = E;
    datos[1][2] = F;
    datos[2][0] = 0;
    datos[2][1] = 0;
    datos[2][2] = 1;
}
Matriz2D::Matriz2D(Punto * p) {
    datos[0][0] = 0;
    datos[0][1] = 0;
    datos[0][2] = p->x;
    datos[1][0] = 0;
    datos[1][1] = 0;
    datos[1][2] = p->y;
    datos[2][0] = 0;
    datos[2][1] = 0;
    datos[2][2] = 1;
}

Matriz2D* Matriz2D::mult(Matriz2D* M){
    Matriz2D *Mres = new Matriz2D(0,0,0,0,0,0);
    Mres->datos[2][2] = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            Mres->datos[i][j] += datos[i][j] * M->datos[j][i];
        }
    }
}
