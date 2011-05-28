#ifndef __GLLegendDrawer_HPP__
#define __GLLegendDrawer_HPP__

#include <iostream>
#include <cstdlib>

#include <gtkmm.h>
#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <visualization/DisplayInfo.hpp>

class GLLegendDrawer {
  protected:
    static const Glib::ustring font_name;
    static const GLsizei font_chars_count;

    GLuint font_list_base;
    int font_height, font_leading, 
        font_digit_width, font_char_width;

    int ticks_count;
    double tick_size;

    int label_precision;

    struct {
      double x, y;
    } margin, padding, legend_position, scale_position;

    struct {
      double width, height;
    } legend, scale;

    struct {
      double min, max;
    } range;

    Glib::ustring title;

    void load_pango_font();

  public:
    GLLegendDrawer(double range_min = 0.0, double range_max = 1.0, 
                    int label_precision = 2, 
                    Glib::ustring title = Glib::ustring(""),
                    int ticks_count = 4, double tick_size = 3.0);
    virtual ~GLLegendDrawer();

    void set_title(Glib::ustring new_title);
    void set_range(double range_min, double range_max);

    void set_ticks_count(int new_ticks_count);
    void set_tick_size(double new_tick_size);

    void set_precision(int precision);

    virtual void display(DisplayInfo &info);

  protected:
    void display_background();
    void display_scale();
    void display_ticks();
    void display_labels();
    void display_title();
};

#endif /* __GLLegendDrawer_HPP__ */

