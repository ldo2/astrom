#ifndef __gl_Shader_HPP__
#define __gl_Shader_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

  class Shader {
    protected:
      GLhandleARB shader;

    public:
      Shader();
      Shader(GLhandleARB shader);

      GLhandleARB get_ARB_handle() const;

      static void load_shader_source(const char *filename, 
                                      char *&source, int &source_size);
  };

}

#endif /* __gl_Shader_HPP__ */

