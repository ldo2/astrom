#ifndef __DisplayInfo_HPP__
#define __DisplayInfo_HPP__

#include <Camera.hpp>

class DisplayInfo {
  public:
    struct {
      int width, height;
    } screen;

    Camera *camera;

    DisplayInfo(int screen_width, int screen_height, Camera *camera);
};

#endif /* __DisplayInfo_HPP__ */

