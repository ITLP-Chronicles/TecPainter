#ifndef MATRIZ2D_H
#define MATRIZ2D_H

class Matriz2D
{
public:
    float datos[3][3];
    Matriz2D();
    Matriz2D(float);
    Matriz2D(float[3][3]);
    Matriz2D(Matriz2D*);
    Matriz2D(float,float,float,float,float,float);
    Matriz2D *mult(Matriz2D*);
    void multThis(Matriz2D*);

    void trasladar(float,float);
    void rotar(float,float,float);
    void escalar(float,float,float,float);

    void equals(Matriz2D*);
    Matriz2D* copia();

    //Static Methods
    static Matriz2D* GenerateRotationMatrix(float piRadians);
    static Matriz2D* GenerateTraslationMatrix(int deltaX, int deltaY);
    static Matriz2D* GenerateScaleMatrix(float scaleFactorX, float scaleFactorY);
    static Matriz2D* GenerateVerticalMirrorMatrix();
};

#endif // MATRIZ2D_H
