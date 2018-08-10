#include <Edge.h>
#include <cfloat>

namespace li {
    Edge::Edge(const Point &_org, const Point &_dest) : org(_org), dest(_dest) {}

    Edge::Edge(void) : org(Point(0, 0)), dest(Point(1, 0)) {}

    Edge &Edge::rot(void) {
        Point m = 0.5 * (org + dest);
        Point v = dest - org;
        Point n(v.y, -v.x);
        org = m - 0.5 * n;
        dest = m + 0.5 * n;
        return *this;
    }

    // can swap org and dest.
    Edge &Edge::flip(void) {
        return rot().rot();
    }

    Edge &Edge::rot(Point &p, double d) {
        return *this;
    }

    Point Edge::point(double t) {
        return Point(org + t * (dest - org));
    }

//    double dotProduct(const Point &p, const Point &q) {
//        return (p.x * q.x + p.y * q.y);
//    }

    //n * ((a +t(b-a)) -c) =0
    int Edge::intersect(Edge &e, double &t) {
        Point a = org;
        Point b = dest;
        Point c = e.org;
        Point d = e.dest;
        Point n = Point((d - c).y, (c - d).x);
        double denom = n.dotProduct(b - a);
        if (denom == 0.0) {
            int aclass = org.classify(e);
            if ((aclass == LEFT) || (aclass == RIGHT))
                return PARALLEL;
            else
                return COLLINEAR;
        }
        double num = n.dotProduct(a - c);
        t = -num / denom;
        return SKEW;
    }

    int Edge::cross(Edge &e, double &t) {
        double s;
        int crossType = e.intersect(*this, s);
        if ((crossType == COLLINEAR) || (crossType == PARALLEL))
            return crossType;
        if ((s < 0.0) || (s > 1.0))
            return SKEW_NO_CROSS;
        intersect(e, t);
        if ((0.0 <= t) && (t <= 1.0))
            return SKEW_CROSS;
        else
            return SKEW_NO_CROSS;
    }

    // similar to function double Point::distance(Edge &e), but without signed distance.
    double Edge::project(Point &p) {
        if (isZeroLength()) {
            return 0.0;
        }
        Point n = normal();
        Edge f(p, p + n);
        double t;
        intersect(f, t);
        return t;
    }

    bool Edge::isVertical(void) {
        return (org.x == dest.x);
    }

    double Edge::slope(void) {
        if (org.x != dest.x)
            return (dest.y - org.y) / (dest.x - org.x);
        return DBL_MAX;
    }

    double Edge::y(double x) {
        return slope() * (x - org.x) + org.y;
    }

    void Edge::log(int useEndl) {
        org.log();
        dest.log();
        if (useEndl)
            std::cout << std::endl;
    }

    double Edge::length() const{
        Point n = dest - org;
        return xjsqrt(n.dotProduct(n));
    }

    Point Edge::toPoint() {
        return Point(dest - org);
    }

    Edge &Edge::translate(Point const &p) {
        org = org + p;
        dest = dest + p;
        return *this;
    }

    Edge &Edge::scaleLength(double newLength) {
        if (isZeroLength() == 0) {
            return scale(newLength / length());
        }
        return *this;
    }

    Edge &Edge::scale(double scaleFactor, double t) {
        Point p_pre = point(t);
        dest = point(scaleFactor);
        translate(p_pre-point(t));
        return *this;
    }

    Point Edge::normal(void) {
        return (dest - org).normal();
    }

    int Edge::operator==(Edge &e) {
        return (org == e.org) && (dest == e.dest);
    }

    double Edge::angle(Edge &e) {
        return this->toPoint().angle(e.toPoint());
    }

    double Edge::angleClockwise() {
        return this->toPoint().angleClockwise();
    }

    double Edge::angleClockwise(Edge &e) {
        return this->toPoint().angleClockwise(e.toPoint());
    }

    WXJ_BOOL Edge::isZeroLength() {
        return dest == org;
    }

    Point3D Edge::toLine(){
        return Point3D(dest.y-org.y, org.x-dest.x, dest.crossProduct(org));
    }

    Edge &Edge::scaleIndependent(double sx, double sy){
        org.scaleIndependent(sx, sy);
        dest.scaleIndependent(sx, sy);
        return *this;
    }
}

