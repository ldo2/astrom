#ifndef __gl_FrameBuffer_HPP__
#define __gl_FrameBuffer_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

  class FrameBuffer {
    protected:
      GLint width, height;

      GLuint   frame_buffer,
               depth_buffer,
             stencil_buffer;

      static bool is_valid_dimention(GLint width, GLint height);

      static GLenum parse_depth_format(int flags);
      static GLenum parse_stencil_format(int flags);

    public: 
      enum {
        DEPTH16 = 1,
        DEPTH24 = 2,
        DEPTH32 = 4,

        STENCIL1  =  16,
        STENCIL4  =  32,
        STENCIL8  =  64,
        STENCIL16 = 128,
      };


      FrameBuffer(GLint width, GLint height, int flags = 0);
      ~FrameBuffer();

      GLint get_width() const;
      GLint get_height() const;

      bool has_depth() const;
      bool has_stencil() const;

      void bind();
      void unbind();

      void attach_color_texture(GLenum target, GLuint texture_id, 
                                 int attachment_id = 0);
      void attach_depth_texture(GLenum target, GLuint texture_id);

      void detach_color_texture(GLenum target);
      void detach_depth_texture(GLenum target);

      static GLint max_color_attachments();
  };

}

#endif /* __gl_FrameBuffer_HPP__ */

