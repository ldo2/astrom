#include "GLFieldScene.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <GL/glxext.h>

#include <visualization/particle_visualizators/BillboardVisualizator.hpp>

#include <iostream>

/*
 * class GLFieldScene 
 */

  GLFieldScene::GLFieldScene(GLint width, GLint height)
   : resolution(GLFieldScene::round_to_power_of_two(width ),
                GLFieldScene::round_to_power_of_two(height) ), 
     field_buffer(NULL), field_values(NULL),
     particle_shader(NULL), legend(NULL) {}

  GLFieldScene::~GLFieldScene() {
    // ERROR: next lines is wrong, cause such operations requare GL context
    if (legend) delete legend;
    if (field_buffer) delete field_buffer;
    if (field_values) delete field_values;
    if (particle_shader) delete particle_shader;
  }

  void GLFieldScene::initialize() {
    std::cout << "initialize GLFieldScene" << std::endl;

    legend = new GLLegendDrawer();

    field_buffer = new gl::FrameBuffer(resolution.width, resolution.height);
    field_values = new gl::Texture2D(resolution.width, resolution.height);

    particle_shader = new ParticleShader();

    field_buffer->bind();
    field_buffer->attach_color_texture(
      GL_TEXTURE_2D, field_values->get_texture_id()
    );
    field_buffer->unbind();
  }

  void GLFieldScene::render_field(DisplayInfo &info) {
    PFNGLCLAMPCOLORARBPROC glClampColorARB = (PFNGLCLAMPCOLORARBPROC) 
      glXGetProcAddressARB((GLubyte *)"glClampColorARB");

    // disable color clamp (use HDR)
    glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB,   GL_FIXED_ONLY_ARB);
    glClampColorARB(GL_CLAMP_FRAGMENT_COLOR_ARB, GL_FIXED_ONLY_ARB);
    glClampColorARB(GL_CLAMP_READ_COLOR_ARB,     GL_FIXED_ONLY_ARB);

    // Note: use GL_RGBA32F_ARB for textures

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE); 

    set_projection_matrix(info);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    info.camera->bind(); 

    field_buffer->bind();

    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

    glViewport(0, 0, resolution.width, resolution.height);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    BillboardVisualizator visualizator(*info.camera);

    particle_shader->bind();

    glBegin(GL_QUADS);
      particles->render_each_with(visualizator);
    glEnd();
 
    particle_shader->unbind();
    field_buffer->unbind();

    glDrawBuffer(GL_BACK);
    glReadBuffer(GL_BACK);

    glDisable(GL_BLEND);
  }

  GLint GLFieldScene::round_to_power_of_two(GLint number) {
    GLint m, s;

    for(m = 1 << ((sizeof(GLint) << 2) - 1), 
         s = sizeof(GLint) << 1; 
          s > 0; s >>= 1) {
      if(m == number) {
        return m;
      } else { 
        m = m < number ? m << s : m >> s;
      }
    }

    return m >= number ? m : m << 1;
  }

