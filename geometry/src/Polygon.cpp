#include <Polygon.h>

namespace li {
    Polygon::Polygon(void) : _v(NULL), _size(0) {
    }

    Polygon::Polygon(Polygon const &p) {
        _size = p._size;
        if (_size == 0)
            _v = NULL;
        else {
//            Point point = p.point();
//            _v = new Vertex(point);
//            for (int i = 1; i < _size; i++) {
//                p.advance(CLOCKWISE);
//                _v = _v->insert(new Vertex(p.point()));
//            }
//            p.advance(CLOCKWISE);
//            _v = _v->cw();

            Vertex *v = p.v();
            _v = new Vertex((Point) *v);
            for (int i = 1; i < _size; i++) {
                v = v->cw();
                _v = _v->insert(new Vertex((Point) *v));
            }
            _v = _v->cw();
        }
    }

    Polygon::Polygon(Vertex *v) : _v(v) {
        resize();
    }

    Polygon::~Polygon(void) {
        clear();
    }

    Polygon &Polygon::operator=(const Polygon &p) {
        if (this == &p) {
            return *this;
        }
//        if(_size!=p.size()){
        this->~Polygon();

        _size = p._size;
        if (_size == 0)
            _v = NULL;
        else {
            Vertex *v = p.v();
            _v = new Vertex((Point) *v);
            for (int i = 1; i < _size; i++) {
                v = v->cw();
                _v = _v->insert(new Vertex((Point) *v));
            }
            _v = _v->cw();
        }
//        }
        return *this;
    }

    void Polygon::resize(void) {
        if (_v == NULL)
            _size = 0;
        else {
            Vertex *v = _v->cw();
            for (_size = 1; v != _v; ++_size, v = v->cw()) {}
        }
    }

    Vertex *Polygon::v(void) const {
        return _v;
    }

    int Polygon::size(void) const {
        return _size;
    }

    Point Polygon::point(void) const {
        return _v->point();
    }

    Edge Polygon::edge(void) {
        return Edge(point(), _v->cw()->point());
    }

    Vertex *Polygon::cw(void) {
        return _v->cw();
    }

    Vertex *Polygon::ccw(void) {
        return _v->ccw();
    }

    Vertex *Polygon::neighbor(int rotation) {
        return _v->neighbor(rotation);
    }

    Vertex *Polygon::advance(int rotation) {
        return _v = _v->neighbor(rotation);
    }

    Vertex *Polygon::setV(Vertex *v) {
        return _v = v;
    }

    Vertex *Polygon::insert(const Point &p) {
        if (_size++ == 0)
            _v = new Vertex(p);
        else
            _v = _v->insert(new Vertex(p));
        return _v;
    }

    void Polygon::remove(void) {
        Vertex *v = _v;
        _v = (--_size == 0) ? NULL : _v->ccw();
        delete v->remove();
    }

    Polygon *Polygon::split(Vertex *b) {
        Vertex *bp = _v->split(b);
        resize();
        return new Polygon(bp);
    }

    void Polygon::log(int matrixForm, int useEndl) {
        if (isEmpty())return;
        std::cout << std::endl << "{" << std::endl;
        for (int i = 0; i < size(); i++) {
            if (!matrixForm)
                std::cout << "\t";
            advance(li::CLOCKWISE);
            if (matrixForm) {
                v()->log(matrixForm, 1);
            } else {
                v()->log();
            }
        }
        std::cout << std::endl << "}" << std::endl;

        if (useEndl)
            std::cout << std::endl;
    }


    void Polygon::clear() {
        if (_v) {
            Vertex *w = _v->cw();
            while (_v != w) {
                delete w->remove();
                w = _v->cw();
            }
            delete _v;
            _v = NULL;
            _size = 0;
        }
    }

    WXJ_BOOL Polygon::isEmpty() {
        return (_size == 0);
    }

    WXJ_BOOL Polygon::isConvex() {
        if (isEmpty()) {
            return 1;
        }
        Vertex *org = v();
        Edge pre = edge();
        Edge cur;
        for (int i = 0; i < size(); i++) {
            advance(CLOCKWISE);
            cur = edge();
            if (pre.toPoint().isTurningRight(cur.toPoint()) == 0) {
                setV(org);
                return 0;
            }
            pre = cur;
        }
        return 1;
    }

    double Polygon::area() {
        if (size() < 3) {
            return 0.0;
        }
        Point pre, cur;
        advance(CLOCKWISE);
        Point org = point();
        advance(CLOCKWISE);
        pre = point() - org;
        double sum = 0.0;
        for (int i = 2; i < size(); i++) {
            advance(CLOCKWISE);
            cur = point() - org;
            sum += pre.crossProduct(cur);
            pre = cur;
        }
        return xjabs(sum / 2);
    }

    Polygon &Polygon::scaleIndependent(double sx, double sy) {
        for (int i = 0; i < size(); i++) {
            advance(li::CLOCKWISE);
            v()->scaleIndependent(sx, sy);
        }
        return *this;
    }

    ////////////////////////////////

    WXJ_BOOL pointInConvexPolygon(Point &s, Polygon &p) {
        Edge e;
        if (p.isEmpty()) {
            return XJ_FALSE;
        }
        if (p.size() == 1) {
            return p.point() == s;
        }
        if (p.size() == 2) {
            e = p.edge();
            int c = s.classify(e);
            return ((c == BETWEEN) || (c == ORIGIN) | (c == DESTINATION));
        }
        Vertex *org = p.v();
        for (int i = 0; i < p.size(); i++, p.advance(CLOCKWISE)) {
            e = p.edge();
//            e.log();
//            s.log();
//            std::cout<<std::endl;
            if (s.classify(e) == LEFT) {
                p.setV(org);
                return XJ_FALSE;
            }
        }
        return XJ_TRUE;
    }

    Vertex *leastvertex(Polygon &p, int (*cmp)(Point *, Point *)) {
        Vertex *bestV = p.v();
        p.advance(CLOCKWISE);
        for (int i = 1; i < p.size(); p.advance(CLOCKWISE), i++)
            if ((*cmp)(p.v(), bestV) < 0)
                bestV = p.v();
        p.setV(bestV);
        return bestV;
    }

    int leftToRightCmp(Point *a, Point *b) {
        if (*a < *b) return -1;
        if (*a > *b) return 1;
        return 0;
    }

    int rightToLeftCmp(Point *a, Point *b) {
        return leftToRightCmp(b, a);
    }

    Polygon convert(const Edge &edge) {
        Polygon p;
        p.insert(edge.dest);
        p.insert(edge.org);
        return p;
    }
}




