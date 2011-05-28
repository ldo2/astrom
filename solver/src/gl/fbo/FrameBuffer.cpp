#include "FrameBuffer.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <iostream>
#include <stdexcept>

namespace gl {

  /*
   * class FrameBuffer {
   */

    bool FrameBuffer::is_valid_dimention(GLint width, GLint height) {
      return width > 0 && width < GL_MAX_RENDERBUFFER_SIZE_EXT &&
              height > 0 && height < GL_MAX_RENDERBUFFER_SIZE_EXT;
    }

    GLenum FrameBuffer::parse_depth_format(int flags) {
      GLenum format = 0;

      if (flags & DEPTH16) format = GL_DEPTH_COMPONENT16_ARB;
      if (flags & DEPTH24) format = GL_DEPTH_COMPONENT24_ARB;
      if (flags & DEPTH32) format = GL_DEPTH_COMPONENT32_ARB;

      return format;
    }

    GLenum FrameBuffer::parse_stencil_format(int flags) {
      GLenum format = 0;

      if (flags & STENCIL1 ) format = GL_STENCIL_INDEX1_EXT;
      if (flags & STENCIL4 ) format = GL_STENCIL_INDEX4_EXT;
      if (flags & STENCIL8 ) format = GL_STENCIL_INDEX8_EXT;
      if (flags & STENCIL16) format = GL_STENCIL_INDEX16_EXT;

      return format;
    }

    FrameBuffer::FrameBuffer(GLint width, GLint height, int flags)
     : width(width), height(height), frame_buffer(0),
       depth_buffer(0), stencil_buffer(0) {
      if (!FrameBuffer::is_valid_dimention(width, height)) {
        throw std::runtime_error(
          "GL FrameBuffer error: unsupported buffer dimention"
        );
      }

      glGenFramebuffersEXT(1, &frame_buffer);

      bind();

      GLenum   depth_format = FrameBuffer::parse_depth_format  (flags),
             stencil_format = FrameBuffer::parse_stencil_format(flags);

      if (depth_format != 0) {
        glGenRenderbuffersEXT(1, &depth_buffer);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buffer);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, depth_format, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, 
                                     GL_RENDERBUFFER_EXT, depth_buffer);
      }

      if (stencil_format != 0) {
        glGenRenderbuffersEXT(1, &stencil_buffer);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, stencil_buffer);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, stencil_format, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, 
                                     GL_RENDERBUFFER_EXT, stencil_buffer);
      }

      //GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
                                                  
      unbind();
/*
      if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
        throw std::runtime_error(
          "GL FrameBuffer error: unable to create framebuffer"
        );
      }
 */
    }

    FrameBuffer::~FrameBuffer() {
      if (depth_buffer != 0) {
        glDeleteRenderbuffersEXT(1, &depth_buffer);
      }
      if (stencil_buffer != 0) {
        glDeleteRenderbuffersEXT(1, &stencil_buffer);
      }
      if (frame_buffer != 0) {
        glDeleteFramebuffersEXT(1, &frame_buffer);
      }
    }

    GLint FrameBuffer::get_width() const {
      return width;
    }

    GLint FrameBuffer::get_height() const {
      return height;
    }

    bool FrameBuffer::has_depth() const {
      return depth_buffer != 0;
    }
    bool FrameBuffer::has_stencil() const {
      return stencil_buffer != 0;
    }

    void FrameBuffer::bind() {
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buffer);
    }
    void FrameBuffer::unbind() {
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

    void FrameBuffer::attach_color_texture(GLenum target, GLuint texture_id, 
                                            int attachment_id) {
      if (target != GL_TEXTURE_2D && (target < GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB ||
                                       target > GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB)) {
        throw std::runtime_error(
          "GL FrameBuffer error: unsupported texture target"
          " (support only GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP_*)"
        );
      }

      glFramebufferTexture2DEXT(
        GL_FRAMEBUFFER_EXT, 
        GL_COLOR_ATTACHMENT0_EXT + attachment_id,
        target, texture_id, 0
      );
    }

    void FrameBuffer::attach_depth_texture(GLenum target, GLuint texture_id) {
      glFramebufferTexture2DEXT(
        GL_FRAMEBUFFER_EXT, 
        GL_DEPTH_ATTACHMENT_EXT,
        target, texture_id, 0
      );
    }

    void FrameBuffer::detach_color_texture(GLenum target) {
      attach_color_texture(target, 0);
    }

    void FrameBuffer::detach_depth_texture(GLenum target) {
      attach_depth_texture(target, 0);
    }

    GLint FrameBuffer::max_color_attachments() {
      GLint value;

      glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &value);

      return value;
    }

}

