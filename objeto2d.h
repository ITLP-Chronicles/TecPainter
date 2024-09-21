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
};

#endif // OBJETO2D_H
