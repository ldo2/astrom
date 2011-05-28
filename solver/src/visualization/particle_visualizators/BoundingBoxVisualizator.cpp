#include "BoundingBoxVisualizator.hpp"

#include <GL/gl.h>

/*
 * class BoundingBoxVisualizator
 */

  BoundingBoxVisualizator::BoundingBoxVisualizator() {}

  void BoundingBoxVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    double sfield1_value, 
    double sfield2_value, 
    double sfield3_value, 
    double sfield4_value
  ) {
    bounding_box += Geom::BoundingBox3D(position, radius);
  }

  void BoundingBoxVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    const Geom::Vector3D &vfield_value, 
    double sfield_value
  ) {
    bounding_box += Geom::BoundingBox3D(position, radius);
  }

  void BoundingBoxVisualizator::render_bounding_box() {
    glColor4f(1.0, 0.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);

    glBegin(GL_LINES);
      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.min.z);
      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.min.z);

      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.min.z);
      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.min.z);

      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.min.z);
      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.max.z);
//
      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.max.z);
      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.max.z);

      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.max.z);
      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.min.z);

      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.max.z);
      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.max.z);
//
      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.max.z);
      glVertex3d(bounding_box.min.x, bounding_box.min.y, bounding_box.max.z);

      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.max.z);
      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.min.z);

      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.max.z);
      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.max.z);
//
      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.min.z);
      glVertex3d(bounding_box.min.x, bounding_box.max.y, bounding_box.min.z);

      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.min.z);
      glVertex3d(bounding_box.max.x, bounding_box.min.y, bounding_box.min.z);

      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.min.z);
      glVertex3d(bounding_box.max.x, bounding_box.max.y, bounding_box.max.z);
    glEnd();

    glDisable(GL_DEPTH_TEST);
  }

