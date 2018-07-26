#include <Edge3D.h>
#include <Edge.h>
#include <Triangle3D.h>

namespace li {

    //n * ((a +t(b-a)) -c) =0
    int Edge3D::intersect(Triangle3D &p, double &t) {
        Point3D a = org;
        Point3D b = dest;
        Point3D c = p[0]; // some point on the plane
        Point3D n = p.n();
        double denom = n.dotProduct(b - a);
        if (denom == 0.0) {
            int aclass = org.classify(p);
            if (aclass != ON)
                return PARALLEL;
            else
                return COLLINEAR;
        }
        double num = n.dotProduct(a - c);
        t = -num / denom;
        return SKEW;
    }

    Point3D Edge3D::point(double t) {
        return org + t * (dest - org);
    }

}
