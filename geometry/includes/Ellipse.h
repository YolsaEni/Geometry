#pragma once

#include "geometry_inner.h"
//#include "Edge.h"

namespace li {

    class Ellipse
    {
    public:
        Ellipse();
        /**
         * @brief alge2geom:    algebraic parameters to geometric parameters
         * @ref:    https://en.wikipedia.org/wiki/Ellipse#In_analytic_geometry
         *          http:homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/FITZGIBBON/ELLIPSE/
         * @note:   The calculation of phi refer to wikipedia is not correct,
         *          refer to Bob Fisher's matlab program.
         *          What's more, the calculated geometric parameters can't back to
         *          initial algebraic parameters from geom2alge();
         */
        void alge2geom();
        /**
         * @brief geom2alge:    geometric parameters to algebraic parameters
         * @ref:    https://en.wikipedia.org/wiki/Ellipse#In_analytic_geometry
         */
        void geom2alge();

        void log();

        WXJ_BOOL isEmpty();

        int setCanonicalForm(double cx,double cy,double rl,double rs,double phi);
        int setGeneralForm(double a,double b,double c,double d,double e,double f);
    public:
        //algebraic parameters as coefficients of conic section
        double a, b, c, d, e, f;
        WXJ_BOOL  algeFlag;

        //geometric parameters
        double cx;   //center in x coordinate
        double cy;   //center in y coordinate
        double rl;   //semi-major: large radius
        double rs;   //semi-minor: small radius
        double phi;  //azimuth angel in radian unit

        WXJ_BOOL geomFlag;

    };
}