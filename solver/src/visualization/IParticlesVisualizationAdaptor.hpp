#ifndef __IParticlesVisualizationAdaptor_HPP__
#define __IParticlesVisualizationAdaptor_HPP__

#include <visualization/IParticleVisualizator.hpp>

class IParticlesVisualizationAdaptor {
  public:

    virtual ~IParticlesVisualizationAdaptor() {}

    virtual void render_each_with(IParticleVisualizator &visualizator) = 0;

};

#endif /* __IParticlesVisualizationAdaptor_HPP__ */

