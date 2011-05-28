#include "ParticleSystemVisualizationAdaptor.hpp"

namespace sph {

/*
 * class ParticleSystemVisualizationAdaptor
 */

  ParticleSystemVisualizationAdaptor::ParticleSystemVisualizationAdaptor(
    ParticleSystem *system,  
    const ParticleField &field
  ) : system(system), field(field) {}

  void ParticleSystemVisualizationAdaptor::set_field(
    const ParticleField &new_field
  ) {
    field = new_field;
  }

  void ParticleSystemVisualizationAdaptor::render_each_with(
    IParticleVisualizator &visualizator
  ) {
    std::vector<Particle>::iterator particle;
    const double radius = system->kernel->get_smoothing_length();
    int state = system->state;

    for (particle = system->particles.begin(); 
          particle != system->particles.end(); 
           ++particle) {
      ParticleState &particle_state = particle->states[state];

      switch (field.type) {
        case ParticleField::SCALAR:
          visualizator.render(particle_state.position, radius, 
                               particle_state.*field.scalar);
          break;
        case ParticleField::VECTOR:
          visualizator.render(particle_state.position, radius, 
                               particle_state.*field.vector);
          break;
      }
    }

      /* 
         value = dot( //particle->states[state].external_force, 
                      // particle->states[state].acceleration,
                      particle->states[state].velocity,
                      normalize(particle->states[state].position) );
       */
  }

}

