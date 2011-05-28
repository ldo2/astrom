#include "FragmentShader.hpp"

#include "ErrorHelper.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

/*
 * class FragmentShader
 */
  FragmentShader::FragmentShader(GLhandleARB fragment_shader)
   : Shader(fragment_shader) {}

  FragmentShader::FragmentShader(
    const char *source, 
    int source_size
  ) {
    shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    glShaderSourceARB(shader, 1, &source, &source_size);

    glCompileShaderARB(shader);
    ErrorHelper::check_ARB_handle(shader, GL_OBJECT_COMPILE_STATUS_ARB);
  }

}

