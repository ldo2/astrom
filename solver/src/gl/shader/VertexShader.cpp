#include "VertexShader.hpp"

#include "Shader.hpp"
#include "ErrorHelper.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

/*
 * VertexShader
 */

  VertexShader::VertexShader(GLhandleARB vertex_shader) 
   : Shader(vertex_shader) {}

  VertexShader::VertexShader(const char *source, int source_size) {
    shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);

    glShaderSourceARB(shader, 1, &source, &source_size);

    glCompileShaderARB(shader);
    ErrorHelper::check_ARB_handle(shader, GL_OBJECT_COMPILE_STATUS_ARB); 
  }

}

