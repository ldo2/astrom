#ifndef __FieldSelectorModel_HPP__
#define __FieldSelectorModel_HPP__

#include <gtkmm.h>
#include <visualization/GLScene.hpp>

class FieldSelectorModel : public Gtk::TreeModel::ColumnRecord {
  public:
    Gtk::TreeModelColumn<int>            id;
    Gtk::TreeModelColumn<Glib::ustring>  name;
    Gtk::TreeModelColumn<GLScene *> scene;

    FieldSelectorModel() { 
      add(id);
      add(name);
      add(scene);
    }
};

#endif /* __FieldSelectorModel_HPP__ */

