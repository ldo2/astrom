#ifndef __CameraControllerGtkHandler_HPP__
#define __CameraControllerGtkHandler_HPP__

#include <gtkmm.h>

#include <CameraController.hpp>

class CameraControllerGtkHandler : public CameraController {
  public:
    double mouse_x, mouse_y;

    CameraControllerGtkHandler(Camera *camera = NULL);

    bool on_key_press_event(GdkEventKey* event);
    bool on_motion_notify_event(GdkEventMotion *event);
    bool on_button_press_event(GdkEventButton *event);
};

#endif /* __CameraControllerGtkHandler_HPP__ */

