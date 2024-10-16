#ifndef OBJETO2D_H
#define OBJETO2D_H

#include "linea.h"
#include <tuple>
#include <QtXml>

class Objeto2D
{
public:
    Linea *inicio;
    Linea *final;
    TipoLinea defaultLineStyle;
    Objeto2D();
    ~Objeto2D();
    void agregar(Linea *);
    void eliminar(Linea *);
    void desplegar(QPainter *);
    void leer(QDomElement, QDomElement);
    void guardar(QDomDocument,QDomElement);
    bool HayLineas();
    Objeto2D *copia();
    std::tuple<Linea*, Punto*> seleccionada(int, int);
    void trasladar(float newX, float newY);
    void rotar(float xr, float yr, float ang);
    void rotar(Linea * lineaInput);
    void escalar(float factorX, float factorY, float centerX, float centerY);
    void escalar(Linea * lineaInput);
    void updateLineStyleToAll(TipoLinea newStyle);
    void transformar(Matriz2D*);
    void eliminarTodasLineas();

    Punto *centro();

private:
    void ForEachLine(std::function<void(Linea*)> callBack);
};

#endif // OBJETO2D_H
