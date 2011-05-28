#ifndef __ParticleSystemUpdateRoutine_HPP__
#define __ParticleSystemUpdateRoutine_HPP__

#include <iostream>

#include <sph/ParticleSystem.hpp>

#include <pthreads/IRunnable.hpp>

class ParticleSystemUpdateRoutine : public pthreads::IRunnable {
  private:
    sph::ParticleSystem *particle_system;
    double time_step;
    
    volatile bool stop_flag;

  public:
    ParticleSystemUpdateRoutine(sph::ParticleSystem *particle_system, 
                                 double time_step)
     : particle_system(particle_system), time_step(time_step), 
       stop_flag(false) {}

    ~ParticleSystemUpdateRoutine() {}

    virtual void run();

    void stop();
};

#endif /* __ParticleSystemUpdateRoutine_HPP__ */
