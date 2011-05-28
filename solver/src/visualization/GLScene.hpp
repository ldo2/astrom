#ifndef __GLScene_HPP__
#define __GLScene_HPP__

#include <Camera.hpp>

#include <visualization/IParticlesVisualizationAdaptor.hpp>
#include <visualization/DisplayInfo.hpp>

class GLScene {
  protected:
    bool is_initialized;

    void require_initialization();

    void set_projection_matrix(DisplayInfo &info);

  public:
    IParticlesVisualizationAdaptor *particles;

    GLScene(IParticlesVisualizationAdaptor *particles = NULL);
    virtual ~GLScene();

    virtual void initialize() = 0;
    virtual void display(DisplayInfo &info) = 0;

    void camera_centering(DisplayInfo &info);
};

#endif /* __GLScene_HPP__ */

