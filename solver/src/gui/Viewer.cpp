#include "Viewer.hpp"

Viewer::Viewer(Camera *camera) 
 : scene_pane(camera), view_control(&scene_pane) {
  set_title("Viewer");

  // get automatically redrawn if any of their children changed allocation.
  set_reallocate_redraws(true);

  add(screen_split_pane);

  screen_split_pane.add1(view_control);
  screen_split_pane.add2(scene_pane);

  scene_pane.set_size_request(512, 512);

  show_all();
}

Viewer::~Viewer() {}

