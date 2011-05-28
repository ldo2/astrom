#ifndef __CameraController_HPP__
#define __CameraController_HPP__

#include <Camera.hpp>

class CameraController {
  public:
    Camera *camera;

    double     move_sensitivity;
    double rotation_sensitivity;

    static const double DEFAULT_MOVE_SENSITIVITY     = 1.0;
    static const double DEFAULT_ROTATION_SENSITIVITY = 0.015625;
    

    CameraController(
      Camera *camera = NULL, 
      double     move_sensitivity = DEFAULT_MOVE_SENSITIVITY,
      double rotation_sensitivity = DEFAULT_ROTATION_SENSITIVITY
    );

    void move_forward() const;
    void move_backward() const;

    void move_left() const;
    void move_right() const;

    void move_down() const;
    void move_up() const;

    void rotate_down() const;
    void rotate_up() const;
    
    void rotate_left() const;
    void rotate_right() const;
};

#endif /* __CameraController_HPP__ */

