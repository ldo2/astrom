#ifndef __PointVisualizator_HPP__
#define __PointVisualizator_HPP__

#include <Camera.hpp>

#include <geom/Vector3D.hpp>

#include <visualization/IParticleVisualizator.hpp>

class PointVisualizator : public IParticleVisualizator {
  protected:
    double point_size;

  public:
    PointVisualizator(const Camera &camera, double point_size = 1.0);
    virtual ~PointVisualizator();

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0);

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0);

};

#endif /* __PointVisualizator_HPP__ */

