#include "ParticleSystem.hpp"

namespace sph {

    ParticleSystem::ParticleSystem(IKernel *kernel, int count) 
     : particles(count), state(0), next_state(1), kernel(kernel) {}

    void ParticleSystem::initialize(double max_time_step) {
      std::vector<Particle>::iterator particle; 

      for (particle = particles.begin(); particle != particles.end(); ++particle)
        particle->kernel = kernel;

      for (particle = particles.begin(); particle != particles.end(); ++particle)
        particle->calculate_gravity_force<ParticleIterator>(state, particles.begin(), particles.end());

      for (particle = particles.begin(); particle != particles.end(); ++particle)
        particle->calculate_acceleration<ParticleIterator>(state, particles.begin(), particles.end());

      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        particle->calculate_density_rate<ParticleIterator>(state, particles.begin(), particles.end());
        particle->calculate_energy_rate <ParticleIterator>(state, particles.begin(), particles.end());
      }

      elapsed_time = max_time_step;
      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        elapsed_time = std::min(elapsed_time, particle->determine_max_time_step(state));
      }
    }
 
    void ParticleSystem::update(double max_time_step) {
      std::vector<Particle>::iterator particle;

      for (particle = particles.begin(); particle != particles.end(); ++particle) 
        particle->update_positions(state, next_state, elapsed_time);
      
      for (particle = particles.begin(); particle != particles.end(); ++particle)
        particle->calculate_gravity_force<ParticleIterator>(next_state, particles.begin(), particles.end());

      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        particle->update_density (state, next_state, elapsed_time);
        particle->update_energy  (state, next_state, elapsed_time);
        particle->update_pressure(next_state);
      }

      for (particle = particles.begin(); particle != particles.end(); ++particle)
        particle->calculate_acceleration<ParticleIterator>(next_state, particles.begin(), particles.end());

      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        particle->update_velocity(state, next_state, elapsed_time);
      }

      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        particle->calculate_density_rate<ParticleIterator>(next_state, particles.begin(), particles.end());
        particle->calculate_energy_rate <ParticleIterator>(next_state, particles.begin(), particles.end());
      }

      std::cout << "search next step " << max_time_step << std::endl; 

      elapsed_time = max_time_step;
      int particle_index = 0, min_step_particle_index = 0;
      double particle_step;
      for (particle = particles.begin(); particle != particles.end(); ++particle) {
        particle_step = particle->determine_max_time_step(next_state);
        if (elapsed_time > particle_step) {
          elapsed_time = particle_step;
          min_step_particle_index = particle_index;
        }

        ++particle_index;
      }

      ParticleState &pstate = particles[min_step_particle_index].states[next_state];

      std::cout << "select step " << elapsed_time << " in " 
                << min_step_particle_index << " by " 
                << pstate.time_step << " "
                << pstate.velocity_divergence << " "
                << (pstate.energy_rate/pstate.energy) << " "
                << pstate.energy_rate << " "
                << pstate.energy << " "
                << pstate.density << " "
                << pstate.pressure << " on "
                << pstate.position
                << std::endl; 


      int swap;
      swap = state;
      state = next_state;
      next_state = swap;
    }

    void ParticleSystem::print() {
      std::vector<Particle>::iterator particle;

      std::cout << "*** Particles ***" << std::endl;
      //for (particle = particles.begin(); particle != particles.end(); ++particle) {
      particle = particles.begin();
        std::cout << particle->states[state].position << " "
                  << particle->states[state].density  << std::endl;
      //}
    }

}

