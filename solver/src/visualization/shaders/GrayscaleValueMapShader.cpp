#include "GrayscaleValueMapShader.hpp"

#include <gl/shader/ShaderProgramObject.hpp>

#include <gl/shader/VertexShader.hpp>
#include <gl/shader/FragmentShader.hpp>

static const char vertex_shader_source[] =
"void main (void) {"
"  gl_FrontColor  = gl_Color;"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"  gl_Position    = ftransform();"
"}";

static const char fragment_shader_source[] = 
"uniform sampler2D value_map;"

"uniform float min_value;"
"uniform float max_value;"

"void main(void) {"
"  vec4 value = texture2D(value_map, gl_TexCoord[0].xy);"
"  vec4 mapped_value = (value - vec4(min_value))/(max_value - min_value);"
"  float intensity = clamp(mapped_value.r, 0.0, 1.0);"
"  gl_FragColor = vec4(vec3(intensity), 1.0);"
"}";

/*
 * class GrayscaleValueMapShader
 */

  GrayscaleValueMapShader::GrayscaleValueMapShader()
   : gl::ShaderProgramObject(
       gl::VertexShader(vertex_shader_source, sizeof(vertex_shader_source)), 
       gl::FragmentShader(fragment_shader_source, sizeof(fragment_shader_source))
     ), 
     min(get_ARB_handle(), "min_value"),
     max(get_ARB_handle(), "max_value")
  {}

