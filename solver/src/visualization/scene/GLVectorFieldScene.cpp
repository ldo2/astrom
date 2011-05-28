#include "GLVectorFieldScene.hpp"

#include <iostream>

#include <random/RandomGenerator.hpp>

#include <visualization/particle_visualizators/VectorVisualizator.hpp>
#include <visualization/particle_visualizators/BoundingBoxVisualizator.hpp>
#include <visualization/particle_visualizators/SphereVisualizator.hpp>
#include <visualization/particle_visualizators/PointVisualizator.hpp>
#include <visualization/particle_visualizators/CircleVisualizator.hpp>

/*
 * class GLVectorFieldScene 
 */

  GLVectorFieldScene::GLVectorFieldScene()
   : vector_shader(NULL) {}

  GLVectorFieldScene::~GLVectorFieldScene() {
    // ERROR: next lines is wrong, cause such operations requare GL context
    if (vector_shader) delete vector_shader;
  }

  void GLVectorFieldScene::initialize() {
    std::cout << "initialize GLVectorFieldScene" << std::endl;

    GLFieldScene::initialize();

    const int noise_map_size = 512;
 
    noise_map = new gl::Texture2D(noise_map_size, noise_map_size);
    noise_map->bind();

    RandomGenerator random;

    int size = 4 * noise_map_size * noise_map_size * sizeof(unsigned char);
    unsigned char *noise_data = new unsigned char [size];
    for (int i = 0; i < size; i += 4) {
      noise_data[i + 0] =
      noise_data[i + 1] = 
      noise_data[i + 2] = (unsigned char) random.rand(255.0);
      noise_data[i + 3] = 255;
    }

    // glTexImage2D(GL_TEXTURE_2D, 0, /*GL_RGBA*/GL_RGBA32F_ARB, 512, 512, 0, GL_INTENSITY, GL_UNSIGNED_BYTE, noise_data);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, noise_map_size, noise_map_size, GL_RGBA, GL_UNSIGNED_BYTE, noise_data);


    delete[] noise_data;

    noise_map->unbind();

    vector_shader = new VectorFieldFlowShader();
  }

  void GLVectorFieldScene::display(DisplayInfo &info) {
    require_initialization();

    if (particles == NULL) return;

    render_field(info);
    display_flow(info);
    display_field(info);
    // display_per_particle_vectors(info);

    legend->set_range(0.0, field_range.max[3]);
    legend->set_title(Glib::ustring(""));

    legend->display(info);
  }

  void GLVectorFieldScene::display_field(DisplayInfo &info) {
    glViewport(0, 0, info.screen.width, info.screen.height);
 
    set_projection_matrix(info);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    info.camera->bind(); 

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // glClear(GL_COLOR_BUFFER_BIT);
/*
    VectorVisualizator visualizator(*info.camera);

    glColor4f(1.0, 0.0, 1.0, 1.0);
 
    particles->render_each_with(visualizator);
 */
/*
    glClear(GL_DEPTH_BUFFER_BIT);

    BoundingBoxVisualizator bbox_visualizator;

    particles->render_each_with(bbox_visualizator);
    bbox_visualizator.render_bounding_box();
 */

/*
    SphereVisualizator sphere_visualizator(*info.camera);
    particles->render_each_with(sphere_visualizator);
 */
/*
    PointVisualizator point_visualizator(*info.camera, 1.0);
    particles->render_each_with(point_visualizator);
 */
/*
    CircleVisualizator circle_visualizator(*info.camera, 0.25);
    particles->render_each_with(circle_visualizator);
*/
  }

  void GLVectorFieldScene::display_flow(DisplayInfo &info) {
    glViewport(0, 0, info.screen.width, info.screen.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0 + 0);
    field_values->bind();

    glActiveTexture(GL_TEXTURE0 + 1);
    noise_map->bind();

    vector_shader->bind();

    vector_shader->min.set(0.0, 0.0, 0.0);
    vector_shader->max.set( field_range.max[0], 
                            field_range.max[1], 
                            field_range.max[2] );

    vector_shader->u_axis.set(
      info.camera->right.x, 
      info.camera->right.y, 
      info.camera->right.z
    );

    vector_shader->v_axis.set(
      info.camera->up.x, 
      info.camera->up.y, 
      info.camera->up.z
    );

    vector_shader->noise_map.set(1);

    // glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
      glTexCoord2d(1.0,1.0); glVertex2d(1.0, 1.0);
      glTexCoord2d(0.0,1.0); glVertex2d(0.0, 1.0);
      glTexCoord2d(0.0,0.0); glVertex2d(0.0, 0.0);
      glTexCoord2d(1.0,0.0); glVertex2d(1.0, 0.0);
    glEnd();
 
    vector_shader->unbind();

    glActiveTexture(GL_TEXTURE0 + 1);
    noise_map->unbind();

    glActiveTexture(GL_TEXTURE0 + 0);
    field_values->unbind();

    glDisable(GL_TEXTURE_2D);
  }

