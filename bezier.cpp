#include "bezier.h"
#include <vector>
#include "linea.h"
#include <math.h>

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

//El núcleo del los beziers. El algoritmo en sí.
void Bezier::RecalculateSelf(){
    if (this->puntosDeCurva->size() > 0){
        for(const auto& punto : *this->puntosDeCurva)
            delete punto;
        this->puntosDeCurva->clear();
    }

    // Con step nos referimos a la cantidad de puntos a calcular y el número de punto actual que se está calculando.
    for (int step = 0; step < this->pasos; step++){
        auto actualIterPoints = new std::vector<Punto*>(*puntosDeControl);
        double t = (step * 1.0) / this->pasos; // Aquí se obtiene el valor correspondiente de t en este step

        while (actualIterPoints->size() > 1) {
            auto temp = new std::vector<Punto*>();

            for (int i = 0; i < (int)actualIterPoints->size() - 1; i++) {
                temp->push_back(
                    GetLinearInterpolation(actualIterPoints->at(i), actualIterPoints->at(i+1), t)
                );
            }

           //for (auto point : *actualIterPoints) {
            //    delete point;
            //}

            delete actualIterPoints;
            actualIterPoints = temp;
        }

        // Agrega el punto resultante final a puntosDeCurva
        puntosDeCurva->push_back(actualIterPoints->at(0));

        // Limpia cualquier punto restante en actualIterPoints (excepto el primero ya agregado)
        for (size_t i = 1; i < actualIterPoints->size(); ++i) {
            delete actualIterPoints->at(i);
        }

        delete actualIterPoints;
    }
}

void Bezier::Display(QPainter* painter, TipoLinea type){
    //Display the curve itself
    for (int i = 0; i < (int)this->puntosDeCurva->size() - 1; i++){
        auto tempLine = new Linea(this->puntosDeCurva->at(i), this->puntosDeCurva->at(i+1));
        tempLine->tipoLinea = type;
        tempLine->desplegar(painter);
        delete tempLine;
    }

    //Display helping lines to edit bezer curve
    for (int i = 0; i < (int)this->puntosDeControl->size() - 1; i++){
        //Same method, like previous. just creating lines.
        auto tempLine = new Linea(this->puntosDeControl->at(i), this->puntosDeControl->at(i+1));
        tempLine->tipoLinea = type;
        tempLine->desplegar(painter);
        delete tempLine;
    }
}

Bezier* Bezier::copiar(){
    auto copyPuntosControl = new std::vector<Punto*>();
    for (int i = 0; i < (int)this->puntosDeControl->size(); i++){
        copyPuntosControl->push_back(this->puntosDeControl->at(i)->copia());
    }
    return new Bezier(copyPuntosControl, this->pasos);
}
