#include "object3d.h"
#include <vector>
#include "surface.h"
#include "matrix.h"

Object3D::Object3D():surfaces(std::vector<Surface>()) {}

void Object3D::addSurface(const Surface& toAdd){
    this->surfaces.push_back(toAdd);
}

void Object3D::transform(const Matrix& transformy){
    for (Surface& s : this->surfaces){
        s.transform(transformy);
    }
}
