#ifndef __FPSObserver_HPP__
#define __FPSObserver_HPP__

#include <gtkmm.h>

class FPSObserver {
  private:
    Glib::Timer timer;
    int frames;

  public:
    void notify_realize();
    void notify_frame_display();

};

#endif /* __FPSObserver_HPP__ */

