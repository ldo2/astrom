#include "Palette.hpp"

#include <cmath>
#include <iostream>

/*
 * class Palette
 */

  RGBA Palette::color(double value) {
    if (std::isnan(value)) return RGBA(0.0, 0.0, 0.0, 1.0);

    // clamp value to [0, 1]
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;
    
    // remap value to palette color range
    double color = value * (palette.width - 1);

    switch (type) {
      case FLAT:
        return palette[0][(int) round(color)];
      case SMOOTH:
        // floor palette color
        int floor_color = (int) std::floor(color);
        // correct right boundary
        if (floor_color >= palette.width - 1) floor_color -= 1;

        // mixing factor for colors
        double mix_factor = color - floor_color;

        return mix( palette[0][floor_color + 1], 
                    palette[0][floor_color], 
                    mix_factor );
    }
  }

