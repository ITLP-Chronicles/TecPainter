#include "line.h"
#include "vertex.h"

Line::Line()
    : vertex1(Vertex()), vertex2(Vertex()), intermitentSeparationWidth(5), lineType(NormalLine) {}

Line::Line(const Point& p1, const Point& p2)
    : vertex1(Vertex(p1)), vertex2(Vertex(p2)), intermitentSeparationWidth(5), lineType(NormalLine){}

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2)
    : vertex1(Vertex(x1,y1,z1)), vertex2(Vertex(x2,y2,z2)), intermitentSeparationWidth(5), lineType(NormalLine){}

Line Line::copy() const {
    return Line(this->vertex1.point, this->vertex2.point);
}

void Line::transform(const Matrix& MTransform){
    this->vertex1.transform(MTransform);
    this->vertex2.transform(MTransform);
}

//Not neccesary !
Line::~Line() {}


// std::tuple<bool, Point*> Line::isSelected(int px, int py) {
    // double distancia = Utils::distancePointToLine(px, py, this->p1->x, this->p1->y, this->p2->x, this->p2->y);
    // bool estaSeleccionado =  distancia <= 10;

    // // Find the closest point (p1 or p2) based on distance to the clicked point
    // double distanciaAP1 = Utils::distancia2Puntos(px, py, this->p1->x, this->p1->y);
    // double distanciaAP2 = Utils::distancia2Puntos(px, py, this->p2->x, this->p2->y);

    // Point* closestPoint = (distanciaAP1 <= distanciaAP2) ? this->p1 : this->p2;
//     return {true, new Point()};
// }








