#include "ShaderUniformVariable.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <stdexcept>

namespace gl {

/*
 * class ShaderUniformVariable 
 */

  ShaderUniformVariable::ShaderUniformVariable(
    GLhandleARB program_object, 
    const char *name
  ) : program_object(program_object) {
    location = glGetUniformLocationARB(program_object, name);
      
    if (location < 0) {
       std::cerr << "undefined shader uniform variable <"
                << name << "> : " << gluErrorString(glGetError())
                << std::endl;
      //throw std::runtime_error("undefined shader uniform variable");
    }
  }

/*
 * class ShaderUniform1fVariable
 */   
  ShaderUniform1fVariable::ShaderUniform1fVariable(
    GLhandleARB program_object, 
    const char *name
  ) : ShaderUniformVariable(program_object, name) {}

  void ShaderUniform1fVariable::set(GLfloat x) {
    // value[0] = x;
    glUniform1fARB(location, x);
  }

  void ShaderUniform1fVariable::set(GLfloat *x) {
    // value[0] = *x;
    glUniform1fARB(location, *x);
  }

  GLfloat ShaderUniform1fVariable::get() {
    glGetUniformfvARB(program_object, location, value);
    return value[0];
  }

  void ShaderUniform1fVariable::get(GLfloat &x) {
    glGetUniformfvARB(program_object, location, value);
    x = value[0];
  }

/*
 * class ShaderUniform2fVariable
 */

  ShaderUniform2fVariable::ShaderUniform2fVariable(
    GLhandleARB program_object, 
    const char *name
  ) : ShaderUniformVariable(program_object, name) {}

  void ShaderUniform2fVariable::set(GLfloat x, GLfloat y) {
    value[0] = x;
    value[1] = y;

    glUniform2fvARB(location, 1, value);
  }

  void ShaderUniform2fVariable::set(GLfloat *xy) {
    glUniform2fvARB(location, 1, xy);
  }

  GLfloat *ShaderUniform2fVariable::get() {
    glGetUniformfvARB(program_object, location, value);
    return value;
  }

  void ShaderUniform2fVariable::get(GLfloat &x, GLfloat &y) {
    glGetUniformfvARB(program_object, location, value);

    x = value[0];
    y = value[1];
  }


/*
 * class ShaderUniform3fVariable 
 */
  ShaderUniform3fVariable::ShaderUniform3fVariable(
    GLhandleARB program_object, 
    const char *name
  ) : ShaderUniformVariable(program_object, name) {}

  void ShaderUniform3fVariable::set(GLfloat x, GLfloat y, GLfloat z) {
    value[0] = x;
    value[1] = y;
    value[2] = z;

    glUniform3fvARB(location, 1, value);
  }

  void ShaderUniform3fVariable::set(GLfloat *xyz) {
    glUniform3fvARB(location, 1, xyz);
  }

  GLfloat *ShaderUniform3fVariable::get() {
    glGetUniformfvARB(program_object, location, value);
    return value;
  }

  void ShaderUniform3fVariable::get(GLfloat &x, GLfloat &y, GLfloat &z) {
    glGetUniformfvARB(program_object, location, value);

    x = value[0];
    y = value[1];
    z = value[2];
  }

/*
 * class ShaderUniform4fVariable 
 */
  ShaderUniform4fVariable::ShaderUniform4fVariable(
    GLhandleARB program_object, 
    const char *name
  ) : ShaderUniformVariable(program_object, name) {}

  void ShaderUniform4fVariable::set(GLfloat x, GLfloat y, 
                                    GLfloat z, GLfloat w) {
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = w;

    glUniform4fvARB(location, 1, value);
  }

  void ShaderUniform4fVariable::set(GLfloat *xyzw) {
    glUniform4fvARB(location, 1, xyzw);
  }

  GLfloat *ShaderUniform4fVariable::get() {
    glGetUniformfvARB(program_object, location, value);
    return value;
  }

  void ShaderUniform4fVariable::get(GLfloat &x, GLfloat &y, 
                                    GLfloat &z, GLfloat &w) {
    glGetUniformfvARB(program_object, location, value);

    x = value[0];
    y = value[1];
    z = value[2];
    w = value[3];
  }

/*
 * class ShaderUniform1iVariable
 */   
  ShaderUniform1iVariable::ShaderUniform1iVariable(
    GLhandleARB program_object, 
    const char *name
  ) : ShaderUniformVariable(program_object, name) {}

  void ShaderUniform1iVariable::set(GLint i) {
    // value[0] = i;
    glUniform1iARB(location, i);
  }

  void ShaderUniform1iVariable::set(GLint *i) {
    // value[0] = *i;
    glUniform1iARB(location, *i);
  }

  GLint ShaderUniform1iVariable::get() {
    glGetUniformivARB(program_object, location, value);
    return value[0];
  }

  void ShaderUniform1iVariable::get(GLint &i) {
    glGetUniformivARB(program_object, location, value);
    i = value[0];
  }

}

