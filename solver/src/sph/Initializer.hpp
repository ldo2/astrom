#ifndef __sph_Initializer_HPP__
#define __sph_Initializer_HPP__

#include <geom/Vector3D.hpp>
#include <geom/BoundingBox3D.hpp>

#include <sph/FieldDistribution.hpp>
#include <sph/ParticleField.hpp>
#include <sph/ParticleSystem.hpp>

namespace sph {

  class Initializer {
    public:
      enum ParticleGeneratorType {
        UNIFORM,
        DENSITY_ADAPTIVE
      };

    protected:
      IFieldDistribution<double> *density;
      IFieldDistribution<double> *pressure;
      IFieldDistribution<double> *energy;
      IFieldDistribution<Geom::Vector3D> *velocity;

      Geom::BoundingBox3D bounding_volume;

      unsigned int particles_count;
      double N_sph;

      ParticleGeneratorType generator_type;

      void generate_particles(ParticleSystem &system);
      void uniform_generate_particles(ParticleSystem &system);
      void density_adaptive_generate_particles(ParticleSystem &system);

      void build_field_approximation(
        const ParticleField &field, 
        IFieldDistribution<double> *field_distribution, 
        ParticleSystem &system
      );
      void build_field_approximation(
        const ParticleField &field, 
        IFieldDistribution<Geom::Vector3D> *field_distribution, 
        ParticleSystem &system
      );

      void determine_particles_masses(ParticleSystem &system);

    public:
      Initializer(
        IFieldDistribution<double> *density,
        IFieldDistribution<double> *pressure,
        IFieldDistribution<double> *energy,
        IFieldDistribution<Geom::Vector3D> *velocity,
        const Geom::BoundingBox3D &bounding_volume,
        unsigned int particles_count,
        double N_sph,
        ParticleGeneratorType generator_type = DENSITY_ADAPTIVE
      ) : density(density), pressure(pressure), 
          energy(energy), velocity(velocity), 
          bounding_volume(bounding_volume),
          particles_count(particles_count),
          N_sph(N_sph),
          generator_type(generator_type) {}

      void initialize(ParticleSystem &system, double max_time_step);

  };

}

#endif /* __sph_Initializer_HPP__ */

