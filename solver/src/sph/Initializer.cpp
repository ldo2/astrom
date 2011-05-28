#include "Initializer.hpp"

#include <cmath>

#include <sph/ParticleField.hpp>

#include <random/RandomGenerator.hpp>

namespace sph {

  static void build_uniform_samples_grid(
    int samples_count, 
    const Geom::BoundingBox3D &volume, 
    int *grid_size,
    Geom::Vector3D &grid_step
  );

  void Initializer::initialize(ParticleSystem &system, double max_time_step) {
    generate_particles(system);

    build_field_approximation(ParticleField(&ParticleState::density ), density , system);
    build_field_approximation(ParticleField(&ParticleState::pressure), pressure, system);
    build_field_approximation(ParticleField(&ParticleState::energy  ), energy  , system);
    build_field_approximation(ParticleField(&ParticleState::velocity), velocity, system);

    determine_particles_masses(system);

    system.initialize(max_time_step);
  }

  void Initializer::generate_particles(ParticleSystem &system) {
    switch (generator_type) {
      case UNIFORM:
        uniform_generate_particles(system);
        break;
      case DENSITY_ADAPTIVE:
        density_adaptive_generate_particles(system);
        break;
    }

    /*
     * Select smoothing length from:
     *   4*PI/3 * h**3 = N_sph * per_particle_volume
     */
    Geom::Vector3D dimention = bounding_volume.max - bounding_volume.min;
    double total_volume = dimention.x * dimention.y * dimention.z;
    size_t particles_count = system.particles.size();
    const double PI = 3.14159265358979;
    
    double particle_influence_volume = total_volume / particles_count * N_sph;
    double h = std::pow(particle_influence_volume * 0.75 / PI, 1.0/3.0);
 
    system.kernel->set_smoothing_length(h);
  }

  static void build_uniform_samples_grid(
    int samples_count, 
    const Geom::BoundingBox3D &volume, 
    int *grid_size,
    Geom::Vector3D &grid_step
  ) {
    int i, j, k;

    Geom::Vector3D dimentions = volume.max - volume.min;
   
    i = 0; j = 1; k = 2;
    if (dimentions.y > dimentions.x) { 
       i = 1; j = 2; k = 0; 
    }
    if (dimentions.z > dimentions.x && dimentions.z > dimentions.y) { 
       i = 2; j = 0; k = 1; 
    }

    grid_size[i] = std::pow(      
      samples_count * (dimentions.coordinates[i] * dimentions.coordinates[i]) / 
                      (dimentions.coordinates[j] * dimentions.coordinates[k]),
      1.0/3.0
    );
    
    grid_size[j] = grid_size[i] * dimentions.coordinates[j] /
                                   dimentions.coordinates[i];
    grid_size[k] = grid_size[i] * dimentions.coordinates[k] / 
                                   dimentions.coordinates[i];

    if (grid_size[i] <= 0) grid_size[i] = 1;
    if (grid_size[j] <= 0) grid_size[j] = 1;
    if (grid_size[k] <= 0) grid_size[k] = 1;
    
    grid_step.x = dimentions.x / (grid_size[0] > 1 ? (grid_size[0] - 1) : 1.0);
    grid_step.y = dimentions.y / (grid_size[1] > 1 ? (grid_size[1] - 1) : 1.0);
    grid_step.z = dimentions.z / (grid_size[2] > 1 ? (grid_size[0] - 1) : 1.0);
  }


  void Initializer::uniform_generate_particles(ParticleSystem &system) {
    int particles_count_per_axis[3];
    Geom::Vector3D space_step;

    build_uniform_samples_grid(particles_count, bounding_volume, 
                                particles_count_per_axis, space_step);

    int i, j, k;
    Geom::Vector3D position;

    //std::cout << "grid size " << particles_count_per_axis[0]
    //          << " " << particles_count_per_axis[1]
    //          << " " << particles_count_per_axis[2] << std::endl;

    for (i = 0; i < particles_count_per_axis[0]; ++i) {
      for (j = 0; j < particles_count_per_axis[1]; ++j) {
        for (k = 0; k < particles_count_per_axis[2]; ++k) {
          // std::cout << "position " << i << " " << j << " " << k << std::endl;
          position = Geom::Vector3D(
            bounding_volume.min.x + i*space_step.x, 
            bounding_volume.min.y + j*space_step.y, 
            bounding_volume.min.z + k*space_step.z
          );

          if (density->value(position) > 0.0) {
            // std::cout << "particles count " << system.particles.size() << std::endl;
            // std::cout << "particle position " << position << std::endl;
            system.particles.push_back(Particle());
            system.particles.rbegin()->states[0].position = position;
          }
        }
      }
    }
  }

