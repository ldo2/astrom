#include "CameraControllerGtkHandler.hpp"

#include <iostream>

/*
 * class CameraControllerGtkHandler
 */

  CameraControllerGtkHandler::CameraControllerGtkHandler(
    Camera *camera
  ) : CameraController(camera) {}

  bool CameraControllerGtkHandler::on_key_press_event(GdkEventKey* event) {
    switch (event->keyval) {
      case GDK_z:
        move_up();
        break;
      case GDK_Z:
        move_down();
        break;
      case GDK_Up:
      case GDK_plus:
      case GDK_KP_Add:
        move_forward();
        break;
      case GDK_Down:
      case GDK_minus:
      case GDK_KP_Subtract:
        move_backward();
        break;
      case GDK_Left:
        move_left();
        break;
      case GDK_Right:
        move_right();
        break;
      default:
        break;
    }

    return true;
  }

  bool CameraControllerGtkHandler::on_motion_notify_event(GdkEventMotion *event) {
    if (event->state & GDK_BUTTON1_MASK) {
      if (mouse_x > event->x) rotate_left();
      if (mouse_x < event->x) rotate_right();
      if (mouse_y > event->y) rotate_down();
      if (mouse_y < event->y) rotate_up();

      mouse_x = event->x;
      mouse_y = event->y;
    }

    return true;
  }

  bool CameraControllerGtkHandler::on_button_press_event(GdkEventButton *event) {
    if (event->button == 1) {
      mouse_x = event->x;
      mouse_y = event->y;
    }

    return true;
  }

