#pragma once

#include "Vertex.h"
#include "Edge.h"

namespace li {

    // Todo: 3d polygon.

    /*
     * All polygon class, include convex and concave polygon.
     * */
    class Polygon {
    private:
        Vertex *_v;
        int _size;

        //In general, resize must be called whenever a vertex chain of unknown length is added to or removed from a polygon.
        void resize(void);

    public:
        //The constructor that takes no arguments initializes an empty polygon.
        Polygon(void);

        //The copy constructor takes some polygon p and initializes a new polygon with p.
        Polygon(const Polygon &);

        Polygon(Vertex *);

        ~Polygon(void);

        //Todo: optimize
        Polygon &operator=(const Polygon &p);

        Vertex *v(void) const;

        int size(void) const;

        Point point(void) const;

        Edge edge(void);

        Vertex *cw(void);

        Vertex *ccw(void);

        Vertex *neighbor(int rotation);

        //Member functions advance and setV move the window over a different vertex;
        Vertex *advance(int rotation);

        //Member function setV moves the window over the vertex v supplied as an argument.
        Vertex *setV(Vertex *);

        //Member function insert inserts a new vertex after the current vertex and then moves the window over the new vertex.
        Vertex *insert(Point &);

        //Member function remove removes the current vertex. The window is moved over the predecessor, or is undefined if the polygon is now empty.
        void remove(void);

        //Function split splits this polygon along the chord connecting its current vertex to vertex b. It returns a pointer to the new polygon, whose window is placed over bp, the duplicate of b. This polygon's window is not moved:
        // The function must be used with some care.
        Polygon *split(Vertex *);

        //log
        void log(int matrixForm = 0, int useEndl = 1);

        void clear();

        WXJ_BOOL isEmpty();

        // check whether polygon which must is in clockwise is convex
        WXJ_BOOL isConvex();

        //area of this polygon. The polygon can be convex or concave.
        double area();
    };

    /////////////////////

    // Polygon is in clockwise. If using opencv, Polygon should be set in ccw.
    // p is convex polygon.
    WXJ_BOOL pointInConvexPolygon(Point &s, Polygon &p);

    //Function leastVertex moves p's window over the least vertex and returns the vertex
    Vertex *leastvertex(Polygon &p, int (*cmp)(Point *, Point *));


    int leftToRightCmp(Point *a, Point *b);

    int rightToLeftCmp(Point *a, Point *b);
}