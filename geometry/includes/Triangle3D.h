#pragma once

#include "geometry_inner.h"
#include "Edge3D.h"

namespace li {
    /*
     * [Michael_J._Laszlo]_Computational_Geometry_and_Com
     *
     * The plane determined by a triangle subdivides space into two half-spaces. The
     * half-space into which the triangle's normal vector points is called the triangle's positive
     * half-space since the triangle appears to be positively oriented when viewed from this half-space.
     * The other half-space is called the triangle's negative half-space.
     * */
    class Triangle3D {
    private:
        Point3D _v[3];
        Edge3D _boundingBox;
        Point3D _n; //unit normal vector
    public:
        int id;
        int mark;

        Triangle3D(Point3D &vO, Point3D &vl, Point3D &v2, int id);

        Triangle3D(void);

        Point3D operator[](int i) { return _v[i]; }

        Edge3D boundingBox() { return _boundingBox; }

        //return unit normal vector or zero if it degenerates.
        Point3D n(void) { return _n; }

//        double length(void) { return sqrt(x * x + y * y + z * z); }
    };
}