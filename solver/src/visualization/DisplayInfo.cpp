#include "DisplayInfo.hpp"

  DisplayInfo::DisplayInfo(
    int screen_width, int screen_height, 
    Camera *camera
  ) : camera(camera) {
    screen.width  = screen_width;
    screen.height = screen_height;
  }

