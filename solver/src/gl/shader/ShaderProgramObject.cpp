#include "ShaderProgramObject.hpp"

#include <gl/shader/ErrorHelper.hpp>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

namespace gl {

/*
 * class ShaderProgramObject 
 */

  ShaderProgramObject::ShaderProgramObject(GLhandleARB program_object)
    : program_object(program_object) {}

  ShaderProgramObject::ShaderProgramObject(
    const VertexShader   &vertex_shader, 
    const FragmentShader &fragment_shader
  ) {
    program_object = glCreateProgramObjectARB();

    glAttachObjectARB(program_object, vertex_shader.get_ARB_handle());
    glAttachObjectARB(program_object, fragment_shader.get_ARB_handle());

    glLinkProgramARB(program_object);
    ErrorHelper::check_ARB_handle(program_object, GL_OBJECT_LINK_STATUS_ARB);

    glValidateProgramARB(program_object);
    ErrorHelper::check_ARB_handle(program_object, GL_OBJECT_VALIDATE_STATUS_ARB); 
  }

  ShaderProgramObject::ShaderProgramObject(
    const GeometryShader &geometry_shader, 
    const VertexShader   &vertex_shader, 
    const FragmentShader &fragment_shader
  ) {
    program_object = glCreateProgramObjectARB();

    glAttachObjectARB(program_object, vertex_shader.get_ARB_handle());
    glAttachObjectARB(program_object, fragment_shader.get_ARB_handle());
    glAttachObjectARB(program_object, geometry_shader.get_ARB_handle());

    glLinkProgramARB(program_object);
    ErrorHelper::check_ARB_handle(program_object, GL_OBJECT_LINK_STATUS_ARB);

    glValidateProgramARB(program_object);
    ErrorHelper::check_ARB_handle(program_object, GL_OBJECT_VALIDATE_STATUS_ARB); 
  }


  GLhandleARB ShaderProgramObject::get_ARB_handle() {
    return program_object;
  }

  void ShaderProgramObject::bind() {
    glUseProgramObjectARB(program_object);
  }

  void ShaderProgramObject::unbind() {
    glUseProgramObjectARB(0);
  }

}


