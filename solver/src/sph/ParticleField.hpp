#ifndef __sph_ParticleField_HPP__
#define __sph_ParticleField_HPP__

#include <sph/Particle.hpp>

namespace sph {

  class ParticleField {
    public:
      enum {
        SCALAR,
        VECTOR
      } type;

      union {
        double ParticleState::*scalar;
        Geom::Vector3D ParticleState::*vector;
      };

      ParticleField(double ParticleState::*scalar_field)
       : type(SCALAR), scalar(scalar_field) {}

      ParticleField(Geom::Vector3D ParticleState::*vector_field) 
       : type(VECTOR), vector(vector_field) {}
  };

}

#endif /* __sph_ParticleField_HPP__ */

