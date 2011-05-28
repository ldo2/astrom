#include "BoundingBox3D.hpp"

#include <cmath>

namespace Geom {

  BoundingBox3D operator +(const BoundingBox3D &a, const BoundingBox3D &b) {
    return BoundingBox3D(
      Vector3D(
        std::min(a.min.x, b.min.x), 
        std::min(a.min.y, b.min.y), 
        std::min(a.min.z, b.min.z)
      ),
      Vector3D(
        std::max(a.max.x, b.max.x), 
        std::max(a.max.y, b.max.y), 
        std::max(a.max.z, b.max.z)
      )
    );
  }

  BoundingBox3D operator +(const BoundingBox3D &a, const Vector3D &b) {
    return BoundingBox3D(
      Vector3D(
        std::min(a.min.x, b.x), 
        std::min(a.min.y, b.y), 
        std::min(a.min.z, b.z)
      ),
      Vector3D(
        std::max(a.max.x, b.x), 
        std::max(a.max.y, b.y), 
        std::max(a.max.z, b.z)
      )
    );
  }

  BoundingBox3D &operator +=(BoundingBox3D &a, const BoundingBox3D &b) {
    if(a.min.x > b.min.x) a.min.x = b.min.x;
    if(a.min.y > b.min.y) a.min.y = b.min.y;
    if(a.min.z > b.min.z) a.min.z = b.min.z;

    if(a.max.x < b.max.x) a.max.x = b.max.x;
    if(a.max.y < b.max.y) a.max.y = b.max.y;
    if(a.max.z < b.max.z) a.max.z = b.max.z;

    return a;
  }

  BoundingBox3D &operator +=(BoundingBox3D &a, const Vector3D &b) {
    if(a.min.x > b.x) a.min.x = b.x;
    if(a.min.y > b.y) a.min.y = b.y;
    if(a.min.z > b.z) a.min.z = b.z;

    if(a.max.x < b.x) a.max.x = b.x;
    if(a.max.y < b.y) a.max.y = b.y;
    if(a.max.z < b.z) a.max.z = b.z;

    return a;
  }

  std::ostream &operator <<(std::ostream &out, const BoundingBox3D &bbox) {
    out << "BoundingBox3D {"
        << "x: [" << bbox.min.x << ", " << bbox.max.x  << "], "
        << "y: [" << bbox.min.y << ", " << bbox.max.y  << "], "
        << "z: [" << bbox.min.z << ", " << bbox.max.z  << "]"
        << "}";

    return out;
  }

  bool BoundingBox3D::contain(Vector3D &point) {
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
  }

  bool BoundingBox3D::contain(Vector3D &point, double radius) {
    return point.x >= min.x - radius && point.x <= max.x + radius &&
           point.y >= min.y - radius && point.y <= max.y + radius &&
           point.z >= min.z - radius && point.z <= max.z + radius;
  }

}

