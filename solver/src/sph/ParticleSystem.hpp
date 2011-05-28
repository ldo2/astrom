#ifndef __ParticleSystem_HPP__
#define __ParticleSystem_HPP__

#include <iostream>
#include <vector>

#include <GL/gl.h>

#include <sph/Particle.hpp>
#include <sph/IKernel.hpp>

namespace sph {

  class ParticleSystem {
    public:
      std::vector<Particle> particles;
      int state, next_state;
      IKernel *kernel;
      double elapsed_time;

      typedef std::vector<Particle>::iterator ParticleIterator;

      ParticleSystem(IKernel *kernel, int count = 0);

      void initialize(double max_time_step);
      void update(double max_time_step);
      void print();
  };

}

#endif /* __ParticleSystem_HPP__ */

