#include "matriz2d.h"

// Identity matrix constructor (default)
Matriz2D::Matriz2D() {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (i == j) datos[i][j] = 1;
            else datos[i][j] = 0;
        }
    }
}
// Scalar matrix
Matriz2D::Matriz2D(float A) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            datos[i][j] = A;
        }
    }
}
// Matrix from array
Matriz2D::Matriz2D(float A[3][3]) {
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            datos[i][j] = A[i][j];
        }
    }
    datos[2][0] = 0;
    datos[2][1] = 0;
    datos[2][2] = 1;
}
// Matrix defined by values
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
// Point matrix
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
Punto* Matriz2D::matrizAPunto(){
    return new Punto(datos[0][2],datos[1][2]);
}
// Matrix multiplication
Matriz2D* Matriz2D::mult(Matriz2D* M){
    Matriz2D *Mres = new Matriz2D((float)0);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                Mres->datos[i][j] += M->datos[i][k] * datos[k][j];
            }
        }
    }
    return Mres;
}

void Matriz2D::trasladar(float tx, float ty){
    Matriz2D *T = new Matriz2D(1,0,tx,0,1,ty);

    thisEquals(this->mult(T));

    delete T;
    T = nullptr;
}

void Matriz2D::rotar(float tx, float ty, float a){
    Matriz2D *R = new Matriz2D(
        cos(a), -sin(a), tx-tx*cos(a)+ty*sin(a),
        sin(a),  cos(a), ty-ty*cos(a)-tx*sin(a)
    );

    thisEquals(this->mult(R));

    delete R;
    R = nullptr;
}

void Matriz2D::escalar(float sx, float sy, float tx, float ty){
    Matriz2D *E = new Matriz2D(
        sx, 0, tx-tx*sx,
        0, sy, ty-ty*sy
    );

    thisEquals(this->mult(E));

    delete E;
    E = nullptr;
}

void Matriz2D::thisEquals(Matriz2D* M){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            datos[i][j] = M->datos[i][j];
        }
    }
}
