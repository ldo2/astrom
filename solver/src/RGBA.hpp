#ifndef __RGBA_HPP__
#define __RGBA_HPP__

#include <iostream>

class RGBA {
  public:
    union {
      unsigned int rgba;
      struct {
        unsigned char a, b, g, r;
      };
    };
   
    RGBA();
    RGBA(unsigned int rgba);
    RGBA(unsigned char r, unsigned char g, unsigned char b, 
          unsigned char a = 255);
    RGBA(double r, double g, double b, double a = 1.0);

    static unsigned char clamp(int value, int lower = 0, int upper = 255);
    static unsigned char clamp(unsigned int value, unsigned int lower = 0u, 
                                                   unsigned int upper = 255u);
    static unsigned char clamp(double value, double lower = 0.0, 
                                             double upper = 1.0);
};

  RGBA operator +(const RGBA &, const RGBA &);
  RGBA operator -(const RGBA &, const RGBA &);
  RGBA operator *(const RGBA &, const RGBA &);
  RGBA operator /(const RGBA &, const RGBA &);

  RGBA operator *(const RGBA &, const double &);
  RGBA operator *(const double &, const RGBA &);
  RGBA operator /(const RGBA &, const double &);

  RGBA &operator +=(RGBA &, const RGBA &);
  RGBA &operator -=(RGBA &, const RGBA &);
  RGBA &operator *=(RGBA &, const RGBA &);
  RGBA &operator /=(RGBA &, const RGBA &);

  RGBA &operator *=(RGBA &, const double &);
  RGBA &operator /=(RGBA &, const double &);

  RGBA mix(const RGBA &, const RGBA &, unsigned char);
  RGBA mix(const RGBA &, const RGBA &, double);

  std::ostream &operator <<(std::ostream &out, const RGBA &color);

#endif /* __RGBA_HPP__ */

