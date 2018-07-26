#pragma once

#include "Point3D.h"

namespace li {
    class Edge3D {
    public:
        Point3D org;
        Point3D dest;

        Edge3D(Point3D &_org, Point3D &_dest) :
                org(_org), dest(_dest) {}

        Edge3D(void) {}

        int intersect(Triangle3D &p, double &t);

        Point3D point(double t);
    };
}