#ifndef __IParticleVisualizator_HPP__
#define __IParticleVisualizator_HPP__

#include <visualization/RangeColorMap.hpp>

#include <geom/Vector3D.hpp>

class IParticleVisualizator {
  protected:
    RangeColorMap *color_map;

  public:
    IParticleVisualizator(RangeColorMap *color_map = NULL);
    virtual ~IParticleVisualizator() {}

    virtual void set_color_map(RangeColorMap *new_color_map);

    virtual void render(const Geom::Vector3D &position, double radius,
                        double sfield1_value = 0.0, 
                        double sfield2_value = 0.0, 
                        double sfield3_value = 0.0, 
                        double sfield4_value = 0.0) = 0;

    virtual void render(const Geom::Vector3D &position, double radius,
                        const Geom::Vector3D &vfield_value, 
                        double sfield_value = 0.0) = 0;

};

#endif /* __IParticleVisualizator_HPP__ */

