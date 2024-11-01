#include "objeto2d.h"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// ----------- Característica Especial (Guardar archivo y leer) ------------

void Objeto2D::leer(QDomElement objeto2DXML){
    QDomElement trazoXML = objeto2DXML.firstChildElement();

    while (!trazoXML.isNull()) {
        QDomElement puntoXML = trazoXML.firstChildElement();
        if (trazoXML.tagName() == "Linea"){
            Linea* linea = new Linea();

            if (!puntoXML.isNull()) {
                float x = puntoXML.attribute("X").toFloat();
                float y = puntoXML.attribute("Y").toFloat();
                linea->p1 = new Punto(x, y);

                puntoXML = puntoXML.nextSiblingElement();
                if (!puntoXML.isNull()) {
                    x = puntoXML.attribute("X").toFloat();
                    y = puntoXML.attribute("Y").toFloat();
                    linea->p2 = new Punto(x, y);
                }

                QString lineMode = trazoXML.attribute("estilo");
                linea->tipoLinea = lineMode == "I" ? LineaInterlineada:LineaNormal;
            }
            this->agregarLinea(linea);
        } else{
            std::vector<Punto*>* puntosDeControl = new std::vector<Punto*>();;
            while (!puntoXML.isNull()){
                float x = puntoXML.attribute("X").toFloat();
                float y = puntoXML.attribute("Y").toFloat();
                puntosDeControl->push_back(new Punto(x, y));
                puntoXML = puntoXML.nextSiblingElement();
            }
            Bezier* curva = new Bezier(puntosDeControl,500);
            QString lineMode = trazoXML.attribute("estilo");
            curva->tipoLineasBezier = lineMode == "I" ? LineaInterlineada:LineaNormal;
            this->agregarCurva(curva);
        }
        trazoXML = trazoXML.nextSiblingElement();
    }
}
void Objeto2D::guardar(QDomDocument document, QDomElement objeto2DXML){
    Linea* pointer = this->inicio;
    while (pointer != nullptr)
    {
        QDomElement linea=document.createElement("Linea");
        linea.setAttribute("estilo", pointer->tipoLinea == LineaNormal ? "N":"I");
        objeto2DXML.appendChild(linea);

        QDomElement punto=document.createElement("Punto");
        punto.setAttribute("X",pointer->p1->x);
        punto.setAttribute("Y",pointer->p1->y);
        linea.appendChild(punto);

        punto=document.createElement("Punto");
        punto.setAttribute("X",pointer->p2->x);
        punto.setAttribute("Y",pointer->p2->y);
        linea.appendChild(punto);

        pointer = pointer->sig;
    }
    pointer = nullptr;

    for (int i = 0; i < (int)listaDeBezieres->size(); i++){
        QDomElement curva=document.createElement("Curva");
        curva.setAttribute("estilo", listaDeBezieres->at(i)->tipoLineasBezier == LineaNormal ? "N":"I");
        objeto2DXML.appendChild(curva);

        for (int j = 0; j < (int)listaDeBezieres->at(i)->puntosDeControl->size(); j++){
            QDomElement punto=document.createElement("Punto");
            punto.setAttribute("X",listaDeBezieres->at(i)->puntosDeControl->at(j)->x);
            punto.setAttribute("Y",listaDeBezieres->at(i)->puntosDeControl->at(j)->y);
            curva.appendChild(punto);
        }
    }
}

// ---------------- Default Constructor -----------------

// Constructor ()
Objeto2D::Objeto2D() {
    inicio=nullptr;
    final=nullptr;
    defaultLineStyle = LineaNormal;
    listaDeBezieres = new std::vector<Bezier*>();

}

// Destructor ()
Objeto2D::~Objeto2D(){
    while(inicio != nullptr){
        Linea* temp = inicio;
        inicio = inicio->sig;
        delete temp;
    }
}

// ---------------------- Linea Logic --------------------------
void Objeto2D::ForEachLine(std::function<void(Linea*)> callBack){
    Linea* temp = inicio;
    while(temp != nullptr){
        callBack(temp);
        temp = temp->sig;
    }
}

