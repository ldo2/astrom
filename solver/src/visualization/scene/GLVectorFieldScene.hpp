#ifndef __GLVectorFieldScene_HPP__
#define __GLVectorFieldScene_HPP__

#include <visualization/scene/GLFieldScene.hpp>

#include <visualization/shaders/GrayscaleValueMapShader.hpp>
#include <visualization/shaders/VectorFieldFlowShader.hpp>

class GLVectorFieldScene : public GLFieldScene {
  public:
    VectorFieldFlowShader *vector_shader;
    gl::Texture2D *noise_map;

    GLVectorFieldScene();
    virtual ~GLVectorFieldScene();

    virtual void initialize();
    virtual void display(DisplayInfo &info);

  protected:
    void display_field(DisplayInfo &info);
    void display_flow (DisplayInfo &info);
};

#endif /* __GLVectorFieldScene_HPP__ */
