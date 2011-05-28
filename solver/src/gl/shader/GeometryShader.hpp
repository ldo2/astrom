#ifndef __gl_GeometryShader_HPP__
#define __gl_GeometryShader_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include <gl/shader/Shader.hpp>

namespace gl {

  class GeometryShader : public Shader {
    public: 
      GeometryShader(GLhandleARB geometry_shader);
      GeometryShader(const char *source, int source_size);
  };

}

#endif /* __gl_GeometryShader_HPP__ */

