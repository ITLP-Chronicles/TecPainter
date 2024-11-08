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
    Vertex v1(x, y, z);                      // Frente abajo izquierda
    Vertex v2(x + width, y, z);               // Frente abajo derecha
    Vertex v3(x + width, y + height, z);      // Frente arriba derecha
    Vertex v4(x, y + height, z);              // Frente arriba izquierda

    Vertex v5(x, y, z - depth);               // Atrás abajo izquierda
    Vertex v6(x + width, y, z - depth);       // Atrás abajo derecha
    Vertex v7(x + width, y + height, z - depth); // Atrás arriba derecha
    Vertex v8(x, y + height, z - depth);      // Atrás arriba izquierda

    // Crear y agregar cada superficie del prisma al objeto 3D

    // Cara frontal (sentido antihorario desde afuera)
    Surface* front = new Surface();
    front->addVertex(v1);
    front->addVertex(v4);
    front->addVertex(v3);
    front->addVertex(v2);
    addSurface(*front);

    // Cara trasera (sentido antihorario desde afuera)
    Surface* back = new Surface();
    back->addVertex(v6);
    back->addVertex(v5);
    back->addVertex(v8);
    back->addVertex(v7);
    addSurface(*back);

    // Cara derecha (sentido antihorario desde afuera)
    Surface* right = new Surface();
    right->addVertex(v2);
    right->addVertex(v6);
    right->addVertex(v7);
    right->addVertex(v3);
    addSurface(*right);

    // Cara izquierda (sentido antihorario desde afuera)
    Surface* left = new Surface();
    left->addVertex(v5);
    left->addVertex(v1);
    left->addVertex(v4);
    left->addVertex(v8);
    addSurface(*left);

    // Cara superior (sentido antihorario desde afuera)
    Surface* top = new Surface();
    top->addVertex(v4);
    top->addVertex(v3);
    top->addVertex(v7);
    top->addVertex(v8);
    addSurface(*top);

    // Cara inferior (sentido antihorario desde afuera)
    Surface* bottom = new Surface();
    bottom->addVertex(v5);
    bottom->addVertex(v6);
    bottom->addVertex(v2);
    bottom->addVertex(v1);
    addSurface(*bottom);
}

void Object3D::addPrism(int x, int y, int z, int xDif, int yDif, int zDif){

    Surface* superficieCuerpo = new Surface();
    //cara principal
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    this->addSurface(*superficieCuerpo);


    //cara derecha
    superficieCuerpo = new Surface();
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    this->addSurface(*superficieCuerpo);

    //cara trasera
    superficieCuerpo = new Surface();
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara izquierda
    superficieCuerpo = new Surface();
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara superior
    superficieCuerpo = new Surface();
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara inferior
    superficieCuerpo = new Surface();
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    this->addSurface(*superficieCuerpo);
}

