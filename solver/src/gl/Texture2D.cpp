#include "Texture2D.hpp"

namespace gl {

/*
 * class Texture2D 
 */

  Texture2D::Texture2D(GLint width, GLint height) {
    glGenTextures(1, &texture_id);

    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, /*GL_RGBA8*/GL_RGBA32F_ARB,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    unbind();
  }

  Texture2D::~Texture2D() {
    glDeleteTextures(1, &texture_id);
  }

  GLuint Texture2D::get_texture_id() const {
    return texture_id;
  }

  void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
  }

  void Texture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

}

