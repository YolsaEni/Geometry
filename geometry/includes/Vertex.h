#pragma once

#include "Node.h"
#include "Point.h"

namespace li {
    enum {CLOCKWISE, COUNTER_CLOCKWISE}; // rotation
    class Vertex : public Node, public Point {
    public:
        Vertex(double x, double y);

        //must construct using Point. Should not use Vertex to construct.
        Vertex(const Point &);
//        Vertex(Point );

        //Member functions cw and ccw yield this vertex's successor and predecessor, respectively
        Vertex *cw(void);
        Vertex *ccw(void);

        Vertex *neighbor(int rotation);

        Point point(void);

        Vertex *insert(Vertex *);

        Vertex *remove(void);

        void splice(Vertex *);

        //The latter function partitions a polygon along the chord connecting this vertex (which plays the role of a) to vertex b. It returns a pointer to vertex bp, the duplicate of b.
        Vertex *split(Vertex *);

        friend class Polygon;
    };
}