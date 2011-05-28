#include "Particle.hpp"

namespace sph {
 
  const double Particle::G = 0.36; // 6.673e-11;
  const double Particle::adiabatic_index = 5.0/3.0;

  void Particle::update_density(int begin_state, int end_state, double elapsed_time) {
    states[end_state].density = states[begin_state].density + 
      states[begin_state].density_rate * elapsed_time;

    // states[end_state].density = states[begin_state].smoothed_density;
  }

  void Particle::update_energy(int begin_state, int end_state, double elapsed_time) {
    states[end_state].energy = states[begin_state].energy + 
      states[begin_state].energy_rate * elapsed_time;
  }

  void Particle::update_positions(int begin_state, int end_state, double elapsed_time) {
    states[end_state].position = states[begin_state].position + 
      states[begin_state].velocity * elapsed_time + 
      0.5 * states[begin_state].acceleration * elapsed_time * elapsed_time;
  }

  void Particle::update_velocity(int begin_state, int end_state, double elapsed_time) {
    states[end_state].velocity = states[begin_state].velocity + 
      0.5 * (states[begin_state].acceleration + states[end_state].acceleration) * 
      elapsed_time;
  /*
        std::cout 
          << " v" << begin_state << " " << dot(states[begin_state].velocity, normalize(states[begin_state].position))
          << " a" << begin_state << " " << dot(states[begin_state].acceleration, normalize(states[begin_state].position))
          << " a" << end_state << " " << dot(states[end_state].acceleration, normalize(states[begin_state].position))
          << " v" << end_state << " " << dot(states[end_state].velocity, normalize(states[begin_state].position))
          << std::endl;
   */
  }

  void Particle::update_pressure(int state) {
    // const double adiabatic_index = 5.0/3.0;
    states[state].pressure = (adiabatic_index - 1.0) * states[state].density * states[state].energy;
  }

  double Particle::determine_max_time_step(int state) {
    const double delay = 0.1;

    if (states[state].density == 0.0) {
      std::cout << "!!! alert: zero density" << std::endl;
    }

    return states[state].time_step = std::min(
      delay / std::max(1.0, std::fabs(states[state].velocity_divergence)), 
      delay / std::max(1.0, std::fabs(states[state].energy_rate/states[state].energy))
    );
  }

}

