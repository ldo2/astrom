#include "VertexBuffer.hpp"

#include <stdexcept>

namespace gl {
/*
 * class VertexBuffer 
 */

  VertexBuffer::VertexBuffer() : id(0), target(0) {
    glGenBuffersARB(1, &id);

    if (glIsBufferARB(id) != GL_TRUE) {
      throw std::runtime_error(
        "GL VertexBuffer error: unable to create ARB buffer"
      );
    }
  }

  VertexBuffer::~VertexBuffer() {
    glDeleteBuffersARB(1, &id);
  }

  void VertexBuffer::bind(GLenum bind_target) {
    target = bind_target;

    glBindBufferARB(target, id);
  }

  void VertexBuffer::unbind() {
    glBindBufferARB(target, 0);
  }

  void VertexBuffer::set_data(GLsizeiptrARB size, const void *data_ptr, 
                               GLenum usage) {
    glBufferDataARB(target, size, data_ptr, usage);
  }

  void VertexBuffer::set_sub_data(GLsizeiptrARB offset, GLsizeiptrARB size, 
                                   const void *data_ptr) {
    glBufferSubDataARB(target, offset, size, data_ptr);
  }

  void *VertexBuffer::map(GLenum access) {
    return glMapBufferARB(target, access);
  }

  bool VertexBuffer::unmap() {
    return glUnmapBufferARB(target) == GL_TRUE;
  }

}

