#include "GeometryShader.hpp"

#include "ErrorHelper.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

namespace gl {
/*
 * class GeometryShader
 */
  GeometryShader::GeometryShader(GLhandleARB geometry_shader)
   : Shader(geometry_shader) {}

  GeometryShader::GeometryShader(
    const char *source, 
    int source_size
  ) {
    shader = glCreateShaderObjectARB(GL_GEOMETRY_SHADER_EXT);

    glShaderSourceARB(shader, 1, &source, &source_size);

    glCompileShaderARB(shader);
    ErrorHelper::check_ARB_handle(shader, GL_OBJECT_COMPILE_STATUS_ARB);
  }
}

