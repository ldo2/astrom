#ifndef __ParticleSystemVisualizationAdaptor_HPP__
#define __ParticleSystemVisualizationAdaptor_HPP__

#include <visualization/IParticlesVisualizationAdaptor.hpp>

#include <sph/ParticleSystem.hpp>
#include <sph/Particle.hpp>
#include <sph/ParticleField.hpp>

namespace sph {

  class ParticleSystemVisualizationAdaptor : public IParticlesVisualizationAdaptor {
    protected:
      ParticleSystem *system;
      ParticleField field;

    public:
      ParticleSystemVisualizationAdaptor(ParticleSystem *system,
                                          const ParticleField &field);

      void set_field(const ParticleField &field);

      virtual void render_each_with(IParticleVisualizator &visualizator);

  };

}

#endif /* __ParticleSystemVisualizationAdaptor_HPP__ */

