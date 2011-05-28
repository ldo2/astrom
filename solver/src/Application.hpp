#ifndef __Application_HPP__
#define __Application_HPP__

#include <PhysicalQuantity.hpp>

#include <sph/ParticleSystem.hpp>
#include <sph/kernel/Quartic.hpp>

#include <ParticleSystemUpdateRoutine.hpp>
#include <pthreads/Thread.hpp>

class Application {
  public:
    sph::Kernel::Quartic kernel;
    sph::ParticleSystem particle_system;
    PhysicalQuantity physical_quantity;

    ParticleSystemUpdateRoutine *update_routine;
    pthreads::Thread *update_routine_thread;
    
    Application();
    ~Application();

    static double          density_distribution(const Geom::Vector3D &point);
    static double         pressure_distribution(const Geom::Vector3D &point);
    static double           energy_distribution(const Geom::Vector3D &point);
    static Geom::Vector3D velocity_distribution(const Geom::Vector3D &point);

    static double pressure_gradient(double radius);
    static double ring_mass(double radius);
    static double velocity(double radius);
    static double density(double radius);
};

#endif /* Application_HPP__ */

