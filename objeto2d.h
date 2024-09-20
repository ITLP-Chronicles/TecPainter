#ifndef OBJETO2D_H
#define OBJETO2D_H

#include "linea.h"

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
    Objeto2D *copia();
    Linea* seleccionada(int, int);
};

#endif // OBJETO2D_H
