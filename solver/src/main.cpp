#include <gtkmm.h>
#include <gtkglmm.h>

#include <Application.hpp>

#include <gui/Viewer.hpp>
#include <visualization/Palette.hpp>
#include <visualization/RangeColorMap.hpp>
#include <visualization/FieldRange.hpp>

#include <sph/ParticleSystemVisualizationAdaptor.hpp>

#include <SamplesMatrix.hpp>

/**
 * Директивы компиляции:
 *   PARTICLE_SCALE (double)        - задает масштаб частиц (
 *                                      сферы/окружности:
 *                                        часть радиуса сглаживания 
 *                                        в координатах модели;
 *                                      точки:
 *                                        размер точки в экранных координатах
 *                                    )
 *   PARTICLE_VECTOR_SCALE (double) - задает длину отображаемых векторов 
 *                                    в координатах модели
 *
 *   SMOOTH_FIELD_RENDER            - флаг включающий отображение в режиме 
 *                                    сглаженных полей (требует наличия 
 *                                    аппаратной поддрежки)
 *
 * Отображение несглаженных полей:
 *   по-умолчанию частицы отображаются точками
 *
 *   SPHERE_PARTICLE_RENDER - флаг переключающий в режим отображения 
 *                            частиц сферами
 *
 *   CIRCLE_PARTICLE_RENDER - флаг переключающий в режим отображения 
 *                            частиц окружностями
 */

#ifndef PARTICLE_SCALE 
  #define PARTICLE_SCALE (1.0)
#endif /* define PARTICLE_SCALE */

#ifndef PARTICLE_VECTOR_SCALE 
  #define PARTICLE_VECTOR_SCALE (1.0)
#endif /* define PARTICLE_VECTOR_SCALE */

/*
 * Palettes
 */

RGBA default_palette_colors[] = {
  RGBA(0.0, 0.0, 1.0),  // blue
  RGBA(0.0, 1.0, 1.0),  // cyan
  RGBA(0.0, 1.0, 0.0),  // green
  RGBA(1.0, 1.0, 0.0),  // yellow
  RGBA(1.0, 0.0, 0.0)   // red
};

RGBA monochrome_palette_colors[] = {
  RGBA(1.0, 0.0, 1.0)  // violet
};

Palette default_palette(
  default_palette_colors, 
  default_palette_colors + sizeof(default_palette_colors)/sizeof(RGBA)
);

Palette monochrome_palette(
  monochrome_palette_colors, 
  monochrome_palette_colors + sizeof(monochrome_palette_colors)/sizeof(RGBA), 
  Palette::FLAT
);

/*
 * Camera
 */

Camera camera(
  Geom::Vector3D(0.0, 0.0, 0.0),
  Geom::Vector3D(1.0, 0.0, 0.0),
  Geom::Vector3D(0.0, 0.0,-1.0)
);

/* 
 * Define visualization type
 */

#ifdef SMOOTH_FIELD_RENDER 

#include <visualization/scene/GLScalarFieldScene.hpp>
#include <visualization/scene/GLVectorFieldScene.hpp>

  void register_field(
    Viewer &viewer, sph::ParticleSystem *particle_system,
    Glib::ustring name, Geom::Vector3D sph::ParticleState::*vector_field
  ) {
    GLVectorFieldScene *vector_scene = new GLVectorFieldScene();
    vector_scene->particles = new sph::ParticleSystemVisualizationAdaptor(
      particle_system, vector_field
    );

    viewer.view_control.register_field(
      name, vector_scene, &vector_scene->field_range
    );
  }

  void register_field(
    Viewer &viewer, sph::ParticleSystem *particle_system,
    Glib::ustring name, double sph::ParticleState::*scalar_field
  ) {
    GLScalarFieldScene *scalar_scene = new GLScalarFieldScene();
    scalar_scene->particles = new sph::ParticleSystemVisualizationAdaptor(
      particle_system, scalar_field
    );

    viewer.view_control.register_field(
      name, scalar_scene, &scalar_scene->field_range
    );
  }

#else /* use simple particle rendering */

#include <visualization/scene/GLParticlesScene.hpp>
#include <visualization/particle_visualizators/PointVisualizator.hpp>
#include <visualization/particle_visualizators/SphereVisualizator.hpp>
#include <visualization/particle_visualizators/CircleVisualizator.hpp>
#include <visualization/particle_visualizators/VectorVisualizator.hpp>

  void register_field(
    Viewer &viewer, sph::ParticleSystem *particle_system,
    Glib::ustring name, Geom::Vector3D sph::ParticleState::*vector_field
  ) {
    FieldRange *field_range = new FieldRange(0.0, 1.0);

    GLParticlesScene *scene = new GLParticlesScene(
      new RangeColorMap(field_range, &default_palette), 
      new VectorVisualizator(camera, PARTICLE_VECTOR_SCALE)
    );
    scene->particles = new sph::ParticleSystemVisualizationAdaptor(
      particle_system, vector_field
    );

    viewer.view_control.register_field(
      name, scene, field_range
    );
  }

  void register_field(
    Viewer &viewer, sph::ParticleSystem *particle_system,
    Glib::ustring name, double sph::ParticleState::*scalar_field
  ) {
    FieldRange *field_range = new FieldRange(0.0, 1.0);

    GLParticlesScene *scene = new GLParticlesScene(
      new RangeColorMap(field_range, &default_palette),
#if   defined(SPHERE_PARTICLE_RENDER)
      new SphereVisualizator(camera, PARTICLE_SCALE)
#elif defined(CIRCLE_PARTICLE_RENDER)
      new CircleVisualizator(camera, PARTICLE_SCALE)
#else
      new PointVisualizator(camera, PARTICLE_SCALE)
#endif
    );
    scene->particles = new sph::ParticleSystemVisualizationAdaptor(
      particle_system, scalar_field
    );

    viewer.view_control.register_field(
      name, scene, field_range
    );
  }

#endif

int main(int argc, char* argv[]) {
  /*
   * GTK initialize
   */
  Gtk::Main kit(argc, argv);
  Gtk::GL::init(argc, argv);

  /*
   * Create main frame and application data
   */

  Viewer viewer(&camera);
  Application app;

  /*
   * Bind view scenes
   */

  register_field(viewer, &app.particle_system, 
                  "density"       , &sph::ParticleState::density       );
  register_field(viewer, &app.particle_system, 
                  "pressure"      , &sph::ParticleState::pressure      );
  register_field(viewer, &app.particle_system, 
                  "energy"        , &sph::ParticleState::energy        );
  register_field(viewer, &app.particle_system, 
                  "density rate"  , &sph::ParticleState::density_rate  );
  register_field(viewer, &app.particle_system, 
                  "energy rate"   , &sph::ParticleState::energy_rate   );
  register_field(viewer, &app.particle_system, 
                  "velocity"      , &sph::ParticleState::velocity      );
  register_field(viewer, &app.particle_system, 
                  "acceleration"  , &sph::ParticleState::acceleration  );
  register_field(viewer, &app.particle_system, 
                  "external force", &sph::ParticleState::external_force);
  register_field(viewer, &app.particle_system, 
                  "velocity_divergence", &sph::ParticleState::velocity_divergence);
  register_field(viewer, &app.particle_system, 
                  "velocity_divergence", &sph::ParticleState::time_step);

  /*
   * Run main loop
   */

  kit.run(viewer);

  return 0;
}