bool Objeto2D::HayLineas(){
    return this->inicio != nullptr && this->final != nullptr;
}

void Objeto2D::agregarLinea(Linea *linea) {
    if (inicio==nullptr) {
        inicio=linea;
        final=linea;
    } else {
        final->sig=linea;
        final=linea;
    }
}

void Objeto2D::eliminarTodasLineas(){
    std::vector<Linea*>* temp = new std::vector<Linea*>();
    ForEachLine([temp](Linea* line){
        temp->push_back(line);
    });
    for(int i = 0; i < (int)temp->size(); i++){
        eliminar(temp->at(i));
    }
    delete temp;
}


void Objeto2D::updateLineStyleToAll(TipoLinea newStyle){
    ForEachLine([newStyle](Linea *current){
        current->tipoLinea = newStyle;
    });

    for (const auto& bezier : *this->listaDeBezieres){
        bezier->tipoLineasBezier = newStyle;
    }
}


//Solo toma en cuenta las líneas
tuple<Linea*, Punto*> Objeto2D::seleccionada(int x, int y){
    //1. Posicionar puntero inicial para recorrer cada línea y revisar su cercanía con el click
    Linea* pointer = inicio;
    while (pointer != nullptr){
        //2. Llamar al método de la línea. Retorna <bool, Punto*>: True si dio click allí y el punto más cercano
        auto tuple = pointer->esSeleccionada(x,y);
        if (std::get<0>(tuple)){
            return std::make_tuple(pointer, std::get<1>(tuple));
        }
        pointer = pointer->sig;
    }
    //3. Retorna una tupla por defecto
    return std::make_tuple(nullptr, nullptr);
}


void Objeto2D::eliminar(Linea *linea) {
    if (inicio == nullptr || linea == nullptr) return; // Check for null pointers

    // Caso: Eliminar primera línea
    if (linea == inicio) {
        inicio = inicio->sig;
        delete linea;
        if (inicio == nullptr) { // Si la lista está vacía, actualizar el final
            final = nullptr;
        }
        return;
    }

    Linea *pointer = inicio;

    // Buscar en toda la lísta por la línea en cuestión
    while (pointer->sig != nullptr && pointer->sig != linea) {
        pointer = pointer->sig;
    }

    // Si la encontramos...?
    if (pointer->sig == linea) {
        // Caso: Borrando la última línea
        if (linea == final) {
            final = pointer;
        }
        pointer->sig = linea->sig; // Bypass the line to delete
        delete linea; // Free memory
    }
}



//------------ Curvas de Bezier Logic -------------

void Objeto2D::agregarCurva(Bezier *curva) {
    this->listaDeBezieres->push_back(curva);
}

//Funcionalidad específica de c++ no pensarlo mucho
void Objeto2D::eliminarCurva(Bezier *nuevaCurva) {
    auto it = this->listaDeBezieres->begin();
    while (it != this->listaDeBezieres->end()) {
        if (*it == nuevaCurva) {
            delete *it;
            it = this->listaDeBezieres->erase(it);
        } else {
            ++it;
        }
    }
}

bool Objeto2D::HayCurvas(){
    return this->listaDeBezieres->size() > 0;
}


/* Checa si se ha seleccionado algun punto de control de cualquier curva de bezier y devuelve la curva y su punto de control
 * seleccionado, puede devolver:
 *
 * En caso de que encuentre:
 * 	Una tupla con lo siguiente:
 * 		- Bezier* = Curva a la cual el punto le pertenece
 * 		- Punto* = Punto de CONTROL seleccionado de la curva Bezier*
 *
 * 	De lo contrario:
 * 		- Bezier* = nullptr
 * 		- Punto* = nullptr
*/
std::tuple<Bezier*, Punto*> Objeto2D::seleccionadaCurva(int clickX, int clickY){
    int radioSelection = 30; //In pixels

    for (const auto& curvaBezier: *this->listaDeBezieres){
        auto [isFound, pointFound] = curvaBezier->esSeleccionada(clickX, clickY, radioSelection);
        if (isFound)
            return {curvaBezier, pointFound};
    }

    return {nullptr, nullptr};
}

//----------- Objeto2D Métodos --------------

