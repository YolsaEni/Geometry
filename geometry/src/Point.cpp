

#include <Point.h>
#include <Edge.h>

namespace li {
    Point::Point(double _x, double _y) : x(_x), y(_y) {}

    Point Point::operator+(const Point &p) {
        return Point(x + p.x, y + p.y);
    }

    Point Point::operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    Point &Point::scale_x(double sx) {
        x *= sx;
        return *this;
    }

    Point &Point::scale_y(double sy) {
        y *= sy;
        return *this;
    }

    Point &Point::scaleIndependent(double sx, double sy){
        return scale_x(sx).scale_y(sy);
    }

    Point operator*(double s, const Point &p) {
        return Point(s * p.x, s * p.y);
    }

    double Point::operator[](int i) {
        return (i == 0) ? x : y;
    }

    int Point::operator==(Point &p) {
        return (x == p.x) && (y == p.y);
    }

    int Point::operator!=(Point &p) {
        return !(*this == p);
    }

    int Point::operator<(Point &p) {
        return ((x < p.x) || ((x == p.x) && (y < p.y)));
    }

    int Point::operator>(Point &p) {
        return ((x > p.x) || ((x == p.x) && (y > p.y)));
    }

    int Point::classify(Point &p0, Point &pl) {
        Point p2 = *this;
        Point a = pl - p0;
        Point b = p2 - p0;
        double sa = a.x * b.y - b.x * a.y;
        if (sa > 0.0)
            return LEFT;
        if (sa < 0.0)
            return RIGHT;
        if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
            return BEHIND;
        if (a.length() < b.length())
            return BEYOND;
        if (p0 == p2)
            return ORIGIN;
        if (pl == p2)
            return DESTINATION;
        return BETWEEN;
    }

    int Point::classify(Edge &e) {
        return classify(e.org, e.dest);
    }

    double Point::polarAngle(void) {
        if ((x == 0.0) && (y == 0.0))
            return -1.0;
        if (x == 0.0)
            return ((y > 0.0) ? 90 : 270);
        double theta = xjatan(y / x); // in radians
        theta *= 360 / (2 * XJ_PI); // convert to degrees
        if (x > 0.0) // quadrants 1 and 4
            return ((y >= 0.0) ? theta : 360 + theta);
        else // quadrants 2 and 3
            return (180 + theta);
    }

    double Point::length(void) const {
        return xjsqrt(x * x + y * y);
    }

    double Point::norm(int p) const {
        return length();
    }

    double Point::distance(Edge &e) {
        Edge ab = e;
        ab.flip().rot();
        Point n(ab.dest - ab.org);
        n = (1.0 / n.length()) * n;
        Edge f(*this, *this + n);
        double t;
        f.intersect(e, t);
        return t;
    }

    void Point::log(int matrixForm, int useEndl) {
        if (matrixForm) {
            std::cout << x << " " << y;
        } else {
            std::cout << *this;
        }
        if (useEndl)
            std::cout << std::endl;
    }

    WXJ_BOOL Point::isZero() const {
        return (x == 0) && (y == 0);
    }

    Point Point::unit() {
        if (!isZero())
            return 1 / length() * (*this);
        else
            return Point();
    }

    Point Point::normal() {
        return unit().rot();
    }

    Point &Point::rot(void) {
        double t = x;
        x = y;
        y = -t;
        return *this;
    }

    double Point::dotProduct(const Point &p) const {
        return x * p.x + y * p.y;
    }

    double Point::crossProduct(const Point &p) const {
        return x * p.y - y * p.x;
    }

    double Point::angle(const Point &p) const {
        if (isZero() || p.isZero()) {
            return 0;
        }
        WXJ_DOUBLE angle0;
        angle0 = dotProduct(p) / (norm() * p.norm());
        return xjacos(angle0);
    }

    double Point::angleClockwise() const {
        double angle2 = angle(Point(1.0, 0.0));
        if (y < 0) {
            angle2 = 2 * XJ_PI - angle2;
        }
        return angle2;
    }

    double Point::angleClockwise(const Point &p) {
        double angle_a, angle_b, angle;
        angle_b = angleClockwise();
        angle_a = p.angleClockwise();
        angle = angle_b - angle_a;
        if (angle < 0) {
            angle = 2 * XJ_PI + angle;
        }
        return angle;
    }

    WXJ_BOOL Point::isTurningRight(const Point &point) {
        return Point(y, -x).dotProduct(point) >= 0 ? 1 : 0;
    }

    PointCommaInitializer<double> Point::operator<<(const double &s) {
        return PointCommaInitializer<double>(*this, s);
    }

    std::ostream &operator<<(std::ostream &io, li::Point &p) {
        io << "{x: " << p.x << ", y: " << p.y << "} ";
        return io;
    }

    std::istream &operator>>(std::istream &io, li::Point &p) {
        io >> p.x;
        asst_assert(!io.eof() && !io.fail()
                    && "Too many or too few coefficients passed to comma initializer (operator<<)");
        io >> p.y;

        return io;
    }

}
