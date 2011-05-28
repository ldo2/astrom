#include "RangeColorMap.hpp"

/*
 * class RangeColorMap 
 */

  RGBA RangeColorMap::map(
    double sfield1_value, 
    double sfield2_value, 
    double sfield3_value, 
    double sfield4_value
  ) {
    return palette->color((sfield1_value - range->min[0])/
                          (range->max[0] - range->min[0]));
  }

  RGBA RangeColorMap::map(
    const Geom::Vector3D &vfield_value, 
    double sfield_value
  ) {
    return palette->color((dot(vfield_value, vfield_value) - range->min[3])/
                          (range->max[3] - range->min[3]));
  }

