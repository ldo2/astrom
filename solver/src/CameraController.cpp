#include "CameraController.hpp"

/*
 * class CameraController 
 */    

  CameraController::CameraController(
    Camera *camera, double move_sensitivity, double rotation_sensitivity
  ) : camera(camera), move_sensitivity(move_sensitivity), 
      rotation_sensitivity(rotation_sensitivity) {}

  void CameraController::move_forward() const {
    if (camera == NULL) return;
    camera->eye += move_sensitivity * camera->view;
  }

  void CameraController::move_backward() const {
    if (camera == NULL) return;
    camera->eye -= move_sensitivity * camera->view;
  }

  void CameraController::move_left() const{
    if (camera == NULL) return;
    camera->eye -= move_sensitivity * camera->right;
  }

  void CameraController::move_right() const {
    if (camera == NULL) return;
    camera->eye += move_sensitivity * camera->right;
  }

  void CameraController::move_down() const{
    if (camera == NULL) return;
    camera->eye -= move_sensitivity * camera->up;
  }

  void CameraController::move_up() const {
    if (camera == NULL) return;
    camera->eye += move_sensitivity * camera->up;
  }

  void CameraController::rotate_down() const {
    if (camera == NULL) return;
    camera->rotate_up(-rotation_sensitivity);
  }

  void CameraController::rotate_up() const {
    if (camera == NULL) return;
    camera->rotate_up(rotation_sensitivity);
  }
    
  void CameraController::rotate_left() const {
    if (camera == NULL) return;
    camera->rotate(-rotation_sensitivity);
  }

  void CameraController::rotate_right() const {
    if (camera == NULL) return;
    camera->rotate(rotation_sensitivity);
  }

