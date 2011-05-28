#ifndef __gl_ShaderProgramObject_HPP__
#define __gl_ShaderProgramObject_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include <gl/shader/VertexShader.hpp>
#include <gl/shader/FragmentShader.hpp>
#include <gl/shader/GeometryShader.hpp>

namespace gl {

  class ShaderProgramObject {
    protected: 
      GLhandleARB program_object;

    public:
      ShaderProgramObject(GLhandleARB program_object);
      ShaderProgramObject(const VertexShader   &vertex_shader, 
                          const FragmentShader &fragment_shader);
      ShaderProgramObject(const GeometryShader &geometry_shader, 
                          const VertexShader   &vertex_shader, 
                          const FragmentShader &fragment_shader);

      GLhandleARB get_ARB_handle();

      void bind();
      void unbind();
  };

}

#endif /* __gl_ShaderProgramObject_HPP__ */

