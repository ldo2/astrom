#include "RGBA.hpp"


/* 
 * class RGBA 
 */

  unsigned char RGBA::clamp(int value, int lower, int upper) {
    if (value < lower) value = lower;
    if (value > upper) value = upper;
    return (unsigned char) ((value * 255)/(upper - lower));
  }

  unsigned char RGBA::clamp(unsigned int value, unsigned int lower, 
                                                unsigned int upper) {
    if (value < lower) value = lower;
    if (value > upper) value = upper;
    return (unsigned char) ((value * 255)/(upper - lower));
  }

  unsigned char RGBA::clamp(double value, double lower, double upper) {
    if (value < lower) value = lower;
    if (value > upper) value = upper;
    return (unsigned char) ((value * 255)/(upper - lower));
  }


  RGBA::RGBA() 
   : rgba(0u) {}

  RGBA::RGBA(unsigned int rgba) 
   : rgba(rgba) {}

  RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   : a(a), b(b), g(g), r(r) {}

  RGBA::RGBA(double r, double g, double b, double a)
   : a(RGBA::clamp(a)), 
     b(RGBA::clamp(b)), g(RGBA::clamp(g)), r(RGBA::clamp(r)) {}


  RGBA operator +(const RGBA &left, const RGBA &right) {
    return RGBA(
      RGBA::clamp((unsigned int) left.r + right.r),
      RGBA::clamp((unsigned int) left.g + right.g),
      RGBA::clamp((unsigned int) left.b + right.b),
      RGBA::clamp((unsigned int) left.a + right.a)
    );
  }

  RGBA operator -(const RGBA &left, const RGBA &right) {
    return RGBA(
      RGBA::clamp((int) left.r - right.r),
      RGBA::clamp((int) left.g - right.g),
      RGBA::clamp((int) left.b - right.b),
      RGBA::clamp((int) left.a - right.a)
    );
  }

  RGBA operator *(const RGBA &left, const RGBA &right) {
    return RGBA(
      RGBA::clamp((unsigned int) left.r * right.r),
      RGBA::clamp((unsigned int) left.g * right.g),
      RGBA::clamp((unsigned int) left.b * right.b),
      RGBA::clamp((unsigned int) left.a * right.a)
    );
  }

  RGBA operator /(const RGBA &left, const RGBA &right) {
    return RGBA(
      RGBA::clamp((double) left.r / right.r),
      RGBA::clamp((double) left.g / right.g),
      RGBA::clamp((double) left.b / right.b),
      RGBA::clamp((double) left.a / right.a)
    );
  }

  RGBA operator *(const RGBA &rgba, const double &factor) {
    double scaled_factor = 0.00390625 * factor;

    return RGBA(
      RGBA::clamp(scaled_factor * rgba.r),
      RGBA::clamp(scaled_factor * rgba.g),
      RGBA::clamp(scaled_factor * rgba.b),
      RGBA::clamp(scaled_factor * rgba.a)
    );
  }

  RGBA operator *(const double &factor, const RGBA &rgba) {
    double scaled_factor = 0.00390625 * factor;

    return RGBA(
      RGBA::clamp(scaled_factor * rgba.r),
      RGBA::clamp(scaled_factor * rgba.g),
      RGBA::clamp(scaled_factor * rgba.b),
      RGBA::clamp(scaled_factor * rgba.a)
    );
  }

  RGBA operator /(const RGBA &rgba, const double &factor) {
    double scaled_factor = 0.00390625 / factor;

    return RGBA(
      RGBA::clamp(scaled_factor * rgba.r),
      RGBA::clamp(scaled_factor * rgba.g),
      RGBA::clamp(scaled_factor * rgba.b),
      RGBA::clamp(scaled_factor * rgba.a)
    );
  }

  RGBA &operator +=(RGBA &left, const RGBA &right) {
    left.r = RGBA::clamp((unsigned int) left.r + right.r);
    left.g = RGBA::clamp((unsigned int) left.g + right.g);
    left.b = RGBA::clamp((unsigned int) left.b + right.b);
    left.a = RGBA::clamp((unsigned int) left.a + right.a);

    return left;
  }

  RGBA &operator -=(RGBA &left, const RGBA &right) {
    left.r = RGBA::clamp((int) left.r - right.r);
    left.g = RGBA::clamp((int) left.g - right.g);
    left.b = RGBA::clamp((int) left.b - right.b);
    left.a = RGBA::clamp((int) left.a - right.a);

    return left;
  }

  RGBA &operator *=(RGBA &left, const RGBA &right) {
    left.r = RGBA::clamp((unsigned int) left.r * right.r);
    left.g = RGBA::clamp((unsigned int) left.g * right.g);
    left.b = RGBA::clamp((unsigned int) left.b * right.b);
    left.a = RGBA::clamp((unsigned int) left.a * right.a);

    return left;
  }

  RGBA &operator /=(RGBA &left, const RGBA &right) {
    left.r = RGBA::clamp((double) left.r / right.r);
    left.g = RGBA::clamp((double) left.g / right.g);
    left.b = RGBA::clamp((double) left.b / right.b);
    left.a = RGBA::clamp((double) left.a / right.a);

    return left;
  }

  RGBA &operator *=(RGBA &rgba, const double &factor) {
    double scaled_factor = 0.00390625 * factor;

    rgba.r = RGBA::clamp(scaled_factor * rgba.r);
    rgba.g = RGBA::clamp(scaled_factor * rgba.g);
    rgba.b = RGBA::clamp(scaled_factor * rgba.b);
    rgba.a = RGBA::clamp(scaled_factor * rgba.a);

    return rgba;
  }

  RGBA &operator /=(RGBA &rgba, const double &factor) {
    double scaled_factor = 0.00390625 / factor;

    rgba.r = RGBA::clamp(scaled_factor * rgba.r);
    rgba.g = RGBA::clamp(scaled_factor * rgba.g);
    rgba.b = RGBA::clamp(scaled_factor * rgba.b);
    rgba.a = RGBA::clamp(scaled_factor * rgba.a);

    return rgba;
  }

  RGBA mix(const RGBA &first, const RGBA &second, unsigned char alpha) {
    return mix(first, second, alpha/255.0);
  }

  RGBA mix(const RGBA &first, const RGBA &second, double alpha) {
    double one_minus_alpha = 1.0 - alpha;

    return RGBA(
      RGBA::clamp(first.r * alpha + second.r * one_minus_alpha, 0.0, 255.0), 
      RGBA::clamp(first.g * alpha + second.g * one_minus_alpha, 0.0, 255.0),
      RGBA::clamp(first.b * alpha + second.b * one_minus_alpha, 0.0, 255.0),
      RGBA::clamp(first.a * alpha + second.a * one_minus_alpha, 0.0, 255.0)
    );
  }

  std::ostream &operator <<(std::ostream &out, const RGBA &color) {
    out << "RGBA(" << (int) color.r << ", " << (int) color.g << ", "
                   << (int) color.b << ", " << (int) color.a <<  ")";
    return out;
  }

