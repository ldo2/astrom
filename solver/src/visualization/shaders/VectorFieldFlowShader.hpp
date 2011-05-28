#ifndef __VectorFieldFlowShader_HPP__
#define __VectorFieldFlowShader_HPP__

#include <gl/shader/ShaderProgramObject.hpp>
#include <gl/shader/ShaderUniformVariable.hpp>

class VectorFieldFlowShader : public gl::ShaderProgramObject {
  public:
    gl::ShaderUniform1iVariable noise_map;

    gl::ShaderUniform3fVariable min;
    gl::ShaderUniform3fVariable max;

    gl::ShaderUniform3fVariable u_axis;
    gl::ShaderUniform3fVariable v_axis;

    VectorFieldFlowShader();
};

#endif /* __VectorFieldFlowShader_HPP__ */
