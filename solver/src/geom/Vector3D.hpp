#ifndef __Geom_Vector3D_HPP__
#define __Geom_Vector3D_HPP__

#include <iostream>
#include <cmath>

namespace Geom {

  class Vector3D {
    public:
      union {
        double coordinates[3];
        struct {
          double x, y, z;
        };
      };

      Vector3D() {}
      Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
  };

  /* Vector3D Interface */

  inline std::ostream &operator <<(std::ostream &out, const Vector3D &v);

  inline Vector3D operator +(const Vector3D &va, const Vector3D &vb);
  inline Vector3D operator -(const Vector3D &va, const Vector3D &vb);
  inline Vector3D operator *(const Vector3D &va, const Vector3D &vb);
  inline Vector3D operator /(const Vector3D &va, const Vector3D &vb);

  inline Vector3D operator *(const Vector3D &v, const double &scal);
  inline Vector3D operator *(const double &scal, const Vector3D &v);
  inline Vector3D operator /(const Vector3D &v, const double &scal);

  inline Vector3D operator -(const Vector3D &v);

  inline Vector3D &operator +=(Vector3D &va, const Vector3D &vb);
  inline Vector3D &operator -=(Vector3D &va, const Vector3D &vb);
  inline Vector3D &operator *=(Vector3D &va, const Vector3D &vb);
  inline Vector3D &operator /=(Vector3D &va, const Vector3D &vb);


  inline Vector3D &operator *=(Vector3D &v, const double &scal);
  inline Vector3D &operator /=(Vector3D &v, const double &scal);

  // inline bool operator ==(const Vector3D &va, const Vector3D &vb);
  // inline bool operator !=(const Vector3D &va, const Vector3D &vb);

  inline double   length(const Vector3D &v);
  inline double   distance(const Vector3D &va, const Vector3D &vb);
  inline Vector3D normalize(const Vector3D &v);
  inline double   dot(const Vector3D &va, const Vector3D &vb);
  inline Vector3D cross(const Vector3D &va, const Vector3D &vb);
  inline Vector3D reflect(const Vector3D &v, const Vector3D &n);
  inline Vector3D refract(const Vector3D &v, const Vector3D &n, const double eta);

  /* Vector3D Implementation */

  inline std::ostream &operator <<(std::ostream &out, const Vector3D &v) {
    out << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ")";
    // out << v.x << " " << v.y << " " << v.z;
    return out;
  }

  inline Vector3D operator +(const Vector3D &va, const Vector3D &vb) {
    return Vector3D(va.x + vb.x, va.y + vb.y, va.z + vb.z);
  }

  inline Vector3D operator -(const Vector3D &va, const Vector3D &vb) {
    return Vector3D(va.x - vb.x, va.y - vb.y, va.z - vb.z);
  }

  inline Vector3D operator *(const Vector3D &va, const Vector3D &vb) {
    return Vector3D(va.x*vb.x, va.y*vb.y, va.z*vb.z);
  }

  inline Vector3D operator /(const Vector3D &va, const Vector3D &vb) {
    return Vector3D(va.x/vb.x, va.y/vb.y, va.z/vb.z);
  }

  inline Vector3D operator *(const Vector3D &v, const double &scal) {
    return Vector3D(v.x*scal, v.y*scal, v.z*scal);
  }

  inline Vector3D operator *(const double &scal, const Vector3D &v) {
    return Vector3D(v.x*scal, v.y*scal, v.z*scal);
  }

  inline Vector3D operator /(const Vector3D &v, const double &scal) {
    return Vector3D(v.x/scal, v.y/scal, v.z/scal);
  }

  inline Vector3D operator -(const Vector3D &v) {
    return Vector3D(-v.x, -v.y, -v.z);
  }

  inline Vector3D &operator +=(Vector3D &va, const Vector3D &vb) {
    va.x += vb.x;
    va.y += vb.y;
    va.z += vb.z;

    return va;
  }

  inline Vector3D &operator -=(Vector3D &va, const Vector3D &vb) {
    va.x -= vb.x;
    va.y -= vb.y;
    va.z -= vb.z;

    return va;
  }

  inline Vector3D &operator *=(Vector3D &va, const Vector3D &vb) {
    va.x *= vb.x;
    va.y *= vb.y;
    va.z *= vb.z;

    return va;
  }

  inline Vector3D &operator /=(Vector3D &va, const Vector3D &vb) {
    va.x /= vb.x;
    va.y /= vb.y;
    va.z /= vb.z;

    return va;
  }

  inline Vector3D &operator *=(Vector3D &v, const double &scal) {
    v.x *= scal;
    v.y *= scal;
    v.z *= scal;

    return v;
  }

  inline Vector3D &operator /=(Vector3D &v, const double &scal) {
    v.x /= scal;
    v.y /= scal;
    v.z /= scal;

    return v;
  }

  inline double length(const Vector3D &v) {
    return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  }

  inline double distance(const Vector3D &va, const Vector3D &vb) {
    double dx, dy, dz;

    dx = va.x - vb.x; 
    dy = va.y - vb.y; 
    dz = va.z - vb.z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
  }

  inline Vector3D normalize(const Vector3D &v) {
    double scal = length(v);
    
    if (scal != 0.0) {
      return Vector3D(v.x/scal, v.y/scal, v.z/scal);
    }

    return Vector3D(0.0, 0.0, 0.0); // error
  }

  inline double dot(const Vector3D &va, const Vector3D &vb) {
    return va.x*vb.x + va.y*vb.y + va.z*vb.z;
  }

  inline Vector3D cross(const Vector3D &va, const Vector3D &vb) {
    return Vector3D(va.y*vb.z - va.z*vb.y,
				            va.z*vb.x - va.x*vb.z,
				            va.x*vb.y - va.y*vb.x);
  }

  inline Vector3D reflect(const Vector3D &v, const Vector3D &n) {
    return v - 2*dot(n, v)*n;
  }

  inline Vector3D refract(const Vector3D &v, const Vector3D &n, 
                           const double eta) {
    double dot_n_v = dot(n, v);
    double k = 1.0 - eta * eta * (1.0 - dot_n_v*dot_n_v);

    if (k >= 0.0) {
      return eta*v - (eta*dot_n_v + std::sqrt(k))*n;
    }

    return Vector3D(0.0, 0.0, 0.0); // error
  }

}

#endif /* __Geom_Vector3D_HPP__ */

