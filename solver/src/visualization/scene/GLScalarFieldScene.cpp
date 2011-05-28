#include "GLScalarFieldScene.hpp"

#include <iostream>

/*
 * class GLScalarFieldScene 
 */

  GLScalarFieldScene::GLScalarFieldScene()
   : grayscale_map_shader(NULL), color_map_shader(NULL) {}

  GLScalarFieldScene::~GLScalarFieldScene() {
    // ERROR: next lines is wrong, cause such operations requare GL context
    if (grayscale_map_shader) delete grayscale_map_shader;
    if (    color_map_shader) delete     color_map_shader;
  }

  void GLScalarFieldScene::initialize() {
    std::cout << "initialize GLScalarFieldScene" << std::endl;

    GLFieldScene::initialize();

    grayscale_map_shader = new GrayscaleValueMapShader();
        color_map_shader = new     ColorValueMapShader();
  }

  void GLScalarFieldScene::display(DisplayInfo &info) {
    require_initialization();

    if (particles == NULL) return;

    render_field(info);
    display_field(info);

    legend->set_range(field_range.min[0], field_range.max[0]);
    legend->set_title(Glib::ustring(""));

    legend->display(info);
  }

  void GLScalarFieldScene::display_field(DisplayInfo &info) {
    glViewport(0, 0, info.screen.width, info.screen.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    field_values->bind();

    color_map_shader->bind();

    color_map_shader->min.set( field_range.min[0], 
                               field_range.min[1], 
                               field_range.min[2] );
    color_map_shader->max.set( field_range.max[0], 
                               field_range.max[1], 
                               field_range.max[2] );
    color_map_shader->value_function.set(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
      glTexCoord2d(1.0,1.0); glVertex2d(1.0, 1.0);
      glTexCoord2d(0.0,1.0); glVertex2d(0.0, 1.0);
      glTexCoord2d(0.0,0.0); glVertex2d(0.0, 0.0);
      glTexCoord2d(1.0,0.0); glVertex2d(1.0, 0.0);
    glEnd();
 
    color_map_shader->unbind();
    field_values->unbind();
  }

  


