#ifndef __GLScalarFieldScene_HPP__
#define __GLScalarFieldScene_HPP__

#include <visualization/scene/GLFieldScene.hpp>

#include <visualization/shaders/GrayscaleValueMapShader.hpp>
#include <visualization/shaders/ColorValueMapShader.hpp>

class GLScalarFieldScene : public GLFieldScene {
  public:
    GrayscaleValueMapShader *grayscale_map_shader;
        ColorValueMapShader *color_map_shader;

    GLScalarFieldScene();
    virtual ~GLScalarFieldScene();

    virtual void initialize();
    virtual void display(DisplayInfo &info);

  protected:
    void display_field(DisplayInfo &info);
};

#endif /* __GLScalarFieldScene_HPP__ */

