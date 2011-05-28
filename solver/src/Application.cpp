#include "Application.hpp"

#include <sph/FieldDistribution.hpp>
#include <sph/Initializer.hpp>

  const double radius_max = 10.0;
  const double PI = 3.14159265358979;

  class FunctionIntegral {
    private:
      double left_boundary, right_boundary;

      int points_count;
      double *points;

      double argument_step;  

    public:
      template <typename Callable>
      FunctionIntegral(Callable function, double left_boundary, 
                        double right_boundary, int points_count = 1000)
       : left_boundary(left_boundary), right_boundary(right_boundary), 
         points_count(points_count), points(new double [points_count]), 
         argument_step((right_boundary - left_boundary)/(points_count - 1)) {
        // calculate integral
        double argument = left_boundary;
        double integral = 0.0;

        for (int i = 0; i < points_count; ++i) {
          points[i] = integral;
          argument += argument_step;
          integral += function(argument) * argument_step;
        }
      }

      ~FunctionIntegral() {
        delete[] points;
      }

      double operator ()(double argument) {
        double argument_offset = (argument - left_boundary)/argument_step;
        int argument_index = std::floor(argument_offset); 
        double argument_mix = argument_offset - argument_index;

        double argument_low  = points[argument_index],
               argument_high = points[argument_index >= points_count ? 
                                       points_count - 1 : argument_index + 1];

        return argument_low * (1.0 - argument_mix) + 
                argument_high * argument_mix;
      
      }
  };

  Application::Application() 
   : kernel(1.0), particle_system(&kernel) {
    sph::FieldDistribution<double, double (*)(const Geom::Vector3D &)> 
      density(&Application::density_distribution),
      pressure(&Application::pressure_distribution),
      energy(&Application::energy_distribution);
    sph::FieldDistribution<Geom::Vector3D, Geom::Vector3D(*)(const Geom::Vector3D &)> 
      velocity(&Application::velocity_distribution);

    const int particles_count = 500;

    /* размеры двумерной области */
    double a = 2.0 * radius_max, b = 2.0 * radius_max;

    sph::Initializer initialier(
      /* начальные распределения полей */
      &density,
      &pressure,
      &energy,
      &velocity,
      /* область в которой генерируются частицы */
      Geom::BoundingBox3D(
        Geom::Vector3D(-0.5*a, -0.5*b,  0.0), 
        Geom::Vector3D( 0.5*a,  0.5*b,  /* тольшина одного слоя частиц */
                                        (a + b) / (particles_count - 1.0))
      ),
      /* коэффициент кол-ва генерируемых частиц */
      particles_count,
      /* коэффициент кол-ва частиц в области сглаживания */
      400, 
      /* тип генератора частиц */
       sph::Initializer::DENSITY_ADAPTIVE
      // sph::Initializer::UNIFORM
    );

    /* шаг интегрирования */
    double const time_step = 0.00025;

    initialier.initialize(particle_system, time_step);

    

    std::cout << "particles count " 
              << particle_system.particles.size() 
              << std::endl
              << "smoothing length " 
              << particle_system.kernel->get_smoothing_length() 
              << std::endl
              << "time step " 
              << time_step 
              << std::endl;

    /* запуск процесса расчета */
    update_routine = new ParticleSystemUpdateRoutine(&particle_system, time_step);
    update_routine_thread = new pthreads::Thread(update_routine);
    update_routine_thread->start();
  }

  Application::~Application() {
    std::cout << "close application" << std::endl;

    update_routine->stop();
    update_routine_thread->join();

    delete update_routine_thread;
    delete update_routine;
  }

  /* начальное распределение плотности */
  double Application::density_distribution(const Geom::Vector3D &point) {
    double radius = length(point);
    return density(radius);
  }

  /* начальное распределение давления */
  double Application::pressure_distribution(const Geom::Vector3D &point) {
    static FunctionIntegral pressure(&Application::pressure_gradient, 
                                      radius_max, 0.0);

    double radius = length(point);
    return pressure(radius);
  }

  /* начальное распределение внутренней энергии */
  double Application::energy_distribution(const Geom::Vector3D &point) {
    return pressure_distribution(point) / ((sph::Particle::adiabatic_index - 1.0) 
                                            * density_distribution(point));
  }

  /* начальное распределение скорости */
  Geom::Vector3D Application::velocity_distribution(const Geom::Vector3D &point) {
    double radius = length(point);
    // return Geom::Vector3D(0.0, 0.0, 0.0);
    return velocity(radius)*normalize(Geom::Vector3D(-point.y, point.x, 0.0));
  }


  double Application::pressure_gradient(double radius) {
    static FunctionIntegral mass(&Application::ring_mass, 0.0, radius_max);

    double velocity_module = velocity(radius);

    return -(sph::Particle::G * density(radius) * mass(radius) / (radius * radius) + 
             velocity_module * velocity_module / radius);
  }

  double Application::ring_mass(double radius) {
    return 4*PI * radius * radius * density(radius);
  }

  double Application::velocity(double radius) {
    return 0.1*std::sqrt(radius) + 1.0;
  }

  double Application::density(double radius) {
    return radius < radius_max ? 0.5*(std::cos(radius/radius_max*PI) + 1.0) : 0.0;
  }

  

