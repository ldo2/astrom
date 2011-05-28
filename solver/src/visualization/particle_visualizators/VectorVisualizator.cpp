#include "VectorVisualizator.hpp"

#include <GL/gl.h>

/*
 * class VectorVisualizator 
 */

  VectorVisualizator::VectorVisualizator(const Camera &camera, double scale) 
   : du(camera.up + camera.right), dv(camera.up - camera.right), 
     scale(scale) {}

  void VectorVisualizator::render(
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

    Geom::Vector3D vfield_value(sfield1_value, sfield2_value, sfield3_value);

    Geom::Vector3D tangent    = normalize(vfield_value);
    Geom::Vector3D orthogonal = normalize(
      dot(vfield_value, dv) * du - dot(vfield_value, du) * dv
    );


    glBegin(GL_LINES);
      // glTexCoord2d(-1.0, 0.0);
      glVertex3dv(position.coordinates);
      // glTexCoord2d( 1.0, 0.0);
      glVertex3dv((position + scale * tangent).coordinates);

      glVertex3dv((position + 0.8 * scale * tangent + 
                    0.1 * scale * orthogonal).coordinates);
      glVertex3dv((position + scale * tangent).coordinates);
      glVertex3dv((position + 0.8 * scale * tangent - 
                    0.1 * scale * orthogonal).coordinates);
      glVertex3dv((position + scale * tangent).coordinates);
    glEnd();
  }

  void VectorVisualizator::render(
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

    Geom::Vector3D tangent    = normalize(vfield_value);
    Geom::Vector3D orthogonal = normalize(
      dot(vfield_value, dv) * du - dot(vfield_value, du) * dv
    );
  
    glBegin(GL_LINES);
      // glTexCoord2d(-1.0, 0.0);
      glVertex3dv(position.coordinates);
      // glTexCoord2d( 1.0, 0.0);
      glVertex3dv((position + scale * tangent).coordinates);

      glVertex3dv((position + 0.8 * scale * tangent + 
                    0.1 * scale * orthogonal).coordinates);
      glVertex3dv((position + scale * tangent).coordinates);
      glVertex3dv((position + 0.8 * scale * tangent - 
                    0.1 * scale * orthogonal).coordinates);
      glVertex3dv((position + scale * tangent).coordinates);
    glEnd();
  }

