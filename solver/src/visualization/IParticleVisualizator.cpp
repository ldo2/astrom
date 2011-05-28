#include "IParticleVisualizator.hpp"

/*
 * interface IParticleVisualizator
 */

  IParticleVisualizator::IParticleVisualizator(
    RangeColorMap *color_map
  ) : color_map(color_map) {
    set_color_map(color_map);
  }

  void IParticleVisualizator::set_color_map(RangeColorMap *new_color_map) {
    color_map = new_color_map;
  }
