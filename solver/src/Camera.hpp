#ifndef __Camera_HPP__
#define __Camera_HPP__

#include <geom/Vector3D.hpp>

#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

class Camera {
  public:
    Geom::Vector3D eye;
    Geom::Vector3D up;
    Geom::Vector3D view;
    Geom::Vector3D right;

    Camera()
     : eye(0.0, 0.0, 0.0), up(0.0, 0.0, 1.0), view(0.0, 1.0, 0.0), 
       right(cross(view, up)) {}
    Camera(Geom::Vector3D eye, Geom::Vector3D up, Geom::Vector3D view)
     : eye(eye), up(up), view(view), right(cross(view, up)) {}

    void rotate(double angle) {
      double cos_a = std::cos(angle), sin_a = std::sin(angle);
      double x, y;

      x =  cos_a*view.x + sin_a*view.y;
      y = -sin_a*view.x + cos_a*view.y;

      view.x = x;
      view.y = y;

      x =  cos_a*right.x + sin_a*right.y;
      y = -sin_a*right.x + cos_a*right.y;

      right.x = x;
      right.y = y;

      x =  cos_a*up.x + sin_a*up.y;
      y = -sin_a*up.x + cos_a*up.y;

      up.x = x;
      up.y = y;
    }

    void rotate_up(double angle) {
      double cos_a = std::cos(angle), sin_a = std::sin(angle);

      Geom::Vector3D new_up, new_view;

      new_up   =  cos_a * up + sin_a * view;
      new_view = -sin_a * up + cos_a * view;

      up   = new_up;
      view = new_view;
    }

    void bind() {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      Geom::Vector3D center = eye + view;
      gluLookAt(
        eye.x   , eye.y   , eye.z   ,
        center.x, center.y, center.z,
        up.x    , up.y    , up.z
      );
    }
};

inline std::ostream &operator <<(std::ostream &out, const Camera &camera) {
  out << "Camera {"
      << "eye: "   << camera.eye  << ", "
      << "view: "  << camera.view << ", "
      << "up: "    << camera.up   << ", "
      << "right: " << camera.right
      << "}";

  return out;
}

#endif /* __Camera_HPP__ */

