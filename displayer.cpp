#include "displayer.h"
#include "vertex.h"
#include "surface.h"
#include "object3d.h"
#include "qpainterpath.h"

void Displayer::object3d(QPainter* painterRef, const Object3D& obj){
    for (Surface surface : obj.surfaces){
        Displayer::surface(painterRef, surface);
    }
}

void Displayer::surface(QPainter* painterRef, const Surface& originalSurface){
    Surface s = originalSurface.copy();
    float xv = 0, yv = 0, zv = 500;
    float zf = 1000;

    for (Vertex& v : s.vertices){
        float dp = (zf-zv)/(zf-v.z);
        v.y *= dp;
        v.x *= dp;
    }

    for (Vertex& v: s.vertices){
        xv += v.x;
        yv += v.y;
    }

    xv /= s.vertices.size();
    yv /= s.vertices.size();

    float x1 = s.vertices[0].x;
    float y1 = s.vertices[0].y;
    float z1 = s.vertices[0].z;

    float x2 = s.vertices[1].x;
    float y2 = s.vertices[1].y;
    float z2 = s.vertices[1].z;

    float x3 = s.vertices[2].x;
    float y3 = s.vertices[2].y;
    float z3 = s.vertices[2].z;

    float A=y1*(z2-z3)+y2*(z3-z1)+y3*(z1-z2);
    float B=z1*(x2-x3)+z2*(x3-x1)+z3*(x1-x2);
    float C=x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
    float D=-x1*(y2*z3-y3*z2)-x2*(y3*z1-y1*z3)-x3*(y1*z2-y2*z1);



    if (A*xv+B+yv+C*zv+D>0){
        Line *temp;
        for (int i = 0; i < (int)s.vertices.size() - 1; ++i) {
            Vertex* v1  = &s.vertices.at(i);
            Vertex* v2 = &s.vertices.at(i+1);

            temp = new Line(v1->x, v1->y, v1->z, v2->x, v2->y, v2->z);
            Displayer::line(painterRef, *temp);
            delete temp;
            //painterRef->drawLine(s.vertices.at(i).x, s.vertices.at(i).y, s.vertices.at(i+1).x, s.vertices.at(i+1).y);
        }

        Vertex* last = &s.vertices.at(s.vertices.size() -1 );
        Vertex* first = &s.vertices.at(0);

        temp = new Line(last->x, last->y, last->z, first->x, first->y, first->z);
        Displayer::line(painterRef, *temp);
        delete temp;
        //painterRef->drawLine(s.vertices.at(s.vertices.size() - 1).x, s.vertices.at(s.vertices.size() - 1).y, s.vertices.at(0).x, s.vertices.at(0).y);

        if (!s.vertices.empty()){
            QPainterPath path;

            path.moveTo(s.vertices[0].x, s.vertices[0].y);
            for (size_t i = 0; i < s.vertices.size(); i++){
                path.lineTo(s.vertices[i].x, s.vertices[i].y);
            }

            path.closeSubpath();

            painterRef->fillPath(path, QBrush(QColor::fromRgb(255,165,200)));
        }
    }
}

void Displayer::line(QPainter* painterRef, const Line& line){
    float dx = line.vertex2.x - line.vertex1.x;
    float dy = line.vertex2.y - line.vertex1.y;

    int pixelsToTravel = (abs(dx) > abs(dy) ? abs(dx) : abs(dy));
    float xIncrement = dx / pixelsToTravel;
    float yIncrement = dy /pixelsToTravel;

    Vertex p = line.vertex1.copy();

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
    painterRef->drawPoint(v.x, v.y);
}

