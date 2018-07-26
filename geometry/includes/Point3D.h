#pragma once

#include "geometry_inner.h"
//#include "Edge.h"

namespace li {
    class Triangle3D;

#define EPSILON1 1E-12
    enum {
        POSITIVE, NEGATIVE, ON
    };

    /*
     * [Michael_J._Laszlo]_Computational_Geometry_and_Com
     * Point may be extended to a polynomial, or a matrix, or any point in a vector space rather than just a point in a plane.
     * */
    class Point3D {
    public:
        double x;
        double y;
        double z;

        Point3D(double _x=0.0, double _y=0.0, double _z=0.0) :
                x(_x), y(_y), z(_z) {}

//        Point3D(void) {}

        Point3D operator+(const Point3D &p) { return Point3D(x + p.x, y + p.y, z + p.z); }

        Point3D operator-(const Point3D &p) { return Point3D(x - p.x, y - p.y, z - p.z); }

        friend Point3D operator*(double, const Point3D &);

        int operator==(Point3D &p) { return ((x == p.x) && (y == p.y) && (z == p.z)); }

        int operator!=(Point3D &p) { return !(*this == p); }

        double operator[](int i) { return ((i == 0) ? x : ((i == 1) ? y : z)); }

        double dotProduct(const Point3D &p) { return (x * p.x + y * p.y + z * p.z); }

        // the function reports the half-space relative
        // to a given triangle p in which this point lies. The function returns POSITIVE
        // or NEGATIVE if this point lies in p's positive or negative half-space; it returns ON if this
        // point lies on the plane determined by p.
        /*
         * The function centers the plane of triangle tri within a slab of width 2 *EPSILON1.
         * A point which lies within this slab is considered to lie on the plane. This is intended to
         * avoid faulty decisions attributable to round-off, such as when a point on the plane appears
         * to lie off the plane due to limitations of representation.
         * */
        int classify(Triangle3D &p);

        // the cross product vector a x b is perpendicular to the plane spanned by vectors a and b,
        Point3D crossProduct(const Point3D &p);

        WXJ_BOOL isZero() const {
            return (x == 0) && (y == 0) && (z == 0);
        }

        //return unit vector of the vector or zero if it degenerates.
        Point3D unit();

        double length(void);

        void log(int matrixForm = 0, int useEndl = 0);
    };

    std::ostream &operator<<(std::ostream &io, li::Point3D &p);

    std::istream &operator>>(std::istream &io, li::Point3D &p);
}