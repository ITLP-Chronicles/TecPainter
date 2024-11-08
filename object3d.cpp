#include "object3d.h"
#include <vector>
#include "surface.h"
#include "matrix.h"
#include "vertex.h"

Object3D::Object3D():surfaces(std::vector<Surface>()) {}

void Object3D::addSurface(const Surface& toAdd){
    this->surfaces.push_back(toAdd);
}

void Object3D::transform(const Matrix& transformy){
    for (Surface& s : this->surfaces){
        s.transform(transformy);
    }
}

void Object3D::addPrism(float x, float y, float z, float width, float height, float depth) {
    // Define las 8 esquinas del prisma
    Vertex v0(x, y, z);                      // Frente abajo izquierda
    Vertex v1(x + width, y, z);               // Frente abajo derecha
    Vertex v2(x + width, y + height, z);      // Frente arriba derecha
    Vertex v3(x, y + height, z);              // Frente arriba izquierda

    Vertex v4(x, y, z - depth);                               // Atrás abajo izquierda
    Vertex v5(x + width, y, z - depth);                       // Atrás abajo derecha
    Vertex v6(x + width, y + height, z - depth);              // Atrás arriba derecha
    Vertex v7(x, y + height, z - depth);                      // Atrás arriba izquierda

    // Crear y agregar cada superficie del prisma al objeto 3D con vertices en sentido antihorario

    // Cara frontal
    Surface* front = new Surface();
    front->addVertex(v0);
    front->addVertex(v3);
    front->addVertex(v2);
    front->addVertex(v1);
    addSurface(*front);

    // Cara trasera
    Surface* back = new Surface();
    back->addVertex(v4);
    back->addVertex(v5);
    back->addVertex(v6);
    back->addVertex(v7);
    addSurface(*back);

    // Cara derecha
    Surface* right = new Surface();
    right->addVertex(v1);
    right->addVertex(v2);
    right->addVertex(v6);
    right->addVertex(v5);
    addSurface(*right);

    // Cara izquierda
    Surface* left = new Surface();
    left->addVertex(v0);
    left->addVertex(v4);
    left->addVertex(v7);
    left->addVertex(v3);
    addSurface(*left);

    // Cara superior
    Surface* top = new Surface();
    top->addVertex(v3);
    top->addVertex(v7);
    top->addVertex(v6);
    top->addVertex(v2);
    addSurface(*top);

    // Cara inferior
    Surface* bottom = new Surface();
    bottom->addVertex(v0);
    bottom->addVertex(v1);
    bottom->addVertex(v5);
    bottom->addVertex(v4);
    addSurface(*bottom);
}
