#include "objeto2d.h"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;



Objeto2D::Objeto2D() {
    inicio=nullptr;
    final=nullptr;
}


Objeto2D::~Objeto2D(){
    while(inicio != nullptr){
        Linea* temp = inicio;
        inicio = inicio->sig;
        delete temp;
        cout << "Se libero una linea" << endl;
    }
}

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

Objeto2D *Objeto2D::copia() {
    Objeto2D *objeto2d = new Objeto2D();
    Linea *linea = inicio; while(linea!=nullptr)
    {
        objeto2d->agregar(linea->copia());
        linea=linea->sig;
    }
    return objeto2d;
}

//------------ Métodos -------------

void Objeto2D::agregar(Linea *linea) {
    if (inicio==nullptr) {
        inicio=linea;
        final=linea;
    } else {
        final->sig=linea;
        final=linea;
    }
}

void Objeto2D::desplegar(QPainter* painter){
    ForEachLine([painter](Linea* linea){linea->desplegar(painter);});
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

void Objeto2D::leer(QDomElement lineaXML, QDomElement puntoXML){
    while (!lineaXML.isNull()) {
        Linea* linea = new Linea();

        QDomElement puntoXML = lineaXML.firstChildElement();
        if (!puntoXML.isNull()) {
            float x = puntoXML.attribute("X").toFloat();
            float y = puntoXML.attribute("Y").toFloat();
            linea->p1 = new Punto(x, y);
            std::cout << "Punto X=" << x << " Y=" << y << std::endl;

            puntoXML = puntoXML.nextSiblingElement();
            if (!puntoXML.isNull()) {
                x = puntoXML.attribute("X").toFloat();
                y = puntoXML.attribute("Y").toFloat();
                linea->p2 = new Punto(x, y);
                std::cout << "Punto X=" << x << " Y=" << y << std::endl;
            }

            QString lineMode = lineaXML.attribute("estilo");
            linea->tipoLinea = lineMode == "I" ? LineaInterlineada:LineaNormal;
        }
        this->agregar(linea);
        lineaXML = lineaXML.nextSiblingElement();
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
}

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

void Objeto2D::escalar(float factorX, float factorY, float centerX, float centerY){
    ForEachLine([factorX, factorY, centerX, centerY](Linea *current){
        current->escalar(factorX, factorY, centerX, centerY);
    });
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


void Objeto2D::updateLineStyleToAll(TipoLinea newStyle){
    ForEachLine([newStyle](Linea *current){
        current->tipoLinea = newStyle;
    });
}

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

void Objeto2D::transformar(Matriz2D* MTransform){
    ForEachLine([MTransform](Linea *current){
        current->transformar(MTransform);
    });
}
