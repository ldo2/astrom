#ifndef __gl_VertexBuffer_HPP__
#define __gl_VertexBuffer_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

  class VertexBuffer {
    protected:
      GLuint id;
      GLenum target;

    public:
      VertexBuffer();
      ~VertexBuffer();

      void bind(GLenum bind_target);
      void unbind();

      void set_data(GLsizeiptrARB size, const void *data_ptr, GLenum usage);
      void set_sub_data(GLsizeiptrARB offset, GLsizeiptrARB size, const void *data_ptr);

      void *map(GLenum access);
      bool unmap();
  };

}

#endif /* __gl_VertexBuffer_HPP__ */

