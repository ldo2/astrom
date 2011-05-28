#ifndef __Viewer_HPP__
#define __Viewer_HPP__

#include <iostream>

#include <gtkmm.h>

#include <Camera.hpp>

#include <gui/GLScenePane.hpp>
#include <gui/ViewControlPane.hpp>

class Viewer : public Gtk::Window {
  public:
    Viewer(Camera *camera);
    virtual ~Viewer();

  public:
    // member widgets:
    Gtk::HPaned screen_split_pane;

    GLScenePane scene_pane;
    ViewControlPane view_control;

};

#endif /* __Viewer_HPP__ */

