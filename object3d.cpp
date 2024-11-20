#include "object3d.h"
#include <vector>
#include "surface.h"
#include "matrix.h"
#include "vertex.h"

Object3D::Object3D():surfaces(std::vector<Surface>()), originalSurfaces(std::vector<Surface>())  {
    x = 0;
    y = 0;
    z = 0;
    sizex = 0;
    sizey = 0;
    sizez = 0;
    ejex=new Line(250,250,150,300,250,150);
    ejey=new Line(250,250,150,250,300,150);
    ejez=new Line(250,250,150,250,250,200);
}



void Object3D::addSurface(const Surface& toAdd){
    this->surfaces.push_back(toAdd);
    this->originalSurfaces.push_back(toAdd);
}

void Object3D::transform(const Matrix& transformy){
    for (Surface& s : this->surfaces){
        s.transform(transformy);
    }
}

Object3D::~Object3D() {
    delete ejex;
    delete ejey;
    delete ejez;
    for (Surface& surface : surfaces) {
        delete &surface;
    }
}

void Object3D::addPrism(float x, float y, float z, float width, float height, float depth) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->sizex = width;
    this->sizey = height;
    this->sizez = depth;
    // Define las 8 esquinas del prisma
    Vertex v1(x, y, z);                      // Frente abajo izquierda
    Vertex v2(x + width, y, z);               // Frente abajo derecha
    Vertex v3(x + width, y + height, z);      // Frente arriba derecha
    Vertex v4(x, y + height, z);              // Frente arriba izquierda

    Vertex v5(x, y, z + depth);                               // Atrás abajo izquierda
    Vertex v6(x + width, y, z + depth);                       // Atrás abajo derecha
    Vertex v7(x + width, y + height, z + depth);              // Atrás arriba derecha
    Vertex v8(x, y + height, z + depth);                      // Atrás arriba izquierda

    // Crear y agregar cada superficie del prisma al objeto 3D con vertices en sentido antihorario

    // Cara frontal (sentido antihorario desde afuera)
    Surface* front = new Surface();
    front->addVertex(v1);
    front->addVertex(v2);
    front->addVertex(v3);
    front->addVertex(v4);
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
    right->addVertex(v3);
    right->addVertex(v7);
    right->addVertex(v6);
    addSurface(*right);

    // Cara izquierda (sentido antihorario desde afuera)
    Surface* left = new Surface();
    left->addVertex(v1);
    left->addVertex(v4);
    left->addVertex(v8);
    left->addVertex(v5);
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

void Object3D::addPrism(int x, int y, int z, int xDif, int yDif, int zDif, QColor& color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->sizex = xDif;
    this->sizey = yDif;
    this->sizez = zDif;

    Surface* superficieCuerpo = new Surface(color);
    //cara principal
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    this->addSurface(*superficieCuerpo);


    //cara derecha
    superficieCuerpo = new Surface(color);
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    this->addSurface(*superficieCuerpo);

    //cara trasera
    superficieCuerpo = new Surface(color);
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara izquierda
    superficieCuerpo = new Surface(color);
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara superior
    superficieCuerpo = new Surface(color);
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z));
    superficieCuerpo->addVertex(Vertex(x + xDif, y + yDif, z - zDif));
    superficieCuerpo->addVertex(Vertex(x, y + yDif, z - zDif));
    this->addSurface(*superficieCuerpo);

    //cara inferior
    superficieCuerpo = new Surface(color);
    superficieCuerpo->addVertex(Vertex(x, y, z));
    superficieCuerpo->addVertex(Vertex(x, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z - zDif));
    superficieCuerpo->addVertex(Vertex(x + xDif, y, z));
    this->addSurface(*superficieCuerpo);
}
void Object3D::rotar(float theta, Line* eje) {
    float a = eje->vertex2.x - eje->vertex1.x;
    float b = eje->vertex2.y - eje->vertex1.y;
    float c = eje->vertex2.z - eje->vertex1.z;
    float alpha = atan2(b, c);
    float d = sqrt(pow(b, 2) + pow(c, 2));
    float beta = atan2(a, d);

    Matrix T1 = Matrix::generateGraphicableSquareMatrix(4, {{1,0,0, -eje->vertex1.x},
                                                       {0,1,0, -eje->vertex1.y},
                                                       {0,0,1, -eje->vertex1.x}});
    Matrix R1x = Matrix::generateGraphicableSquareMatrix(4, {{1,0,0, 0},
                                                            {0, cos(alpha), -sin(alpha), 0},
                                                            {0, sin(alpha), cos(alpha), 0}});
    Matrix R1y = Matrix::generateGraphicableSquareMatrix(4, {{cos(-beta), 0, sin(-beta), 0},
                                                             {0, 1, 0, 0},
                                                             {cos(theta), -sin(theta), 0, 0}});
    Matrix Rz = Matrix::generateGraphicableSquareMatrix(4, {{cos(-beta), 0, sin(-beta), 0},
                                                             {sin(theta), cos(theta), 0, 0},
                                                             {0, 0, 1, 0}});
    Matrix R2y = Matrix::generateGraphicableSquareMatrix(4, {{cos(beta), 0, sin(beta), 0},
                                                            {0, 1, 0, 0},
                                                            {-sin(beta), 0, cos(beta), 0}});
    Matrix R2x = Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, 0},
                                                             {0, cos(-alpha), -sin(-alpha), 0},
                                                             {0, sin(-alpha), cos(-alpha), 0}});
    Matrix T2 = Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, eje->vertex1.x},
                                                             {0, 1, 0, eje->vertex1.y},
                                                             {0, 0, 1, eje->vertex1.z}});

    Matrix M = T2 * (R2x * (R2y * (Rz * (R1y * (R1x *T1)))));
    transform(M);

    // También transformar los ejes
    ejex->transform(M);
    ejey->transform(M);
    ejez->transform(M);
}
#include "vertex.h"

Vertex Object3D::calculateCentroid() const {
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumZ = 0.0f;
    int vertexCount = 0;

    for (const Surface& surface : surfaces) {
        for (const Vertex& vertex : surface.vertices) { // Asegúrate de tener un método getVertices() en Surface
            sumX += vertex.x;  // Usa el método correspondiente de Vertex para obtener x, y, z
            sumY += vertex.y;
            sumZ += vertex.z;
            vertexCount++;
        }
    }

    if (vertexCount == 0) {
        return Vertex(0.0f, 0.0f, 0.0f);  // En caso de que no haya vértices
    }

    return Vertex(sumX / vertexCount, sumY / vertexCount, sumZ / vertexCount);
}

Object3D* Object3D::copy(){
    Object3D* toReturn = new Object3D();

    for(const Surface& s : this->surfaces)
        toReturn->addSurface(s.copy());

    return toReturn;
}

void Object3D::reset(){
    this->surfaces.clear();

    for(const Surface& originalSurface: this->originalSurfaces)
        this->surfaces.push_back(originalSurface.copy());
}

Line* Object3D::getCurrentAxis(Axis axis){
    switch (axis) {
    case X_AXIS:
        return ejex;
    case Y_AXIS:
        return ejey;;
    case Z_AXIS:
        return ejez;
    default:
        return nullptr;
    }
}