  void Initializer::density_adaptive_generate_particles(ParticleSystem &system) {
    RandomGenerator random;
    
    double total_mass = 0.0;

    // intergate density distribution numerically
    int grid_size[3];
    Geom::Vector3D grid_step;

    build_uniform_samples_grid(particles_count, bounding_volume, 
                                grid_size, grid_step);

    int i, j, k, l;
    double subvolume_density_sum;
    Geom::Vector3D position;

    const int subvolume_samples_count = 25;
    double dV = grid_step.x * grid_step.y * grid_step.z;

    for (i = 0; i < grid_size[0]; ++i) {
      for (j = 0; j < grid_size[1]; ++j) {
        for (k = 0; k < grid_size[2]; ++k) {
          position = Geom::Vector3D(
            bounding_volume.min.x + i*grid_step.x, 
            bounding_volume.min.y + j*grid_step.y, 
            bounding_volume.min.z + k*grid_step.z
          );

          subvolume_density_sum = 0.0;

          for (l = 0; l < subvolume_samples_count; ++l) {
            subvolume_density_sum += density->value(
              position + Geom::Vector3D(
                random.rand(grid_step.x), 
                random.rand(grid_step.y), 
                random.rand(grid_step.z)
              )
            );
          }

          total_mass += subvolume_density_sum/subvolume_samples_count * dV;
        }
      }
    }

    // generate particles
    const int sparse_step = 2;
    const int sparse_subvolume_samples_count = subvolume_samples_count *
      sparse_step * sparse_step * sparse_step;

    int subvolume_particles_count;
    double total_density = 0.0;

    for (i = 0; i < grid_size[0]; i += sparse_step) {
      for (j = 0; j < grid_size[1]; j += sparse_step) {
        for (k = 0; k < grid_size[2]; k += sparse_step) {
          position = Geom::Vector3D(
            bounding_volume.min.x + i*grid_step.x, 
            bounding_volume.min.y + j*grid_step.y, 
            bounding_volume.min.z + k*grid_step.z
          );

          subvolume_density_sum = 0.0;

          for (l = 0; l < sparse_subvolume_samples_count; ++l) {
            subvolume_density_sum += density->value(
              position + Geom::Vector3D(
                random.rand(std::min(sparse_step,  grid_size[0] - i) * grid_step.x), 
                random.rand(std::min(sparse_step,  grid_size[1] - j) * grid_step.y), 
                random.rand(std::min(sparse_step,  grid_size[2] - k) * grid_step.z)
              )
            );
          }

          subvolume_particles_count = particles_count * dV *
            subvolume_density_sum/subvolume_samples_count / total_mass;
          total_density += subvolume_density_sum/subvolume_samples_count;

          for (l = 0; l < subvolume_particles_count; ++l) {
            system.particles.push_back(Particle());
            do {
              system.particles.rbegin()->states[0].position = 
                position + Geom::Vector3D(
                  random.rand(sparse_step * grid_step.x), 
                  random.rand(sparse_step * grid_step.y), 
                  random.rand(sparse_step * grid_step.z)
                );
            } while (
              density->value(
                system.particles.rbegin()->states[0].position
              ) <= 0.0
            );
          }
        }
      }
    }

    std::cout << "total density " <<  total_density             << std::endl
              << "   total mass " <<  total_mass                << std::endl
              << " density/mass " << (total_density/total_mass) << std::endl
              << "  cell volume " <<  dV                        << std::endl;

  }

  void Initializer::determine_particles_masses(ParticleSystem &system) {
    std::vector<Particle>::iterator particle;
 
    for (particle = system.particles.begin();
          particle != system.particles.end();
           ++particle) {
      particle->states[0].mass = 
       particle->states[1].mass = 
        particle->states[0].density;
    }
  }

  void Initializer::build_field_approximation(
    const ParticleField &field, 
    IFieldDistribution<double> *field_distribution, 
    ParticleSystem &system
  ) {
    std::vector<Particle>::iterator particle;
 
    for (particle = system.particles.begin();
          particle != system.particles.end();
           ++particle) {
      particle->states[0].*field.scalar = field_distribution->value(
        particle->states[0].position
      );
    }
  }

  void Initializer::build_field_approximation(
    const ParticleField &field, 
    IFieldDistribution<Geom::Vector3D> *field_distribution, 
    ParticleSystem &system
  ) {
    std::vector<Particle>::iterator particle;
 
    for (particle = system.particles.begin();
          particle != system.particles.end();
           ++particle) {
      particle->states[0].*field.vector = field_distribution->value(
        particle->states[0].position
      );
    }
  }

  
}

