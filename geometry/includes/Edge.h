#pragma once

#include "Point.h"
#include "Point3D.h"

namespace li {
    enum {
        COLLINEAR, PARALLEL, SKEW, SKEW_CROSS, SKEW_NO_CROSS
    };

    /*
     * We will usually
refer to a directed line segment as an edge when it is the side of some polygon; the
edge is directed so that the polygon's interior lies to its right. An infinite (directed) line
is determined by two points and is directed from the first point to the second. A ray is a
semi-infinite line starting at the origin and passing through the destination.
     * The Edge class will be used to represent all forms of lines.
     * */
    class Edge {
    public:
        Point org;
        Point dest;

        Edge(const Point &_org, const Point &_dest);

        Edge(void);

        // rotate 90 degrees cw around middle point.
        Edge &rot(void);

        // flip around middle point.
        Edge &flip(void);

        //Todo: rotate d degrees cw around point.p.
        Edge &rot(Point &p, double d=90.0);

        Point point(double);

        // lines intersect.
        int intersect(Edge &, double &);

        //Member function Edge::cross returns SKEW_CROSS if and only if this line segment
        // intersects line segment e. If the line segments do intersect,
        // the parametric value along this line segment corresponding to the point of intersection is returned through reference parameter t.
        // Otherwise the function returns COLLINEAR, PARALLEL, or SKEW_NO_CROSS.
        int cross(Edge &e, double &t);

        // project point p to this line.
        // the parametric value along this line segment corresponding to the point of projection is returned
        double project(Point &p);

        bool isVertical(void);

        // Member function slope returns the slope of this edge, or DBL_MAX if this edge is vertical
        double slope(void);

        //Member function y is passed a value x and returns the value y such that (x, y) is a
        // point on this infinite line. The function is defined only if this edge is not vertical.
        double y(double);

        void log(int useEndl = 0);

        double length();

        // to point
        Point toPoint();

        //translate edge by p
        Edge &translate(Point const &p);

        // scale edge while keep org fixed, length can be negative.
        Edge &scaleLength(double length);

        // scale edge while keep the point with the parametric value t along this line segment fixed, scaleFactor can be negative.
        // for example, t =0.0 : scale edge while keep org fixed,
        // t = 0.5,  scale edge while keep middle point fixed.
        Edge &scale(double scaleFactor, double t=0.0);

        //return unit normal vector pointing to the line's right or zero if it degenerates.
        Point normal(void);

        //
        int operator==(Edge &);

        // angle: [0, PI], normal vector angle in vector space
        double angle(Edge &e);

        // angle: [0, 2*PI). angle from this edge to e in clockwise
        double angleClockwise(Edge &e);

        //
        WXJ_BOOL isZeroLength();

        //transform to (a, b, c) of line ax + by + c = 0;
        Point3D toLine();
    };

    // convert y = kx+b to Edge.
    // E_X is E(X)
    template<typename T>
    Edge LineToEdge(T k, T b, int isVertical, T E_X) {
        Point p1, p2;
        if (isVertical) {
            p1 = Point(E_X, 0);
            p2 = Point(E_X, 1);
        } else {
            p1 = Point(0, b);
            p2 = Point(1, k + b);
        }
        return Edge(p1, p2);
    }
}