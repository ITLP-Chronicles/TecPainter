#include "utils.h"
#include "linea.h"

Linea::Linea() {
    p1 = new Punto();
    p2 = new Punto();
    tipoLinea = LineaNormal;
    anchoInterlineado = 5;
    sig=nullptr;
}

Linea::~Linea() {
    delete p1;
    delete p2;
    tipoLinea = LineaNormal;
    anchoInterlineado = 5;
    sig=nullptr;
}

Linea::Linea(Punto *p1, Punto *p2) {
    this->p1 = p1;
    this->p2 = p2;
    tipoLinea = LineaNormal;
    anchoInterlineado = 5;
    sig=nullptr;
}

Linea::Linea(float x1,float y1,float x2,float y2) {
    p1 = new Punto(x1,y1);
    p2 = new Punto(x2,y2);
    tipoLinea = LineaNormal;
    anchoInterlineado = 5;
    sig=nullptr;
}

void Linea::desplegar(QPainter *painter) {
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    int pixelsToTravel = (abs(dx) > abs(dy) ? abs(dx) : abs(dy));
    float xIncrement = dx /pixelsToTravel;
    float yIncrement = dy /pixelsToTravel;
    Punto *p = p1->copia();

    bool canDisplay = false;
    for(int i = 0; i <= pixelsToTravel; i++){
        if (i % anchoInterlineado == 0){
            canDisplay = !canDisplay;
        }
        if (tipoLinea == LineaNormal){
            p->desplegar(painter);
        } else {
            if (canDisplay){
                p->desplegar(painter);
            }
        }

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

std::tuple<bool, Punto*> Linea::esSeleccionada(int px, int py) {
    double distancia = Utils::distanciaPuntoALinea(px, py, this->p1->x, this->p1->y, this->p2->x, this->p2->y);
    bool estaSeleccionado =  distancia <= 10;

    // Find the closest point (p1 or p2) based on distance to the clicked point
    double distanciaAP1 = Utils::distancia2Puntos(px, py, this->p1->x, this->p1->y);
    double distanciaAP2 = Utils::distancia2Puntos(px, py, this->p2->x, this->p2->y);

    Punto* closestPoint = (distanciaAP1 <= distanciaAP2) ? this->p1 : this->p2;

    return std::make_tuple(estaSeleccionado, closestPoint);
}

void Linea::trasladar(float tx, float ty){
    p1->trasladar(tx,ty);
    p2->trasladar(tx,ty);
}

void Linea::rotar(float xr, float yr, float ang){
    p1->rotar(xr, yr, ang);
    p2->rotar(xr, yr, ang);
}

void Linea::escalar(float sx, float sy, float xf, float yf) {
    p1->escalar(sx, sy, xf, yf);
    p2->escalar(sx, sy, xf, yf);
}






