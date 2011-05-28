#include "GLParticlesScene.hpp"

/*
 * class GLParticlesScene
 */

  GLParticlesScene::GLParticlesScene(
    RangeColorMap *color_map, 
    IParticleVisualizator *particle_visualizator
  ) : color_map(color_map), particle_visualizator(particle_visualizator) {}

  void GLParticlesScene::initialize() {}

  void GLParticlesScene::display(DisplayInfo &info) {
    glViewport(0, 0, info.screen.width, info.screen.height);
 
    set_projection_matrix(info);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    info.camera->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    particle_visualizator->set_color_map(color_map);
    particles->render_each_with(*particle_visualizator);
  }

