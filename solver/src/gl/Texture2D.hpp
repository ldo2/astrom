#ifndef __Texture2D_HPP__
#define __Texture2D_HPP__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

namespace gl {

  class Texture2D {
    protected:
      GLuint texture_id;

    public:
      Texture2D(GLint width, GLint height);
      ~Texture2D();

      GLuint get_texture_id() const;

      void bind();
      void unbind();
  };

}

#endif /* __Texture2D_HPP__ */
