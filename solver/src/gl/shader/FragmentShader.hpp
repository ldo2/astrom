#ifndef __gl_FragmentShader_HPP__
#define __gl_FragmentShader_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include <gl/shader/Shader.hpp>

namespace gl {

  class FragmentShader : public Shader {
    public: 
      FragmentShader(GLhandleARB fragment_shader);
      FragmentShader(const char *source, int source_size);
  };

}

#endif /* __gl_FragmentShader_HPP__ */

