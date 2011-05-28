#ifndef __GLScenePane_HPP__
#define __GLScenePane_HPP__

#include <gtkmm.h>
#include <gtkglmm.h>

#include <visualization/GLScene.hpp>

#include <FPSObserver.hpp>
#include <CameraControllerGtkHandler.hpp>

class GLScenePane : public Gtk::GL::DrawingArea {
  protected:
    sigc::connection connection_idle;

    Camera *camera;
    CameraControllerGtkHandler camera_handler;

    GLScene *scene;

    FPSObserver fps_observer;

  public:
    GLScenePane(Camera *camera, GLScene *scene = NULL);
    virtual ~GLScenePane();

    void invalidate();
    void update();

    void set_scene(GLScene *scene);

  protected:
    /* signal handlers */

    // display callbacks
    virtual void on_realize();
    virtual bool on_configure_event(GdkEventConfigure* event);
    virtual bool on_expose_event(GdkEventExpose* event);

    // synchronous update callbacks
    virtual bool on_map_event(GdkEventAny* event);
    virtual bool on_unmap_event(GdkEventAny* event);
    virtual bool on_visibility_notify_event(GdkEventVisibility* event);
    virtual bool on_idle();

    // camera control
    virtual bool on_key_press_event(GdkEventKey* event);
    virtual bool on_motion_notify_event(GdkEventMotion *event);
    virtual bool on_button_press_event(GdkEventButton *event);

};

#endif /* __GLScenePane_HPP__ */

