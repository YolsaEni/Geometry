#include <Ellipse.h>

namespace li {
    Ellipse::Ellipse() {
        algeFlag = XJ_FALSE;
        a = b = c = d = e = f = 0;

        geomFlag = XJ_FALSE;
        cx = cy = 0;
        rl = rs = 0;
        phi = 0;
    }

    void Ellipse::alge2geom() {
        if (!algeFlag)
            return;

        double tmp1 = b * b - 4 * a * c;
        double tmp2 = sqrt((a - c) * (a - c) + b * b);
        double tmp3 = a * e * e + c * d * d - b * d * e + tmp1 * f;

        double r1 = -sqrt(2 * tmp3 * (a + c + tmp2)) / tmp1;
        double r2 = -sqrt(2 * tmp3 * (a + c - tmp2)) / tmp1;
        rl = r1 >= r2 ? r1 : r2;
        rs = r1 <= r2 ? r1 : r2;

        cx = (2 * c * d - b * e) / tmp1;
        cy = (2 * a * e - b * d) / tmp1;

        phi = 0.5 * atan2(b, a - c);
        if (r1 > r2)
            phi += M_PI_2;

        geomFlag = XJ_TRUE;
    }

    void Ellipse::geom2alge() {
        if (!geomFlag)
            return;

        a = rl * rl * sin(phi) * sin(phi) + rs * rs * cos(phi) * cos(phi);
        b = 2 * (rs * rs - rl * rl) * sin(phi) * cos(phi);
        c = rl * rl * cos(phi) * cos(phi) + rs * rs * sin(phi) * sin(phi);
        d = -2 * a * cx - b * cy;
        e = -b * cx - 2 * c * cy;
        f = a * cx * cx + b * cx * cy + c * cy * cy - rl * rl * rs * rs;

        algeFlag = XJ_TRUE;
    }

    void Ellipse::log() {
        if (isEmpty()) {
            std::cout << "Ellipse is empty" << std::endl;
            return;
        }
        if (!algeFlag) {
            geom2alge();
        } else if (!geomFlag) {
            alge2geom();
        }
        std::cout << "Ellipse :"
                  << "\n\t" << "general form: " << a << " " << b << " " << c << " " << d << " " << e << " " << f
                  << "\n\t" << "canonical form: " << cx << " " << cy << " " << rl << " " << rs << " "
                  << xjradian2degree(phi)
                  << std::endl;
    }


    WXJ_BOOL Ellipse::isEmpty() {
        return (!algeFlag && !geomFlag);
    }

    int Ellipse::setCanonicalForm(double cx, double cy, double rl, double rs, double phi) {
        this->cx = cx;
        this->cy = cy;
        this->rl = rl;
        this->rs = rs;
        this->phi = phi;
        this->geomFlag = 1;
        geom2alge();
        return 1;
    }

    int Ellipse::setGeneralForm(double a, double b, double c, double d, double e, double f) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->e = e;
        this->f = f;
        this->algeFlag = 1;
        alge2geom();
        return 1;
    }
}