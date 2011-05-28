#ifndef __FieldControlPane_HPP__
#define __FieldControlPane_HPP__

#include <gtkmm.h>

#include <visualization/GLScene.hpp>
#include <visualization/FieldRange.hpp>

class FieldControlPane : public Gtk::VBox {
  public:
    GLScene *field_scene;
    FieldRange *field_range;

    Gtk::SpinButton *min_input;
    Gtk::SpinButton *max_input;

    FieldControlPane(Glib::ustring field_name, GLScene *field_scene, 
                      FieldRange *field_range);

    void on_range_min_changed();
    void on_range_max_changed();

};

#endif /* __FieldControlPane_HPP__ */

