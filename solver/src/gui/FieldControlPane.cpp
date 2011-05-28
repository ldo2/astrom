#include "FieldControlPane.hpp"

#include <limits>

  FieldControlPane::FieldControlPane(
    Glib::ustring field_name, 
    GLScene *field_scene,
    FieldRange *field_range
  ) : field_scene(field_scene), field_range(field_range) {
    // add name label
    {
      Gtk::Label *name_label = Gtk::manage(new Gtk::Label(field_name));
      name_label->show();
      pack_start(*name_label, Gtk::PACK_SHRINK);
    }

    // add field value range control
    {
      Gtk::Frame *range_frame = Gtk::manage(new Gtk::Frame("Values range"));
      pack_start(*range_frame, Gtk::PACK_SHRINK);

      Gtk::Table *range_frame_content = Gtk::manage(new Gtk::Table(2, 2));
      range_frame->add(*range_frame_content);

      double infinity = std::numeric_limits<double>::infinity();

      // range min control
      {
        Gtk::Label *min_label = Gtk::manage(new Gtk::Label("min:", Gtk::ALIGN_RIGHT));
        range_frame_content->attach(
          *min_label, 0, 1, 0, 1, 
          Gtk::FILL | Gtk::EXPAND, Gtk::FILL | Gtk::EXPAND, 5, 2
        );

        min_input = Gtk::manage(new Gtk::SpinButton());
        range_frame_content->attach(*min_input, 1, 2, 0, 1);

        min_input->set_range(-infinity, infinity);
        min_input->set_value(0.0);
        min_input->set_increments(0.01, 0.1);
        min_input->set_digits(2);

        min_input->signal_value_changed().connect( 
          sigc::mem_fun(*this, &FieldControlPane::on_range_min_changed) 
        );
      }

      // range max control
      {
        Gtk::Label *max_label = Gtk::manage(new Gtk::Label("max:", Gtk::ALIGN_RIGHT));
        range_frame_content->attach(
          *max_label, 0, 1, 1, 2, 
          Gtk::FILL | Gtk::EXPAND, Gtk::FILL | Gtk::EXPAND, 5, 2
        );

        max_input = Gtk::manage(new Gtk::SpinButton());
        range_frame_content->attach(*max_input, 1, 2, 1, 2);

        max_input->set_range(-infinity, infinity);
        max_input->set_value(1.0);
        max_input->set_increments(0.01, 0.1);
        max_input->set_digits(2);

        max_input->signal_value_changed().connect( 
          sigc::mem_fun(*this, &FieldControlPane::on_range_max_changed) 
        );
      }

      range_frame->show_all();
    }
    
  }

  void FieldControlPane::on_range_min_changed() {
    double min_value = min_input->get_value();
    field_range->set_min(min_value);
  }

  void FieldControlPane::on_range_max_changed() {
    double max_value = max_input->get_value();
    field_range->set_max(max_value);
  }

