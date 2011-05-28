#ifndef __GLFieldScene_HPP__
#define __GLFieldScene_HPP__

#include <Dimention.hpp>

#include <visualization/GLScene.hpp>
#include <visualization/GLLegendDrawer.hpp>
#include <visualization/FieldRange.hpp>

#include <visualization/shaders/ParticleShader.hpp>

#include <gl/Texture2D.hpp>
#include <gl/fbo/FrameBuffer.hpp>

class GLFieldScene : public GLScene {
  public:
    Dimention<GLint> resolution;

    gl::FrameBuffer *field_buffer;
    gl::Texture2D   *field_values;

    ParticleShader *particle_shader;
    GLLegendDrawer *legend;

    FieldRange field_range;

    GLFieldScene(GLint width = 512, GLint height = 512);
    virtual ~GLFieldScene();

    virtual void initialize();
    virtual void display(DisplayInfo &info) = 0;

  protected:
    void render_field(DisplayInfo &info);

    static GLint round_to_power_of_two(GLint number);
};

#endif /* __GLFieldScene_HPP__ */

