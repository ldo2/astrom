#ifndef __gl_ErrorHelper_HPP__
#define __gl_ErrorHelper_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

  class ErrorHelper {
    public:
      static void check_ARB_handle(GLhandleARB handle, GLenum param);
  };

}

#endif /* __gl_ErrorHelper_HPP__ */

