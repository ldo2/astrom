#ifndef __Particle_HPP__
#define __Particle_HPP__

#include <geom/Vector3D.hpp>
#include <sph/IKernel.hpp>

namespace sph {

  class ParticleState {
    public:
      double mass;
      double density;
      double smoothed_density;
      double velocity_divergence;
      double time_step;
     
      Geom::Vector3D position;
      Geom::Vector3D velocity;
      Geom::Vector3D acceleration;

      Geom::Vector3D external_force;

      double pressure;
      double temperature;
      double energy;

      double density_rate;
      double energy_rate;
  };

  class Particle {
    public: 
      static const double G;
      static const double adiabatic_index;

      ParticleState states[2];
      IKernel *kernel;

      Particle() : kernel(NULL) {}

      template <class NeighborIterator>
      void calculate_density_rate(int state, NeighborIterator particle, NeighborIterator end);

      template <class NeighborIterator>
      void calculate_acceleration(int state, NeighborIterator particle, NeighborIterator end);

      template <class NeighborIterator>
      void calculate_energy_rate(int state, NeighborIterator particle, NeighborIterator end);

      template <class ParticleIterator>
      void calculate_gravity_force(int state, ParticleIterator particle, ParticleIterator end);

      void update_density(int begin_state, int end_state, double elapsed_time);

      void update_energy(int begin_state, int end_state, double elapsed_time);

      void update_positions(int begin_state, int end_state, double elapsed_time);

      void update_velocity(int begin_state, int end_state, double elapsed_time);

      void update_pressure(int state);

      double determine_max_time_step(int state);
      
  };

}

#include <sph/Particle.tcc>

#endif /* __Particle_HPP__ */

