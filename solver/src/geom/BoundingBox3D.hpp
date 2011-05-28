#ifndef __Geom_BoundingBox3D_HPP__
#define __Geom_BoundingBox3D_HPP__

#include <iostream>
#include <limits>

#include <geom/Vector3D.hpp>

namespace Geom {

  class BoundingBox3D {
    public:
      Vector3D min, max;

      BoundingBox3D() {
        double infinity = std::numeric_limits<double>::infinity();
        min.x = min.y = min.z =  infinity;
        max.x = max.y = max.z = -infinity;
      }
      BoundingBox3D(const Vector3D &center, double radius) 
       : min(center.x - radius, center.y - radius, center.z - radius), 
         max(center.x + radius, center.y + radius, center.z + radius) {}
      BoundingBox3D(const Vector3D &minmax) 
       : min(minmax), max(minmax) {}
      BoundingBox3D(const Vector3D &min, const Vector3D &max) 
       : min(min), max(max) {}

      bool contain(Vector3D &point);
      bool contain(Vector3D &point, double radius);

  };

  BoundingBox3D operator +(const BoundingBox3D &a, const BoundingBox3D &b);
  BoundingBox3D operator +(const BoundingBox3D &a, const Vector3D &b);

  BoundingBox3D &operator +=(BoundingBox3D &a, const BoundingBox3D &b);
  BoundingBox3D &operator +=(BoundingBox3D &a, const Vector3D &b);

  std::ostream &operator <<(std::ostream &out, const BoundingBox3D &bbox);

}

#endif /* __Geom_BoundingBox3D_HPP__ */

