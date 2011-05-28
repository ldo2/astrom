#include "ViewControlPane.hpp"

#include <gui/FieldControlPane.hpp>

  ViewControlPane::ViewControlPane(GLScenePane *scene_pane) 
   : scene_pane(scene_pane), next_id(0) {
    fields_list = Gtk::ListStore::create(field_model);
    field_switch.set_model(fields_list);

    field_switch.pack_start(field_model.name);
    pack_start(field_switch, Gtk::PACK_SHRINK);

    field_switch.signal_changed().connect( 
      sigc::mem_fun(*this, &ViewControlPane::on_field_switch) 
    );

    field_control.set_show_tabs(false);

    pack_start(field_control, Gtk::PACK_SHRINK);
  }

  void ViewControlPane::register_field(
    Glib::ustring name, 
    GLScene *scene, 
    FieldRange *field_range
  ) {
    Gtk::TreeModel::Row field_row = *fields_list->append();

    field_row[field_model.id   ] = next_id++;
    field_row[field_model.name ] = name;
    field_row[field_model.scene] = scene;

    FieldControlPane *control_pane = Gtk::manage(
      new FieldControlPane(name, scene, field_range)
    );
    field_control.append_page(*control_pane);
    control_pane->show();
  }

  void ViewControlPane::on_field_switch() {
    Gtk::TreeModel::iterator active_row = field_switch.get_active();

    if (active_row) {
      Gtk::TreeModel::Row selected_row = *active_row;

      if (selected_row) {
        field_control.set_current_page(selected_row[field_model.id]);
        scene_pane->set_scene(selected_row[field_model.scene]);
        scene_pane->grab_focus();
      }
    }
  }

