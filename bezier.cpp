#include "bezier.h"
#include <vector>
#include "linea.h"

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

//El núcleo del los beziers. El algoritmo en sí.
void Bezier::RecalculateSelf(){
    if (this->puntosDeCurva->size() > 0){
        for(const auto& punto : *this->puntosDeCurva)
            delete punto;
        this->puntosDeCurva->clear();
    }

    //Con step nos referimos a la cantidad de puntos a hacerse y el no. de punto actual que se está calculando.
    for (int step = 0; step < this->pasos; step++){
        auto actualIterPoints = new std::vector<Punto*>(*puntosDeControl);
        double t = (step * 1.0) / this->pasos; //Aquí ya se está obteniendo el valor correspondiente de t en este step

        while (actualIterPoints->size() > 1) {
            auto temp = new std::vector<Punto*>();

            //Calcula los puntos intermedios dado el valor t.e.g entre los puntos
            //1-2, 2-3, 3-4, 4-5, 5-6, pero evitando 'último'-null. Por eso el size() - 1
            //y los guarda en temp para ser usados en la siguiente iteración.
            //Hasta que temp sea de longitud 1 (el punto que buscamos), ya acabamos por este step.
            for (int i = 0; i < (int)actualIterPoints->size() -1; i++){
                temp->push_back(
                    GetLinearInterpolation(actualIterPoints->at(i), actualIterPoints->at(i+1), t)
                );
            }
            delete actualIterPoints;
            actualIterPoints = temp;
        }

        //Aquí obtendríamos el punto resultante de todo el cálculo solo en este valor de t, lo agregamos al arreglo de curvas.
        //y continuamos con el siguiente valor de t
        puntosDeCurva->push_back(actualIterPoints->at(0));
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
