#ifndef __ColorValueMapShader_HPP__
#define __ColorValueMapShader_HPP__

#include <gl/shader/ShaderProgramObject.hpp>
#include <gl/shader/ShaderUniformVariable.hpp>

class ColorValueMapShader : public gl::ShaderProgramObject {
  public:
    gl::ShaderUniform3fVariable min;
    gl::ShaderUniform3fVariable max;
    gl::ShaderUniform3fVariable value_function;

    ColorValueMapShader();
};

#endif /* __ColorValueMapShader_HPP__ */

