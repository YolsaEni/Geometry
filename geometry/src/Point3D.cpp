#include <Point3D.h>
#include <Triangle3D.h>

namespace li {
    Point3D operator*(double s, const Point3D &p) {
        return Point3D(s * p.x, s * p.y, s * p.z);
    }

    int Point3D::classify(Triangle3D &p) {
        Point3D v = *this - p[0];
        double len = v.length();
        if (len == 0.0)
            return ON;
        v = (1.0 / len) * v;
        double d = v.dotProduct(p.n());
        if (d > EPSILON1)
            return POSITIVE;
        else if (d < -EPSILON1)
            return NEGATIVE;
        else
            return ON;
    }

    Point3D Point3D::crossProduct(const Point3D &p) {
        return Point3D(y * p.z - z * p.y,
                       z * p.x - x * p.z,
                       x * p.y - y * p.x);
    }

    Point3D Point3D::unit() {
        if (!isZero())
            return 1 / length() * (*this);
        else
            return Point3D();
    }

    double Point3D::length(void) {
        return xjsqrt(dotProduct(*this));
    }

    void Point3D::log(int matrixForm, int useEndl) {
        if (matrixForm) {
            std::cout << x << " " << y << " " << z;
        } else {
            std::cout << *this;
        }
        if (useEndl)
            std::cout << std::endl;
    }

    std::ostream &operator<<(std::ostream &io, li::Point3D &p) {
        io << "{x: " << p.x << ", y: " << p.y << ", z: " << p.z << "} ";
        return io;
    }

    std::istream &operator>>(std::istream &io, li::Point3D &p) {
        io >> p.x;
        asst_assert(!io.eof() && !io.fail()
                    && "Too many or too few coefficients passed to comma initializer (operator<<)");
        io >> p.y;
        asst_assert(!io.eof() && !io.fail()
                    && "Too many or too few coefficients passed to comma initializer (operator<<)");
        io >> p.z;
        return io;
    }

}
