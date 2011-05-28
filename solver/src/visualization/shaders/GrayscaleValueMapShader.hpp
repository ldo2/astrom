#ifndef __GrayscaleValueMapShader_HPP__
#define __GrayscaleValueMapShader_HPP__

#include <gl/shader/ShaderProgramObject.hpp>
#include <gl/shader/ShaderUniformVariable.hpp>

class GrayscaleValueMapShader : public gl::ShaderProgramObject {
  public:
    gl::ShaderUniform1fVariable min;
    gl::ShaderUniform1fVariable max;

    GrayscaleValueMapShader();
};

#endif /* __GrayscaleValueMapShader_HPP__ */

