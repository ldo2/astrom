#include "SphereVisualizator.hpp"

#include <GL/gl.h>

/*
 * class SphereVisualizator 
 */

  SphereVisualizator::SphereVisualizator(const Camera &camera, 
                                          double scale, int quality) 
   : scale(scale), sphere_display_list(0) {
    sphere_display_list = glGenLists(1);

    GLUquadric *sphere = gluNewQuadric();

    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    glNewList(sphere_display_list, GL_COMPILE);
      gluSphere(sphere, 1.0, quality, quality);
    glEndList();

    gluDeleteQuadric(sphere);
  }

  SphereVisualizator::~SphereVisualizator() {
    glDeleteLists(sphere_display_list, 1);
  }

  void SphereVisualizator::render(
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
    draw_sphere(position, scale*radius);
  }

  void SphereVisualizator::render(
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
    draw_sphere(position, scale*radius);
  }

  void SphereVisualizator::draw_sphere(
    const Geom::Vector3D &position, 
    double radius
  ) {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glPushMatrix();
      glTranslated(position.x, position.y, position.z);
      glScaled(radius, radius, radius);

      glCallList(sphere_display_list);
    glPopMatrix();
    
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_DEPTH_TEST);
  }

