#ifndef __gl_ShaderUniformVariable_HPP__
#define __gl_ShaderUniformVariable_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

namespace gl {

  class ShaderUniformVariable {
    protected: 
      GLhandleARB program_object;
      GLint location;

    public:
      ShaderUniformVariable(GLhandleARB program_object, 
                             const char *name);
  };

  class ShaderUniform1fVariable : public ShaderUniformVariable {
    protected:
      GLfloat value[1];

    public:
      ShaderUniform1fVariable(GLhandleARB program_object, 
                               const char *name);

      void set(GLfloat x);
      void set(GLfloat *x);

      GLfloat get();
      void get(GLfloat &x);
  };

  class ShaderUniform2fVariable : public ShaderUniformVariable {
    protected:
      GLfloat value[2];

    public:
      ShaderUniform2fVariable(GLhandleARB program_object, 
                               const char *name);

      void set(GLfloat x, GLfloat y);
      void set(GLfloat *xy);

      GLfloat *get();
      void get(GLfloat &x, GLfloat &y);
  };

  class ShaderUniform3fVariable : public ShaderUniformVariable {
    protected:
      GLfloat value[3];

    public:
      ShaderUniform3fVariable(GLhandleARB program_object, 
                               const char *name);

      void set(GLfloat x, GLfloat y, GLfloat z);
      void set(GLfloat *xyz);

      GLfloat *get();
      void get(GLfloat &x, GLfloat &y, GLfloat &z);
  };

  class ShaderUniform4fVariable : public ShaderUniformVariable {
    protected:
      GLfloat value[4];

    public:
      ShaderUniform4fVariable(GLhandleARB program_object, 
                               const char *name);

      void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
      void set(GLfloat *xyzw);

      GLfloat *get();
      void get(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w);
  };

  class ShaderUniform1iVariable : public ShaderUniformVariable {
    protected:
      GLint value[1];

    public:
      ShaderUniform1iVariable(GLhandleARB program_object, 
                               const char *name);

      void set(GLint i);
      void set(GLint *i);

      GLint get();
      void get(GLint &i);
  };

}

#endif /* __gl_ShaderUniformVariable_HPP__ */