void Objeto2D::desplegar(QPainter* painter){
    ForEachLine([painter](Linea* linea){linea->desplegar(painter);});

    for (int i = 0; i < (int)this->listaDeBezieres->size(); i++){
        this->listaDeBezieres->at(i)->Display(painter);
    }
}

//TODO: Copiar también las curvas de bezier
Objeto2D *Objeto2D::copia() {
    Objeto2D *objeto2d = new Objeto2D();

    Linea *linea = inicio;
    while(linea!=nullptr)
    {
        objeto2d->agregarLinea(linea->copia());
        linea=linea->sig;
    }

    for (int i = 0; i < (int)this->listaDeBezieres->size(); i++)
        objeto2d->agregarCurva(this->listaDeBezieres->at(i)->copiar());

    return objeto2d;
}

//Solo toma en cuenta las líneas no las curvas
Punto *Objeto2D::centro(){
    int minX = inicio->p1->x, maxX = inicio->p1->x,
        minY = inicio->p1->y, maxY = inicio->p1->y;

    ForEachLine([&](Linea* linea) {
        for (int i = 0; i < 2; ++i) {
            Punto* p = (i == 0) ? linea->p1 : linea->p2;

            if (p->x < minX) minX = p->x;
            if (p->x > maxX) maxX = p->x;

            if (p->y < minY) minY = p->y;
            if (p->y > maxY) maxY = p->y;
        }
    });

    return new Punto ((minX+maxX)/2, (minY+maxY)/2);
}

//---------------------- Graficación SIN Matrices ------------------------------------------

void Objeto2D::trasladar(float newX, float newY){
    ForEachLine([newX, newY](Linea* current){
        current->trasladar(newX, newY);
    });
}

void Objeto2D::rotar(float xr, float yr, float ang){
    ForEachLine([xr, yr, ang](Linea *current){
        current->rotar(xr, yr, ang);
    });
}

void Objeto2D::escalar(float factorX, float factorY, float centerX, float centerY){
    ForEachLine([factorX, factorY, centerX, centerY](Linea *current){
        current->escalar(factorX, factorY, centerX, centerY);
    });
}

//---------------------- Graficación CON Matrices ------------------------------------------

void Objeto2D::transformar(Matriz2D* MTransform){
    ForEachLine([MTransform](Linea *current){
        current->transformar(MTransform);
    });

    for (int i = 0; i < (int)this->listaDeBezieres->size(); i++){
        Bezier* temp = this->listaDeBezieres->at(i);
        for (int j = 0; j < (int)temp->puntosDeControl->size(); j++){
            Punto* actualPoint = temp->puntosDeControl->at(j);
            actualPoint->transformar(MTransform);
        }
        temp->RecalculateSelf();
    }
}

void Objeto2D::trasladar(Linea* inputLinea){
    auto deltaX = inputLinea->p2->x - inputLinea->p1->x;
    auto deltaY = inputLinea->p2->y - inputLinea->p1->y;
    Matriz2D* traslate = new Matriz2D(1,0, deltaX, 0, 1, deltaY);
    transformar(traslate);
    delete traslate;
}

void Objeto2D::rotar(Linea* inputLinea){
    auto deltaX = inputLinea->p2->x - inputLinea->p1->x;
    auto deltaY = inputLinea->p2->y - inputLinea->p1->y;
    auto piRadians = atan2(deltaY, deltaX);

    float cos_teta = cos(piRadians);
    float sin_teta = sin(piRadians);

    Matriz2D * traslate =  new Matriz2D(1,0, -inputLinea->p1->x, 0, 1, -inputLinea->p1->y);
    Matriz2D* rotation = new Matriz2D(cos_teta, -sin_teta, 0, sin_teta, cos_teta,0);
    Matriz2D * traslate_back =  new Matriz2D(1,0, inputLinea->p1->x, 0, 1, inputLinea->p1->y);

    Matriz2D * finished_origin_rotated = traslate_back->mult(rotation);
    Matriz2D * finished_back = finished_origin_rotated->mult(traslate);

    transformar(finished_back);

    delete traslate;
    delete rotation;
    delete traslate_back;
    delete finished_origin_rotated;
    delete finished_back;
}

