#ifndef __Dimention_HPP__
#define __Dimention_HPP__

#include <iostream>

template <typename _NumericType>
class Dimention {
  public:
    typedef _NumericType NumericType;

    NumericType width, height;
    
    Dimention(const NumericType &width, const NumericType &height)
     : width(width), height(height) {}
};

template <typename _NumericType>
std::ostream &operator << (
  std::ostream &out, 
  const Dimention<_NumericType> &dimention
) {
  out << "Dimention {"
      <<    "width: " << dimention.width
      << ", height: " << dimention.height
      << "}";
  return out;
}

#endif /* __Dimention_HPP__ */

