#include "ParticleSystemUpdateRoutine.hpp"

#include <iostream>
#include <fstream>

  void ParticleSystemUpdateRoutine::run() {
    // std::ofstream outfile;
    double t = 0.0;

    // outfile.open("traces.dat");

    while(!stop_flag) {
      /* dump some traces */ 
      /*
      outfile << t << " ";
      for (size_t i = 0; i < particle_system->particles.size(); i += 25) {
        sph::ParticleState &state = particle_system->particles[i].states[particle_system->state];
        outfile << state.density << " " << state.velocity_divergence << " ";
      }
      outfile << std::endl;
      */
      t += particle_system->elapsed_time;

      particle_system->update(time_step);
      std::cout << "update " << std::scientific << particle_system->elapsed_time << std::endl;
      // particle_system->print();
    }

    // outfile.close();
  }
  
  void ParticleSystemUpdateRoutine::stop() {
    stop_flag = true;
  }

