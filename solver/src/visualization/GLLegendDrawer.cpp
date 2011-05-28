#include "GLLegendDrawer.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>

/*
 * class GLLegendDrawer 
 */

  const Glib::ustring GLLegendDrawer::font_name("courier 12");
  const GLsizei GLLegendDrawer::font_chars_count(128);

  void GLLegendDrawer::load_pango_font() {
    font_list_base = glGenLists(font_chars_count);
    if (!font_list_base) {
      std::cerr << "GLLegendDrawer: can't allocate GL display lists"
                   " for bitmap font" << std::endl;
      throw std::runtime_error("GLLegendDrawer: font loading error");
    }

    Pango::FontDescription font_description(font_name);

    Glib::RefPtr<Pango::Font> font = Gdk::GL::Font::use_pango_font(
      font_description, 0, font_chars_count, font_list_base
    );
    if (!font) {
      std::cerr << "GLLegendDrawer: can't load font " 
                << font_name << std::endl;
      throw std::runtime_error("GLLegendDrawer: font loading error");
    }

    Pango::FontMetrics font_metrics = font->get_metrics();

    font_height  = PANGO_PIXELS(font_metrics.get_ascent() + 
                                 font_metrics.get_descent());
    font_leading = font_height/2;

    font_digit_width = PANGO_PIXELS(font_metrics.get_approximate_digit_width());
    font_char_width  = PANGO_PIXELS(font_metrics.get_approximate_char_width());
  }

  GLLegendDrawer::GLLegendDrawer(double range_min, double range_max, 
                                  int label_precision, Glib::ustring title,
                                  int ticks_count, double tick_size)
   : font_list_base(0), font_height(0), font_leading(0),
     font_digit_width(0), font_char_width(0),
     ticks_count(ticks_count), tick_size(tick_size), 
     label_precision(label_precision), title(title) {
    margin.x = 20.0; 
    margin.y = 10.0;

    padding.x = 20.0; 
    padding.y = 10.0;

    legend.width  = 0.0; 
    legend.height = 0.0;

    scale.width  = 0.0; 
    scale.height = 20.0;

    set_ticks_count(ticks_count);
    set_range(range_min, range_max);

    load_pango_font();
  }

  GLLegendDrawer::~GLLegendDrawer() {
    glDeleteLists(font_list_base, font_chars_count);
  }


  void GLLegendDrawer::set_title(Glib::ustring new_title) {
    title = new_title;
  }

  void GLLegendDrawer::set_range(double range_min, double range_max) {
    range.min = range_min;
    range.max = range_max;
  
    if (range_min == range_max) {
      // error: zero range
      range.max += 1.0e-6; // add some epsilon
    }
  }

  void GLLegendDrawer::set_ticks_count(int new_ticks_count) {
    ticks_count = std::max(new_ticks_count, 2);
  }

  void GLLegendDrawer::set_tick_size(double new_tick_size) {
    tick_size = new_tick_size;
  }

  void GLLegendDrawer::set_precision(int precision) {
    label_precision = precision;
  }

  void GLLegendDrawer::display(DisplayInfo &info) {
    /* rescale legend screen dimention */
    legend.width  = info.screen.width - 2*margin.x; 
    legend.height = scale.height + 2*(padding.y + font_leading + font_height);

    scale.width  = legend.width - 2 * (padding.x +
                    font_digit_width * label_precision); 

    /* calculate legend positions */
    legend_position.x = margin.x;
    legend_position.y = margin.y;

    scale_position.x = legend_position.x + padding.x + 
                        font_digit_width * label_precision;
    scale_position.y = legend_position.y + padding.y + 
                        2 * (font_leading + font_height);

    /* set GL coordinates transformation to screen space */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, info.screen.width, 0.0, info.screen.height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* display process */
    display_background();
    display_scale();
    display_ticks();
    display_labels();
    display_title();
  }


  void GLLegendDrawer::display_background() {
    const int cos_table_size = 6;
    const double cos_table[] = {
      0.974927912181824,
      0.900968867902419,
      0.78183148246803,
      0.623489801858734,
      0.433883739117558,
      0.222520933956314
    };

    const double round_radius = std::min(padding.x, padding.y);

    double vertices[][2] = {
      // outer box
      { legend_position.x,                
        legend_position.y                 }, // 0
      { legend_position.x,                
        legend_position.y + legend.height }, // 1
      { legend_position.x + legend.width, 
        legend_position.y + legend.height }, // 2
      { legend_position.x + legend.width, 
        legend_position.y                 }, // 3
      // inner box
      { legend_position.x + round_radius,                
        legend_position.y + round_radius                 }, // 4 
      { legend_position.x + round_radius,                
        legend_position.y - round_radius + legend.height }, // 5
      { legend_position.x - round_radius + legend.width, 
        legend_position.y - round_radius + legend.height }, // 6
      { legend_position.x - round_radius + legend.width, 
        legend_position.y + round_radius                 }, // 7
      // x extend
      { legend_position.x,                
        legend_position.y + round_radius                 }, // 8 
      { legend_position.x,                
        legend_position.y - round_radius + legend.height }, // 9
      { legend_position.x + legend.width, 
        legend_position.y - round_radius + legend.height }, // 10
      { legend_position.x + legend.width, 
        legend_position.y + round_radius                 }, // 11
      // y extend
      { legend_position.x + round_radius,                
        legend_position.y                                }, // 12 
      { legend_position.x + round_radius,                
        legend_position.y + legend.height                }, // 13
      { legend_position.x - round_radius + legend.width, 
        legend_position.y + legend.height                }, // 14
      { legend_position.x - round_radius + legend.width, 
        legend_position.y                                }, // 15
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0, 1.0, 1.0, 0.5);

    /* draw background rectangle */
/*
    glBegin(GL_QUADS);
      glVertex2dv(vertices[0]);
      glVertex2dv(vertices[1]);
      glVertex2dv(vertices[2]);
      glVertex2dv(vertices[3]);
    glEnd();
 */

    /* draw background round rectangle */
    glBegin(GL_QUADS);
      // center
      glVertex2dv(vertices[4]);
      glVertex2dv(vertices[5]);
      glVertex2dv(vertices[6]);
      glVertex2dv(vertices[7]);
      // left side
      glVertex2dv(vertices[8]);
      glVertex2dv(vertices[4]);
      glVertex2dv(vertices[5]);
      glVertex2dv(vertices[9]);
      // up side
      glVertex2dv(vertices[13]);
      glVertex2dv(vertices[ 5]);
      glVertex2dv(vertices[ 6]);
      glVertex2dv(vertices[14]);
      // right side
      glVertex2dv(vertices[ 6]);
      glVertex2dv(vertices[10]);
      glVertex2dv(vertices[11]);
      glVertex2dv(vertices[ 7]);
      // down side
      glVertex2dv(vertices[ 7]);
      glVertex2dv(vertices[15]);
      glVertex2dv(vertices[12]);
      glVertex2dv(vertices[ 4]);
    glEnd();
     
    const int corners_count = 4;
    const double corners_directions[][2] = {
      {-1.0, -1.0}, {-1.0, 1.0}, {1.0, 1.0}, {1.0, -1.0}
    };

    /* draw round corners */
    for (int corner = 0; corner < corners_count; ++corner) {
      glBegin(GL_TRIANGLE_FAN);
        glVertex2dv(vertices[4 + corner]);
        glVertex2dv(vertices[8 + corner]);

        for (int phi = 0; phi < cos_table_size; ++phi) {
          glVertex2d(
            vertices[4 + corner][0] + round_radius *
            corners_directions[corner][0] * cos_table[phi],
            vertices[4 + corner][1] + round_radius *
            corners_directions[corner][1] * cos_table[cos_table_size - phi - 1] 
          );
        }

        glVertex2dv(vertices[12 + corner]);
      glEnd();
    }

    glDisable(GL_BLEND);
  }

  void GLLegendDrawer::display_scale() { 
    const int   colors_count = 5;
    const float colors_map[][3] = {
      {0.0, 0.0, 1.0},
      {0.0, 1.0, 1.0},
      {0.0, 1.0, 0.0},
      {1.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
    };

    double segment_x;

    glBegin(GL_TRIANGLE_STRIP);
      for (int color = 0; color < colors_count; ++color) {
        glColor3fv(colors_map[color]);

        segment_x = scale_position.x + (double) color/(colors_count - 1) * 
                                                 scale.width;

        glVertex2d(segment_x, scale_position.y);
        glVertex2d(segment_x, scale_position.y + scale.height);
      }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
      glVertex2d(scale_position.x, scale_position.y);
      glVertex2d(scale_position.x, scale_position.y + scale.height);
      glVertex2d(scale_position.x + scale.width, 
                                   scale_position.y + scale.height);
      glVertex2d(scale_position.x + scale.width, 
                                   scale_position.y);
    glEnd();
  }

  void GLLegendDrawer::display_ticks() {
    double tick_x;

    glBegin(GL_LINES);
      for (int tick = 0; tick <= ticks_count; ++tick) {
        tick_x = scale_position.x + (double) tick/ticks_count * scale.width;
        glVertex2d(tick_x, scale_position.y - tick_size);
        glVertex2d(tick_x, scale_position.y + tick_size);
      }
    glEnd();
  }

  void GLLegendDrawer::display_labels() {
    Glib::ustring label;
    double label_value;

    glColor3f(0.0, 0.0, 0.0);
    glListBase(font_list_base);
    for (int tick = 0; tick <= ticks_count; ++tick) {
      std::stringstream stream;
      stream.setf(std::ios::fixed, std::ios::floatfield);
      // stream.setf(std::ios::scientific, std::ios::floatfield);
      stream.precision(label_precision);

      label_value = range.min + (double) tick/ticks_count * 
                                 (range.max - range.min);
      stream << label_value;
      stream >> label;

      glRasterPos2f(
        scale_position.x + (double) tick/ticks_count * scale.width - 
          font_digit_width * (label.find('.') + 0.5), 
        scale_position.y - font_height - font_leading
      );
    
      glCallLists(label.length(), GL_UNSIGNED_BYTE, label.c_str());
    }
  }

  void GLLegendDrawer::display_title() {
    size_t title_length = title.length();

    glColor3f(0.0, 0.0, 0.0);
    glListBase(font_list_base);
    glRasterPos2f(
      legend_position.x + 0.5*(legend.width - title_length * font_char_width), 
      legend_position.y + padding.y
    );
    
    glCallLists(title_length, GL_UNSIGNED_BYTE, title.c_str());
  }


