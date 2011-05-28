#include "ParticleShader.hpp"

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
"float weight(float R) {"
"  return R <= 1.0 ? (1.0 + 3.0*R)*(1.0 - R)*(1.0 - R)*(1.0 - R) : 0.0;"
"}"

"void main (void) {"
"  float r  = length(gl_TexCoord[0].xy);"
"  if (r > 1.0) discard;"
"  gl_FragColor = weight(r) * gl_Color;"
"}";

/*
 * class ParticleShader
 */

  ParticleShader::ParticleShader()
   : gl::ShaderProgramObject(
       gl::VertexShader(vertex_shader_source, sizeof(vertex_shader_source)), 
       gl::FragmentShader(fragment_shader_source, sizeof(fragment_shader_source))
     )
  {}

