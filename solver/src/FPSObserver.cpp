#include "FPSObserver.hpp"

#include <iostream>

/*
 * class FPSObserver 
 */

  void FPSObserver::notify_realize() {
    frames = 0;
    timer.start();
  }

  void FPSObserver::notify_frame_display() {
    ++frames;

    double seconds = timer.elapsed();
    if (seconds >= 5.0) {
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout.precision(3);
      std::cout << frames << " frames in "
                << seconds << " seconds = "
                << (frames/seconds) << " FPS\n";
      timer.reset();
      frames = 0;
    }
  }

