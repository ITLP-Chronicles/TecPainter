#ifndef BEZIER_H
#define BEZIER_H

#include "punto.h"
#include <vector>
#include "linea.h"

class Bezier
{

public:
    //Arreglo para guardar los puntos de control
    std::vector<Punto*>* puntosDeControl;

    //Arreglo para guardar los puntos de la curva
    std::vector<Punto*>* puntosDeCurva;

    //Número de puntos a generar de la curva
    int pasos;

    //Solo dale los puntos de control en un arreglo (vector) y el de puntos a generar de la curva
    Bezier(std::vector<Punto*>* nuevosPuntosDeControl, int pasosByDefault);
    ~Bezier();

    //Lo despliega, exige el tipo de línea en como se desee imprimir en pantalla
    void Display(QPainter* painter);

    Bezier* copiar();

    std::tuple<bool, Punto*> esSeleccionada(int clickX, int clickY, int radioSelectionRange);

    TipoLinea tipoLineasBezier = LineaNormal;

    //When you change internals control points, by default they don't change curve points, they need to be
    //recalculated, so with this function you can recalculate them.
    void RecalculateSelf();
  };


#endif // BEZIER_H
