#include "bezier.h"
#include <vector>
#include "linea.h"
#include <math.h>

using namespace std;

//Método para poder obtener el punto "intermedio" en el porcentaje actualT (entre 0 y 1) entre p1 y p2
//e.g Si tengo (1,1)  y (1,10) con t = 0.5, me dará (1,5).
Punto* GetLinearInterpolation(Punto* p1, Punto* p2, double actualT){
    double newX = (1 - actualT) * p1->x + actualT * p2->x;
    double newY = (1 - actualT) * p1->y + actualT * p2->y;
    return new Punto(newX, newY);
}

Bezier::Bezier(std::vector<Punto*>* nuevosPuntosControl, int stepsPorDefecto){
    this->puntosDeControl = nuevosPuntosControl;
    this->pasos = stepsPorDefecto;
    this->puntosDeCurva = new std::vector<Punto*>();
    this->RecalculateSelf();
}

Bezier::~Bezier(){
    for(const auto& punto : *this->puntosDeControl)
        delete punto;

    for(const auto& punto: *this->puntosDeCurva)
        delete punto;
}


/* Dado un punto retorna el posible punto que se haya seleccionado con respecto a los PUNTOS DE CONTROL dado un radio (rango
 * de selección
 * En caso de que si:
 * 		Retorna una tupla con
 * 			- booleano = true
 * 			- Punto* = El puntero al punto que se selecciono
 *
 * En caso de que no:
 * 		Retorna una tupla con
 *			- booleano = false
 *			- Punto* = nullptr
*/
std::tuple<bool, Punto*> Bezier::esSeleccionada(int clickX, int clickY, int radiusSelectionRange){
    for (const auto& insideControlPoint : *this->puntosDeControl){
        double distance = sqrt(pow(clickX - insideControlPoint->x, 2) + pow(clickY - insideControlPoint->y, 2));
        if (distance < radiusSelectionRange){
            return {true, insideControlPoint};
        }
    }
    return {false, nullptr};
}

void Bezier::RecalculateSelf(){
    if (!this->puntosDeCurva->empty()) {
        for (auto& punto : *this->puntosDeCurva)
            delete punto;
        this->puntosDeCurva->clear();
    }

    for (int step = 0; step < this->pasos; ++step) {
        // Copiamos los puntos de control a una nueva lista de puntos iterados
        std::vector<std::unique_ptr<Punto>> actualIterPoints;
        for (const auto& controlPoint : *this->puntosDeControl) {
            actualIterPoints.push_back(std::make_unique<Punto>(controlPoint->x, controlPoint->y));
        }

        double t = (step * 1.0) / this->pasos;

        // Calculamos la interpolación de Bézier hasta que quede un solo punto
        while (actualIterPoints.size() > 1) {
            std::vector<std::unique_ptr<Punto>> temp;
            for (size_t i = 0; i < actualIterPoints.size() - 1; ++i) {
                auto point = GetLinearInterpolation(actualIterPoints[i].get(), actualIterPoints[i + 1].get(), t);
                temp.push_back(std::make_unique<Punto>(point->x, point->y));
                delete point;
            }
            actualIterPoints = std::move(temp); // Transferimos la propiedad de temp a actualIterPoints
        }

        // Agregamos el punto final calculado a puntosDeCurva
        this->puntosDeCurva->push_back(new Punto(actualIterPoints[0]->x, actualIterPoints[0]->y));
    }
}


void Bezier::Display(QPainter* painter){
    //Display the curve itself
    for (int i = 0; i < (int)this->puntosDeCurva->size() - 1; i++){
        auto tempLine = new Linea(this->puntosDeCurva->at(i), this->puntosDeCurva->at(i+1));
        tempLine->tipoLinea = this->tipoLineasBezier;
        if (tipoLineasBezier == LineaInterlineada && i%20 > 10){
            tempLine->desplegar(painter);
        }
        else if (tipoLineasBezier == LineaNormal) tempLine->desplegar(painter);
        delete tempLine;
    }

    float width = 10;
    float height = 10;

    //Display helping circles to edit bezer curve
    for (int i = 0; i < (int)this->puntosDeControl->size(); i++){
        //Same method, like previous. just creating lines.
        painter->drawEllipse(
            this->puntosDeControl->at(i)->x - (width / 10),
            this->puntosDeControl->at(i)->y - (height / 2),
            width,
            height
        );
    }
}

Bezier* Bezier::copiar(){
    auto copyPuntosControl = new std::vector<Punto*>();
    for (int i = 0; i < (int)this->puntosDeControl->size(); i++){
        copyPuntosControl->push_back(this->puntosDeControl->at(i)->copia());
    }
    Bezier *copiaBezier = new Bezier(copyPuntosControl, this->pasos);
    copiaBezier->tipoLineasBezier = tipoLineasBezier;
    return copiaBezier;
}
