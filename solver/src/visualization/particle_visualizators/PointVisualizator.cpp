#include "PointVisualizator.hpp"

#include <GL/gl.h>

/*
 * class PointVisualizator 
 */

  PointVisualizator::PointVisualizator(const Camera &camera, double point_size) 
   : point_size(point_size) {}

  PointVisualizator::~PointVisualizator() {}

  void PointVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    double sfield1_value, 
    double sfield2_value, 
    double sfield3_value, 
    double sfield4_value
  ) {
    if (color_map) {
      RGBA color = color_map->map(sfield1_value, sfield2_value, 
                                  sfield3_value, sfield4_value);
      glColor4ub(color.r, color.g, color.b, color.a);
    }
    // glColor4f(sfield1_value, sfield2_value, sfield3_value, sfield4_value);
    glEnable(GL_POINT_SMOOTH);

    glPointSize(point_size);
    
    glBegin(GL_POINTS);
      glVertex3dv(position.coordinates);
    glEnd();

    glDisable(GL_POINT_SMOOTH);
  }

  void PointVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    const Geom::Vector3D &vfield_value, 
    double sfield_value
  ) {
    if (color_map) {
      RGBA color = color_map->map(vfield_value, sfield_value);
      glColor4ub(color.r, color.g, color.b, color.a);
    }
    // glColor4f(vfield_value.x, vfield_value.y, vfield_value.z, sfield_value);
    glEnable(GL_POINT_SMOOTH);

    glPointSize(point_size);
    
    glBegin(GL_POINTS);
      glVertex3dv(position.coordinates);
    glEnd();

    glDisable(GL_POINT_SMOOTH);
  }

