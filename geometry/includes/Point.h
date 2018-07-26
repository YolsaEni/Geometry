#pragma once

#include "geometry_inner.h"
//#include "Edge.h"

namespace li {
    class Edge;

    template<typename T>
    struct PointCommaInitializer;

    enum {
        LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION
    };

    /*
     * Point may be extended to a polynomial, or a matrix, or any point in a vector space rather than just a point in a plane.
     * */
    class Point {
    public:
        double x;
        double y;

        Point(double _x = 0.0, double _y = 0.0);

        Point operator+(const Point &);

        Point operator-(const Point &);

        friend Point operator*(double, const Point &);

        double operator[](int);

        int operator==(Point &);

        int operator!=(Point &);

        // Operators < and > implement the lexicographic order relation
        int operator<(Point &);

        int operator>(Point &);

        int classify(Point &, Point &);

        int classify(Edge &);

        double polarAngle(void);

        double length(void) const;

        // Todo: p!=2
        double norm(int p = 2) const;

        // This member function of class Point is passed an edge e, and it returns the
        // signed distance from this point to edge e. Here the distance from point p to
        // edge e equals the minimum distance from p to any point along the infinite line determined by e.
        // The signed distance is positive if p lies to the right of e, negative if p lies to the left of e, and zero if p is collinear with e.
        double distance(Edge &e);

        void log(int matrixForm=0, int useEndl = 0);

        WXJ_BOOL isZero() const;

        //return unit vector of the vector or zero if it degenerates.
        Point unit();

        //return unit normal vector pointing to the vector's right or zero if it degenerates.
        Point normal();

        Point &rot(void);

        double dotProduct(const Point &p) const;

        //return signed length of their cross product a x b
        double crossProduct(const Point &p) const;

        //angle: [0, PI], normal vector angle in vector space
        double angle(const Point &p) const;

        //angle: [0, 2*PI).  angle from this to Point( 1, 0) in clockwise.
        double angleClockwise() const;

        // angle: [0, 2*PI).  angle from this to p in clockwise.
        double angleClockwise(const Point &p);

        //
        WXJ_BOOL isTurningRight(const Point &point);


/** \anchor MatrixBaseCommaInitRef
  * Convenient operator to set the coefficients of a point.
  * The coefficients must match
  * the size of the point. Otherwise an assertion is raised.
  */
        PointCommaInitializer<double> operator<<(const double &s);
    };

    std::ostream &operator<<(std::ostream &io, li::Point &p);

    std::istream &operator>>(std::istream &io, li::Point &p);

    /** \class CommaInitializer
  * \brief Helper class used by the comma initializer operator
  * This class is internally used to implement the comma initializer feature.
  */
    template<typename T>
    struct PointCommaInitializer {
        inline PointCommaInitializer(Point &p, const T &s)
                : m_p(p), count(1) {
            p.x = s;
        }

        PointCommaInitializer &operator,(const T &s) {

            asst_assert(count == 1
                        && "Too many coefficients passed to comma initializer (operator<<)");
            m_p.y = s;
            count++;
            return *this;
        }

        inline ~PointCommaInitializer() {
            asst_assert(count == 2
                        && "Too few coefficients passed to comma initializer (operator<<)");
        }

        Point &m_p;   // target expression
        int count;
    };

}