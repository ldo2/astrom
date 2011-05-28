#ifndef __gl_VertexShader_HPP__
#define __gl_VertexShader_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include <gl/shader/Shader.hpp>

namespace gl {

  class VertexShader : public Shader {
    public: 
      VertexShader(GLhandleARB vertex_shader);
      VertexShader(const char *source, int source_size);
  };

}

#endif /* __gl_VertexShader_HPP__ */

