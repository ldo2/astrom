#ifndef __ViewControlPane_HPP__
#define __ViewControlPane_HPP__

#include <gtkmm.h>

#include <gui/FieldSelectorModel.hpp>
#include <gui/GLScenePane.hpp>

#include <visualization/GLScene.hpp>
#include <visualization/FieldRange.hpp>

class ViewControlPane : public Gtk::VBox {
  protected:
    GLScenePane *scene_pane;

    /* field switch */
    Gtk::ComboBox field_switch;

    Glib::RefPtr<Gtk::ListStore> fields_list; 
    int next_id;

    FieldSelectorModel field_model;

    /* field display control */
    Gtk::Notebook field_control;

  public:
    ViewControlPane(GLScenePane *scene_pane);

    void register_field(Glib::ustring name, GLScene *scene, 
                         FieldRange *field_range);

    virtual void on_field_switch();

};

#endif /* __ViewControlPane_HPP__ */

