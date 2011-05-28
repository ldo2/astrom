#ifndef __CircleVisualizator_HPP__
#define __CircleVisualizator_HPP__

#include <Camera.hpp>

#include <geom/Vector3D.hpp>

#include <visualization/IParticleVisualizator.hpp>

#include <GL/gl.h>

#define DEFAULT_CIRCLE_QUALITY (26)

class CircleVisualizator : public IParticleVisualizator {
  protected:
    double scale;
    GLuint circle_display_list;

    void draw_circle(const Geom::Vector3D &position, double radius);

  public:
    CircleVisualizator(const Camera &camera, double scale = 1.0,
                        int quality = DEFAULT_CIRCLE_QUALITY);
    virtual ~CircleVisualizator();

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0);

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0);

};

#endif /* __CircleVisualizator_HPP__ */