void Objeto2D::escalar(Linea* inputLinea){
    auto deltaX = inputLinea->p2->x - inputLinea->p1->x;
    auto deltaY = inputLinea->p2->y - inputLinea->p1->y;
    auto factorX = 0.01 + (deltaX)/100;
    auto factorY = 0.01 + -(deltaY)/100;

    Matriz2D * traslate =  new Matriz2D(1,0, -inputLinea->p1->x, 0, 1, -inputLinea->p1->y);
    Matriz2D * scale = new Matriz2D(factorX, 0,0,0,factorY,0);
    Matriz2D * traslate_back = new Matriz2D(1,0, inputLinea->p1->x, 0, 1, inputLinea->p1->y);

    Matriz2D * traslate_origin = scale->mult(traslate);
    Matriz2D * traslate_finished = traslate_back->mult(traslate_origin);

    transformar(traslate_finished);

    delete traslate;
    delete scale;
    delete traslate_back;
    delete traslate_origin;
    delete traslate_finished;
}

void Objeto2D::reflejar(Linea* actualLine){
    int deltaX = actualLine->p2->x - actualLine->p1->x;
    int deltaY = actualLine->p2->y - actualLine->p1->y;

    double angle = atan2(deltaY, deltaX);
    Matriz2D* traslate_origin = Matriz2D::GenerateTraslationMatrix(-actualLine->p1->x, -actualLine->p1->y);
    Matriz2D* rotate = Matriz2D::GenerateRotationMatrix(-angle);
    Matriz2D* vertical_swap = Matriz2D::GenerateVerticalMirrorMatrix();
    Matriz2D* rotate_back = Matriz2D::GenerateRotationMatrix(angle);
    Matriz2D* traslate_back = Matriz2D::GenerateTraslationMatrix(actualLine->p1->x, actualLine->p1->y);

    Matriz2D* traslate_part_1 = traslate_back->mult(rotate_back);
    Matriz2D* mirror_effect_part_1 = traslate_part_1->mult(vertical_swap);
    Matriz2D* mirror_effect_complete = mirror_effect_part_1->mult(rotate);
    Matriz2D* traslate_complete = mirror_effect_complete->mult(traslate_origin);

    transformar(traslate_complete);

    delete traslate_origin;
    delete rotate;
    delete vertical_swap;
    delete rotate_back;
    delete traslate_back;
    delete traslate_part_1;
    delete mirror_effect_part_1;
    delete mirror_effect_complete;
    delete traslate_complete;
}

void Objeto2D::escalarArbitrario(Linea* actualLine){
    auto deltaX = actualLine->p2->x - actualLine->p1->x;
    auto deltaY = actualLine->p2->y - actualLine->p1->y;

    auto piRadians = atan2(deltaY, deltaX);
    auto factorX = sqrt(deltaX * deltaX + deltaY * deltaY)/100.0;

    Matriz2D * traslate_to_origin = Matriz2D::GenerateTraslationMatrix(-actualLine->p1->x, -actualLine->p1->y);
    Matriz2D * rotate_to_x = Matriz2D::GenerateRotationMatrix(-piRadians);
    Matriz2D * scale_only_x = Matriz2D::GenerateScaleMatrix(factorX, 1);
    Matriz2D * rotate_to_x_back = Matriz2D::GenerateRotationMatrix(piRadians);
    Matriz2D * traslate_to_origin_back = Matriz2D::GenerateTraslationMatrix(actualLine->p1->x, actualLine->p1->y);

    Matriz2D * step_1 = traslate_to_origin_back->mult(rotate_to_x_back);
    Matriz2D * step_2 = step_1->mult(scale_only_x);
    Matriz2D * step_3 = step_2->mult(rotate_to_x);
    Matriz2D * step_4 = step_3->mult(traslate_to_origin);

    transformar(step_4);

    delete traslate_to_origin;
    delete rotate_to_x;
    delete scale_only_x;
    delete rotate_to_x_back;
    delete traslate_to_origin_back;
    delete step_1;
    delete step_2;
    delete step_3;
    delete step_4;
}

