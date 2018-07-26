#include <cstring>
#include "../geometry.h"

using namespace std;
using namespace li;

void test_List() {
    List<const char *> s;
    s.append("bat");
    s.append("ant");
    s.append("cat");
    cout << leastItem(s, strcmp);
}

void test_point_inside(){
    Point s;
    Polygon p;
    int index;
    s << 0, 0;
    p.insert(s);
    s << 0, 2;
    p.insert(s);
    s << 2, 2;
    p.insert(s);
    s << 2, 0;
    p.insert(s);
    s << 1, 1;
//    p.insert(s);
//    p.insert(s);

    p.log();
    index = pointInConvexPolygon(s, p);
    xjlogApp(index);
    xjlogApp("polygon.isConvex()", p.isConvex());
    xjlogApp("polygon.area()", p.area());


//    s = Point(0, 0);
//    index = pointInConvexPolygon(s, p);
//    xjlogApp(index);
}

void test_point_vector(){
    Point p;
    std::vector<Point> ps;
    ps.push_back(p);
}
void test_polygon_vector(){
    Point s;
    Polygon p;
    int index;
    s = Point(0,0);
    p.insert(s);
    s = Point(0,1);
    p.insert(s);
    s = Point(1,1);
    p.insert(s);
    s = Point(1,0);
    p.insert(s);

    std::vector<Polygon> ps;
    ps.push_back(p);
    ps[0].log();
    p.log();
}

void test_point_edge(){
    Edge e;
    Point s;
    int index;
    e = Edge(Point(0,0), Point(0,1));
    e.log();
    s= Point(-1,0);
    index = s.classify(e);
    xjlogApp(index);

    s= Point(0.5,0);
    index = s.classify(e);
    xjlogApp(index);

    s= Point(0,0);
    index = s.classify(e);
    xjlogApp(index);
}
void test_point3D(){
    Point3D p(1, 2, 3);
    p.log();
}
int main(int argc, char **argv) {
//    test_List();
//    test_point_inside();
//    test_point_edge();
//    test_polygon_vector();
//    test_point_vector();
    test_point3D();
    return 0;
}