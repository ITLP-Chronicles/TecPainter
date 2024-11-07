#include "surface.h"
#include <vector>
#include "vertex.h"
#include "matrix.h"

Surface::Surface() : vertices(std::vector<Vertex>()) {}

void Surface::addVertex(const Vertex& toAdd){
    this->vertices.push_back(toAdd);
}

void Surface::transform(const Matrix& transformy){
    for (auto vertex : this->vertices) {
        vertex.transform(transformy);
    }
}
