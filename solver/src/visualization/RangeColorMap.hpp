#ifndef __RangeColorMap_HPP__
#define __RangeColorMap_HPP__

#include <visualization/Palette.hpp>
#include <visualization/FieldRange.hpp>

class RangeColorMap {
  public:
    FieldRange *range;
    Palette *palette;

    RangeColorMap(FieldRange *range, Palette *palette)
     : range(range), palette(palette) {}

    RGBA map(double sfield1_value = 0.0, 
             double sfield2_value = 0.0, 
             double sfield3_value = 0.0, 
             double sfield4_value = 0.0);

    RGBA map(const Geom::Vector3D &vfield_value, 
             double sfield_value = 0.0);
};

#endif /* __RangeColorMap_HPP__ */

