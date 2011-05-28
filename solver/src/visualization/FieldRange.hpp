#ifndef __FieldRange_HPP__
#define __FieldRange_HPP__

#include <geom/Vector3D.hpp>

class FieldRange {
  public:
    double min[4];
    double max[4];

    FieldRange(double min_value = 0.0, double max_value = 1.0);
    FieldRange(Geom::Vector3D amplitude);

    void set_min(double min_value);
    void set_max(double max_value);

    void set_range(double min_value, double max_value);
    void set_range(Geom::Vector3D amplitude);
};

#endif /* __FieldRange_HPP__ */

