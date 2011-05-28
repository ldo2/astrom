#include "FieldRange.hpp"

/*
 * class FieldRange 
 */

  FieldRange::FieldRange(double min_value, double max_value) {
    set_range(min_value, max_value);
  }

  FieldRange::FieldRange(Geom::Vector3D amplitude) {
    set_range(amplitude);
  }

  void FieldRange::set_min(double min_value) {
    min[0] = min[1] = min[2] = min[3] = min_value;
  }

  void FieldRange::set_max(double max_value) {
    max[0] = max[1] = max[2] = max[3] = max_value;
  }

  void FieldRange::set_range(double min_value, double max_value) {
    set_min(min_value);
    set_max(max_value);
  }

  void FieldRange::set_range(Geom::Vector3D amplitude) {
    set_min(0.0);

    max[0] = amplitude.x;
    max[1] = amplitude.y;
    max[2] = amplitude.z;
    max[3] = length(amplitude);
  }

