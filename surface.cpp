#include "surface.h"
#include <vector>
#include "vertex.h"
#include "matrix.h"
#include <QColor>

Surface::Surface() : color(QColor::fromRgb(255,255,255)), vertices(std::vector<Vertex>())  {}

void Surface::addVertex(const Vertex& toAdd){
    this->vertices.push_back(toAdd);
}

void Surface::transform(const Matrix& transformy){
    for (Vertex& vertex : this->vertices) {
        vertex.transform(transformy);
    }
}

Surface Surface::copy() const{
    auto toReturn = Surface();

    for(Vertex v : this->vertices){
        toReturn.addVertex(v);
    }

    return toReturn;
}
