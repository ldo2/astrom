#include "CircleVisualizator.hpp"

#include <cmath>

#include <GL/gl.h>

/*
 * class CircleVisualizator 
 */

  CircleVisualizator::CircleVisualizator(const Camera &camera, 
                                          double scale, int quality) 
   : scale(scale), circle_display_list(0) {
    circle_display_list = glGenLists(1);

    glNewList(circle_display_list, GL_COMPILE);
      glBegin(GL_LINE_LOOP);
        const double PI = 3.14159265358979;
        double phi;
        for (int segment = 0; segment < quality; ++segment) {
          phi = (2*PI*segment)/quality;
          glVertex3dv((std::cos(phi)*camera.right + 
                       std::sin(phi)*camera.up).coordinates);
        }
      glEnd();
    glEndList();
  }

  CircleVisualizator::~CircleVisualizator() {
    glDeleteLists(circle_display_list, 1);
  }

  void CircleVisualizator::render(
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
    draw_circle(position, scale*radius);
  }

  void CircleVisualizator::render(
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
    draw_circle(position, scale*radius);
  }

  void CircleVisualizator::draw_circle(
    const Geom::Vector3D &position, 
    double radius
  ) {
    glEnable(GL_DEPTH_TEST);
    
    glPushMatrix();
      glTranslated(position.x, position.y, position.z);
      glScaled(radius, radius, radius);

      glCallList(circle_display_list);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
  }

