#include "objeto2d.h"
#include <iostream>
using namespace std;

Objeto2D::Objeto2D() {
    inicio=nullptr;
    final=nullptr;
}

Objeto2D::~Objeto2D(){
    Linea* temp = inicio;
    while(temp != nullptr){
        Linea* nextOne = temp->sig;
        delete temp;
        cout << "Se libero una linea" << endl;
        temp = nextOne;
    }
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
    Linea* pointer = inicio;
    while (pointer != nullptr){
        pointer->desplegar(painter);
        pointer = pointer->sig;
    }
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


Linea* Objeto2D::seleccionada(int x, int y){
    Linea* pointer = inicio;
    while (pointer != nullptr){
        if (pointer->esSeleccionada(x,y)){
            return pointer;
        }
        pointer = pointer->sig;
    }
    return nullptr;
}









