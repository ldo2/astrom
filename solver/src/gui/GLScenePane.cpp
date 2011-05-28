#include "GLScenePane.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

#include <visualization/DisplayInfo.hpp>

/* **** **** **** **** **** GLScenePane constructor  **** **** **** **** **** */

GLScenePane::GLScenePane(Camera *camera, GLScene *scene) 
 : camera(camera), camera_handler(camera), scene(scene) {
  Glib::RefPtr<Gdk::GL::Config> gl_config;

  gl_config = Gdk::GL::Config::create(Gdk::GL::MODE_RGB    |
                                      Gdk::GL::MODE_DEPTH  |
                                      Gdk::GL::MODE_DOUBLE);
  if (!gl_config) {
    std::cerr << "info: Cannot find the double-buffered visual." << std::endl
              << "info: Trying single-buffered visual."          << std::endl;

    gl_config = Gdk::GL::Config::create(Gdk::GL::MODE_RGB   |
                                        Gdk::GL::MODE_DEPTH);
    if (!gl_config) {
      std::cerr << "error: Cannot find any OpenGL-capable visual." << std::endl;
      std::exit(1);
    }
  }

  // set OpenGL-capability to the widget
  set_gl_capability(gl_config);

  // set focus-capability to the widget
  set_can_focus(true);

  // add events
  add_events(Gdk::VISIBILITY_NOTIFY_MASK  |
             Gdk::POINTER_MOTION_MASK     | 
             Gdk::BUTTON_PRESS_MASK      );
}

/* **** **** **** **** ****  GLScenePane destructor  **** **** **** **** **** */

GLScenePane::~GLScenePane() {}

/* **** **** **** **** ****    GLScenePane realize   **** **** **** **** **** */

void GLScenePane::on_realize() {
  Gtk::DrawingArea::on_realize();

  Glib::RefPtr<Gdk::GL::Drawable> gl_drawable = get_gl_drawable();

  // *** OpenGL BEGIN ***
  if (!gl_drawable->gl_begin(get_gl_context())) return;

  gl_drawable->gl_end();
  // *** OpenGL END ***

  fps_observer.notify_realize();
}

/* **** **** **** **** ****  GLScenePane  configure  **** **** **** **** **** */

bool GLScenePane::on_configure_event(GdkEventConfigure* event) {
  Glib::RefPtr<Gdk::GL::Drawable> gl_drawable = get_gl_drawable();

  // *** OpenGL BEGIN ***
  if (!gl_drawable->gl_begin(get_gl_context())) return false;

  glViewport(0, 0, get_width(), get_height());

  gl_drawable->gl_end();
  // *** OpenGL END ***

  return true;
}

/* **** **** **** **** ****   GLScenePane  expose    **** **** **** **** **** */

bool GLScenePane::on_expose_event(GdkEventExpose* event) {
  Glib::RefPtr<Gdk::GL::Drawable> gl_drawable = get_gl_drawable();

  // *** OpenGL BEGIN ***
  if (!gl_drawable->gl_begin(get_gl_context()))
    return false;

  DisplayInfo display_info(get_width(), get_height(), camera);

  if (scene) {
    scene->display(display_info);
  } else {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  // Swap buffers.
  if (gl_drawable->is_double_buffered())
    gl_drawable->swap_buffers();
  else
    glFlush();

  gl_drawable->gl_end();
  // *** OpenGL END ***

  fps_observer.notify_frame_display();

  return true;
}

/* **** **** **** ****     GLScenePane camera control     **** **** **** **** */

bool GLScenePane::on_key_press_event(GdkEventKey* event) {
  // std::cout << "GLScenePane key press event" << std::endl;
  camera_handler.on_key_press_event(event);
  // std::cout << scene->camera << std::endl;

  DisplayInfo display_info(get_width(), get_height(), camera);

  switch (event->keyval) {
    case GDK_Home:
      if (scene) scene->camera_centering(display_info);
      break;
    default:
      break;
  }

  invalidate();

  return true;
}

bool GLScenePane::on_motion_notify_event(GdkEventMotion *event) {
  // std::cout << "GLScenePane motion notify event" << std::endl;
  camera_handler.on_motion_notify_event(event);
  return true;
}

bool GLScenePane::on_button_press_event(GdkEventButton *event) {
  // std::cout << "GLScenePane button press event" << std::endl;
  camera_handler.on_button_press_event(event);
  grab_focus();
  return true;
}

/* **** **** **** ****   GLScenePane synchronous update   **** **** **** **** */

bool GLScenePane::on_map_event(GdkEventAny* event) {
  if (!connection_idle.connected()) {
    connection_idle = Glib::signal_idle().connect(
      sigc::mem_fun(*this, &GLScenePane::on_idle), 
      GDK_PRIORITY_REDRAW
    );
  }

  return true;
}

bool GLScenePane::on_unmap_event(GdkEventAny* event) {
  if (connection_idle.connected()) {
    connection_idle.disconnect();
  }

  return true;
}

bool GLScenePane::on_visibility_notify_event(GdkEventVisibility* event) {
  if (event->state == GDK_VISIBILITY_FULLY_OBSCURED) {
    if (connection_idle.connected()) {
      connection_idle.disconnect();
    }
  } else {
    if (!connection_idle.connected()) {
      connection_idle = Glib::signal_idle().connect(
        sigc::mem_fun(*this, &GLScenePane::on_idle), 
        GDK_PRIORITY_REDRAW
      );
    }
  }

  return true;
}

bool GLScenePane::on_idle() {
  invalidate();
  update();

  return true;
}

/* **** **** **** ****   GLScenePane  auxiliary methods   **** **** **** **** */

void GLScenePane::invalidate() {
  get_window()->invalidate_rect(get_allocation(), false);
}

void GLScenePane::update() { 
  get_window()->process_updates(false); 
}

void GLScenePane::set_scene(GLScene *new_scene) {
  if (scene == NULL && new_scene != NULL) { 
    DisplayInfo display_info(get_width(), get_height(), camera);
    new_scene->camera_centering(display_info); 
  }
  scene = new_scene;
}

