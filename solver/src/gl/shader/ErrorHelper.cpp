#include "ErrorHelper.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <stdexcept>

namespace gl {

#define GL_ERROR_HELPER_LOG_MESSAGE_SIZE (1048576)

  void ErrorHelper::check_ARB_handle(GLhandleARB handle, GLenum param) {
    static GLcharARB message[GL_ERROR_HELPER_LOG_MESSAGE_SIZE];
    GLint state;
    
    glGetObjectParameterivARB(handle, param, &state);
    glGetInfoLogARB(handle, sizeof(message), NULL, message);

    std::cout << "GL log message: " << message << std::endl;
    if (state != GL_TRUE) throw std::runtime_error("GL ARB handle error");
  }

}

