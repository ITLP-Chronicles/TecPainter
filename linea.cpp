#include "utils.h"
#include "linea.h"

Linea::Linea() {
    p1 = new Punto();
    p2 = new Punto();
    sig=nullptr;
}

Linea::~Linea() {
    delete p1;
    delete p2;
    sig=nullptr;
}

Linea::Linea(Punto *p1, Punto *p2) {
    this->p1 = p1;
    this->p2 = p2;
    sig=nullptr;
}

Linea::Linea(float x1,float y1,float x2,float y2) {
    p1 = new Punto(x1,y1);
    p2 = new Punto(x2,y2);
    sig=nullptr;
}

void Linea::desplegar(QPainter *painter) {
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    int pixelsToTravel = (abs(dx) > abs(dy) ? abs(dx) : abs(dy));
    float xIncrement = dx /pixelsToTravel;
    float yIncrement = dy /pixelsToTravel;
    Punto *p = p1->copia();
    for(int i = 0; i <= pixelsToTravel; i++){
        p->desplegar(painter);
        p->x += xIncrement;
        p->y += yIncrement;
    }
    delete p;
}

Linea* Linea::copia()
{
    Linea *linea = new Linea(p1->copia(),p2->copia());
    linea->sig=nullptr;
    return linea;
}

std::tuple<bool, Punto*> Linea::esSeleccionada(int px, int py){
    double distancia = Utils::distanciaPuntoALinea(px,py, this->p1->x, this->p1->y, this->p2->x, this->p2->y);
    bool estaSeleccionado =  distancia <= 10;

    Punto* click = new Punto(px, py);
    double distanciaAP1 = Utils::distancia2Puntos(click, this->p1);
    double distanciaAP2 = Utils::distancia2Puntos(click, this->p2);
    Punto* closestPoint =  distanciaAP1 <= distanciaAP2 ? this->p1 :  this->p2;

    delete click;
    click = nullptr;
    return std::make_tuple(estaSeleccionado, closestPoint);
}








