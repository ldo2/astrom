
namespace sph {

  template <class NeighborIterator>
  void Particle::calculate_density_rate(int state, NeighborIterator particle, NeighborIterator end) {
    ParticleState *particle_i, *particle_j;

    particle_i = &states[state];

    particle_i->density_rate = 0.0;
    particle_i->smoothed_density = 0.0;
    particle_i->velocity_divergence = 0.0;

    for (; particle != end; ++particle) {
      particle_j = &particle->states[state];

      //particle_i->density_rate += particle_j->mass * (particle_i->density/particle_j->density) * 
      //  dot((particle_i->velocity - particle_j->velocity), dWdx(particle_j->position - particle_i->position));
      particle_i->density_rate += - particle_j->mass * (particle_i->density/particle_j->density) * 
        dot(particle_j->velocity, kernel->gradient(particle_j->position - particle_i->position));

      particle_i->velocity_divergence += particle_j->mass/particle_j->density * 
        dot(particle_j->velocity, kernel->gradient(particle_j->position - particle_i->position));

      particle_i->smoothed_density += particle_j->mass * 
        kernel->value(particle_j->position - particle_i->position);
    }
  }

  template <class NeighborIterator>
  void Particle::calculate_acceleration(int state, NeighborIterator particle, NeighborIterator end) {
    ParticleState *particle_i, *particle_j;
    // const double adiabatic_index = 5.0/3.0;
    double speed_of_sound_i, speed_of_sound_j, speed_of_sound,
           density;
    double viscosity_coefficient;

    const double alpha = 0.01, beta = 0.1;

    double artificial_viscosity;
    Geom::Vector3D velocity, distance;

    particle_i = &states[state];

    speed_of_sound_i = std::sqrt((adiabatic_index - 1.0)*particle_i->energy);

    particle_i->acceleration = particle_i->external_force/particle_i->mass;

    for (; particle != end; ++particle) {
      particle_j = &particle->states[state];

      speed_of_sound_j = std::sqrt((adiabatic_index - 1.0)*particle_j->energy);
      speed_of_sound = 0.5*(speed_of_sound_i + speed_of_sound_j);

      density = 0.5 * (particle_j->density + particle_i->density);

      velocity = particle_i->velocity - particle_j->velocity;
      distance = particle_i->position - particle_j->position;

      if (dot(velocity, distance) < 0 && density > 0.0) {
        double h = kernel->get_smoothing_length();
        viscosity_coefficient = h * dot(velocity, distance)/ 
                                 (dot(distance, distance) + 0.01 * h * h);
        artificial_viscosity = (-alpha * speed_of_sound * viscosity_coefficient 
          + beta * viscosity_coefficient * viscosity_coefficient) / density;
      } else {
        artificial_viscosity = 0.0;
      }
     
      if (std::isnan(artificial_viscosity)) {
        artificial_viscosity = 0.0;
      }

      particle_i->acceleration += - particle_j->mass * (
          (particle_j->pressure + particle_i->pressure) / 
          (particle_j->density * particle_i->density)
        /*  + artificial_viscosity */
        ) * kernel->gradient(particle_j->position - particle_i->position);
    }
  }

  template <class NeighborIterator>
  void Particle::calculate_energy_rate(int state, NeighborIterator particle, NeighborIterator end) {
    ParticleState *particle_i, *particle_j;
    // const double adiabatic_index = 5.0/3.0;
    double speed_of_sound_i, speed_of_sound_j, speed_of_sound,
           density;
    double viscosity_coefficient;

    const double alpha = 0.01, beta = 0.1;

    double artificial_viscosity;
    Geom::Vector3D velocity, distance;

    particle_i = &states[state];

    speed_of_sound_i = std::sqrt((adiabatic_index - 1.0)*particle_i->energy);

    particle_i->energy_rate = 0.0;

    for (; particle != end; ++particle) {
      particle_j = &particle->states[state];

      speed_of_sound_j = std::sqrt((adiabatic_index - 1.0)*particle_j->energy);
      speed_of_sound = 0.5*(speed_of_sound_i + speed_of_sound_j);

      density = 0.5 * (particle_j->density + particle_i->density);

      velocity = particle_i->velocity - particle_j->velocity;
      distance = particle_i->position - particle_j->position;

      if (dot(velocity, distance) < 0 && density > 0.0) {
        double h = kernel->get_smoothing_length();
        viscosity_coefficient = h * dot(velocity, distance)/ 
                                 (dot(distance, distance) + 0.01 * h * h);
        artificial_viscosity = (-alpha * speed_of_sound * viscosity_coefficient 
          + beta * viscosity_coefficient * viscosity_coefficient) / density;
      } else {
        artificial_viscosity = 0.0;
      }

      if (std::isnan(artificial_viscosity)) {
        artificial_viscosity = 0.0;
      }

      particle_i->energy_rate += 0.5 * particle_j->mass * (
          (particle_j->pressure + particle_i->pressure) / 
          (particle_j->density * particle_i->density) 
         /* + artificial_viscosity */
        ) * dot( (particle_i->velocity - particle_j->velocity),
             kernel->gradient(particle_j->position - particle_i->position));
    }
  }

  template <class ParticleIterator>
  void Particle::calculate_gravity_force(int state, ParticleIterator particle, ParticleIterator end) {
    ParticleState *particle_i, *particle_j;
    Geom::Vector3D distance_ij;

    particle_i = &states[state];

    particle_i->external_force = Geom::Vector3D(0.0, 0.0, 0.0);

    for (; particle != end; ++particle) {
      particle_j = &particle->states[state];

      distance_ij = particle_j->position - particle_i->position;

      if (length(distance_ij) > 0.01) {
        particle_i->external_force += G * particle_i->mass * particle_j->mass / 
          dot(distance_ij, distance_ij) * normalize(distance_ij);
      }
    }
  }

}

