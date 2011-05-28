#ifndef __GLParticlesScene_HPP__
#define __GLParticlesScene_HPP__

#include <visualization/GLScene.hpp>

#include <visualization/RangeColorMap.hpp>
#include <visualization/IParticleVisualizator.hpp>

class GLParticlesScene : public GLScene {
  public:
    RangeColorMap *color_map;
    IParticleVisualizator *particle_visualizator;

    GLParticlesScene(
      RangeColorMap *color_map, 
      IParticleVisualizator *particle_visualizator
    );

    virtual void initialize();
    virtual void display(DisplayInfo &info);
};

#endif /* __GLParticlesScene_HPP__ */

