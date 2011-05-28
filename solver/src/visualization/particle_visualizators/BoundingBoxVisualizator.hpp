#ifndef __BoundingBoxVisualizator_HPP__
#define __BoundingBoxVisualizator_HPP__

#include <Camera.hpp>

#include <geom/Vector3D.hpp>
#include <geom/BoundingBox3D.hpp>

#include <visualization/IParticleVisualizator.hpp>

class BoundingBoxVisualizator : public IParticleVisualizator {
  public:
    Geom::BoundingBox3D bounding_box;

    BoundingBoxVisualizator();

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0);

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0);

    void render_bounding_box();

};

#endif /* __BoundingBoxVisualizator_HPP__ */

