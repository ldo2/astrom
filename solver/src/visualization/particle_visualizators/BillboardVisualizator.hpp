#ifndef __BillboardVisualizator_HPP__
#define __BillboardVisualizator_HPP__

#include <Camera.hpp>

#include <geom/Vector3D.hpp>

#include <visualization/IParticleVisualizator.hpp>

class BillboardVisualizator : public IParticleVisualizator {
  protected:
    Geom::Vector3D du, dv;

  public:
    BillboardVisualizator(const Camera &camera);

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0);

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0);

};

#endif /* __BillboardVisualizator_HPP__ */

