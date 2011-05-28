#ifndef __Palette_HPP__
#define __Palette_HPP__

#include <SamplesMatrix.hpp>
#include <RGBA.hpp>

#include <iostream>

class Palette {
  protected:
    template <typename ForwardIterator>
    static inline int colors_count(ForwardIterator first, ForwardIterator last) {
      int count;

      for (count = 0; first != last; ++first, ++count) {}

      return count;
    }

  public:
    SamplesMatrix<RGBA> palette;

    enum Type {
      FLAT, SMOOTH
    } type;

    Palette(int colors, Type type = SMOOTH) 
     : palette(colors, 1), type(type) {}

    template <typename ForwardIterator>
    Palette(ForwardIterator first, ForwardIterator last, Type type = SMOOTH) 
     : palette(colors_count(first, last), 1), type(type) {
      for (int color = 0; first != last; ++first, ++color) {
        palette[0][color] = *first;
      }
    }

    ~Palette() {}

    RGBA color(double value);

};

#endif /* __Palette_HPP__ */

