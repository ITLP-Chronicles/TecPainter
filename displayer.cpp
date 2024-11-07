#include "displayer.h"
#include "vertex.h"
#include "surface.h"
#include "object3d.h"

void Displayer::object3d(QPainter* painterRef, const Object3D& obj){
    for (Surface surface : obj.surfaces){
        Displayer::surface(painterRef, surface);
    }
}

void Displayer::surface(QPainter* painterRef, const Surface& s){
    Line *temp;

    for (int i = 0; i < (int)s.vertices.size() - 1; ++i) {
        temp = new Line(s.vertices.at(i).point.copy(), s.vertices.at(i+1).point.copy());
        Displayer::line(painterRef, *temp);
        delete temp;
        /// Testing //painterRef->drawLine(s.vertices.at(i).point.x, s.vertices.at(i).point.y, s.vertices.at(i+1).point.x, s.vertices.at(i+1).point.y);
    }

    temp = new Line(s.vertices.at(s.vertices.size() - 1).point.copy(), s.vertices.at(0).point.copy());
    Displayer::line(painterRef, *temp);
    delete temp;
    /// Testing //painterRef->drawLine(s.vertices.at(s.vertices.size() - 1).point.x, s.vertices.at(s.vertices.size() - 1).point.y, s.vertices.at(0).point.x, s.vertices.at(0).point.y);
}

void Displayer::line(QPainter* painterRef, const Line& line){
    float dx = line.vertex2.point.x - line.vertex1.point.x;
    float dy = line.vertex2.point.y - line.vertex1.point.y;

    int pixelsToTravel = (abs(dx) > abs(dy) ? abs(dx) : abs(dy));
    float xIncrement = dx /pixelsToTravel;
    float yIncrement = dy /pixelsToTravel;

    Point p = line.vertex1.point.copy();

    bool canDisplay = false;
    for(int i = 0; i <= pixelsToTravel; i++){

        if (i % line.intermitentSeparationWidth == 0){
            canDisplay = !canDisplay;
        }
        if (line.lineType == NormalLine){
            Displayer::vertex(painterRef, p);
        } else {
            if (canDisplay){
                Displayer::vertex(painterRef, p);
            }
        }

        Displayer::vertex(painterRef, p);
        p.x += xIncrement;
        p.y += yIncrement;
    }
}

void Displayer::vertex(QPainter* painterRef, const Vertex& v){
    Displayer::point(painterRef, v.point);
}

void Displayer::point(QPainter* painterRef, const Point& point){
    painterRef->drawPoint(point.x, point.y);
}
