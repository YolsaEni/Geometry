#include <Triangle3D.h>

namespace li {
#define min3(A, B, C) \
((A)<(B) ? ((A)<(C)?(A):(C)) : ((B)<(C)?(B):(C)))
#define max3(A, B, C) \
    ((A)>(B) ? ((A)>(C)?(A):(C)) : ((B)>(C)?(B):(C)))

    Triangle3D::Triangle3D(Point3D &v0, Point3D &v1, Point3D &v2,
                           int _id) {
        id = _id;
        mark = 0;
        _v[0] = v0;
        _v[1] = v1;
        _v[2] = v2;
        _boundingBox.org.x = min3(v0.x, v1.x, v2.x);
        _boundingBox.org.y = min3(v0.y, v1.y, v2.y);
        _boundingBox.org.z = min3(v0.z, v1.z, v2.z);
        _boundingBox.dest.x = max3(v0.x, v1.x, v2.x);
        _boundingBox.dest.y = max3(v0.y, v1.y, v2.y);
        _boundingBox.dest.z = max3(v0.z, v1.z, v2.z);
        _n = (v1 - v0).crossProduct(v2 - v0);
        _n = _n.unit();
    }
}
