#include "BillboardVisualizator.hpp"

#include <GL/gl.h>

/*
 * class BillboardVisualizator 
 */

  BillboardVisualizator::BillboardVisualizator(const Camera &camera) 
   : du(camera.up + camera.right), 
     dv(camera.up - camera.right) {}

  void BillboardVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    double sfield1_value, 
    double sfield2_value, 
    double sfield3_value, 
    double sfield4_value
  ) {
    glColor4f(sfield1_value, sfield2_value, sfield3_value, sfield4_value);

    glTexCoord2d( 1.0,  1.0);
    glVertex3dv((position + radius * du).coordinates);
    glTexCoord2d( 1.0, -1.0);
    glVertex3dv((position + radius * dv).coordinates);
    glTexCoord2d(-1.0, -1.0);
    glVertex3dv((position - radius * du).coordinates);
    glTexCoord2d(-1.0,  1.0);
    glVertex3dv((position - radius * dv).coordinates);
  }

  void BillboardVisualizator::render(
    const Geom::Vector3D &position, 
    double radius,
    const Geom::Vector3D &vfield_value, 
    double sfield_value
  ) {
    glColor4f(vfield_value.x, vfield_value.y, vfield_value.z, sfield_value);

    glTexCoord2d( 1.0,  1.0);
    glVertex3dv((position + radius * du).coordinates);
    glTexCoord2d( 1.0, -1.0);
    glVertex3dv((position + radius * dv).coordinates);
    glTexCoord2d(-1.0, -1.0);
    glVertex3dv((position - radius * du).coordinates);
    glTexCoord2d(-1.0,  1.0);
    glVertex3dv((position - radius * dv).coordinates);
  }

