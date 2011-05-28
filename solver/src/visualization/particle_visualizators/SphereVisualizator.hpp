#ifndef __SphereVisualizator_HPP__
#define __SphereVisualizator_HPP__

#include <Camera.hpp>

#include <geom/Vector3D.hpp>

#include <visualization/IParticleVisualizator.hpp>

#include <GL/gl.h>

#define DEFAULT_SPHERE_QUALITY (10)

class SphereVisualizator : public IParticleVisualizator {
  protected:
    double scale;
    GLuint sphere_display_list;

    void draw_sphere(const Geom::Vector3D &position, double radius);

  public:
    SphereVisualizator(const Camera &camera, double scale = 1.0,
                        int quality = DEFAULT_SPHERE_QUALITY);
    virtual ~SphereVisualizator();

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0);

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0);

};

#endif /* __SphereVisualizator_HPP__ */

