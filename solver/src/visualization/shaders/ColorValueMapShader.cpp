#include "ColorValueMapShader.hpp"

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

// "const float min_intensity = -2.8, max_intensity = 16.8; "
"uniform vec3 min_value;"
"uniform vec3 max_value;"

"uniform vec3 value_function;"

"void main(void) {"
"  vec4 value = texture2D(value_map, gl_TexCoord[0].xy);"
"  vec3 mapped_value = (vec3(value) - min_value)/(max_value - min_value);"
"  float intensity = 4.0 * clamp(dot(mapped_value, value_function), 0.0, 1.0);"
"  gl_FragColor = vec4("
"    clamp(1.0 - abs(intensity      ), 0.0, 1.0) * vec3(0.0, 0.0, 1.0) + "
"    clamp(1.0 - abs(intensity - 1.0), 0.0, 1.0) * vec3(0.0, 1.0, 1.0) + "
"    clamp(1.0 - abs(intensity - 2.0), 0.0, 1.0) * vec3(0.0, 1.0, 0.0) + "
"    clamp(1.0 - abs(intensity - 3.0), 0.0, 1.0) * vec3(1.0, 1.0, 0.0) + "
"    clamp(1.0 - abs(intensity - 4.0), 0.0, 1.0) * vec3(1.0, 0.0, 0.0),  "
"    1.0"
"  );"
"}";

/*
 * class ColorValueMapShader
 */

  ColorValueMapShader::ColorValueMapShader()
   : gl::ShaderProgramObject(
       gl::VertexShader(vertex_shader_source, sizeof(vertex_shader_source)), 
       gl::FragmentShader(fragment_shader_source, sizeof(fragment_shader_source))
     ), 
     min(get_ARB_handle(), "min_value"),
     max(get_ARB_handle(), "max_value"),
     value_function(get_ARB_handle(), "value_function")
  {}

