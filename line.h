#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "vertex.h"

enum LineType {
    NormalLine,
    IntermitentLine
};

class Line
{
public:
    Vertex vertex1;
    Vertex vertex2;

    int intermitentSeparationWidth;
    LineType lineType;

    Line();
    ~Line();

    Line copy() const;

    Line(const Vertex& vertex1, const Vertex& vertex2);
    Line(const Point& p1, const Point& p2);
    Line(double, double, double, double, double, double);

    void transform(const Matrix&);
};

#endif // LINE_H
