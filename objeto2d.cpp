#include "objeto2d.h"
#include <iostream>
#include <tuple>
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


tuple<Linea*, Punto*> Objeto2D::seleccionada(int x, int y){
    //1. Posicionar puntero inicial para recorrer cada línea y revisar su cercanía con el click
    Linea* pointer = inicio;
    while (pointer != nullptr){
        //2. Llamar al método de la línea. Retorna <bool, Punto*>: True si dio click allí y el punto más cercano
        auto tuple = inicio->esSeleccionada(x,y);
        if (std::get<0>(tuple)){
            return std::make_tuple(pointer, std::get<1>(tuple));
        }
        pointer = pointer->sig;
    }
    //3. Retorna una tupla por defecto
    return std::make_tuple(nullptr, nullptr);
}









