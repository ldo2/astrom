#include "VectorFieldFlowShader.hpp"

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
"uniform sampler2D vector_field;"
"uniform sampler2D noise_map;"

"uniform vec3 min_value;"
"uniform vec3 max_value;"

"uniform vec3 u_axis;"
"uniform vec3 v_axis;"

"vec3 rescale_vector_value(vec3 vector) {"
"  return (vector - min_value)/(max_value - min_value);"
"}"

"vec3 color_map(float quadruplicate_intensity) {"
"  return "
"    clamp(1.0 - abs(quadruplicate_intensity      ), 0.0, 1.0) * vec3(0.0, 0.0, 1.0) + "
"    clamp(1.0 - abs(quadruplicate_intensity - 1.0), 0.0, 1.0) * vec3(0.0, 1.0, 1.0) + "
"    clamp(1.0 - abs(quadruplicate_intensity - 2.0), 0.0, 1.0) * vec3(0.0, 1.0, 0.0) + "
"    clamp(1.0 - abs(quadruplicate_intensity - 3.0), 0.0, 1.0) * vec3(1.0, 1.0, 0.0) + "
"    clamp(1.0 - abs(quadruplicate_intensity - 4.0), 0.0, 1.0) * vec3(1.0, 0.0, 0.0);"
"}"

"vec3 retrieve_vector(vec2 tex_coord) {"
"  return rescale_vector_value("
"    vec3(texture2D(vector_field, tex_coord))"
"  );"
"}"

"vec4 noise(vec2 tex_coord) {"
"  return texture2D(noise_map, tex_coord);"
"}"

"vec2 project_to_uv(vec3 vector) {"
"  return vec2(dot(vector, u_axis), dot(vector, v_axis));"
"}"

"void main(void) {"
"  vec2 tex_coord = gl_TexCoord[0].xy;"

"  vec3 vector = retrieve_vector(tex_coord);"
"  float intensity = 4.0 * clamp(length(vector), 0.0, 1.0);"
"  vec4 field_blend_factor = noise(tex_coord);"

"  const int SamplesCount = 20;"
"  float step_scale = 1.0/textureSize(noise_map, 0).x;"

"  tex_coord += step_scale * project_to_uv(vector);"
"  for (int i = 1; i < SamplesCount; ++i) {"
"    field_blend_factor += noise(tex_coord);"
"    vector = retrieve_vector(tex_coord);"
"    tex_coord += step_scale * project_to_uv(vector);"
"  }"

"  field_blend_factor /= SamplesCount;"
"  field_blend_factor = mix("
"     0.25*field_blend_factor + vec4(0.75),"
"     field_blend_factor,"
"     2.5*min(length(project_to_uv(vector)), 0.4)"
"   );"

"  gl_FragColor = field_blend_factor * vec4(color_map(intensity), 1.0);"
"}";

/*
 * class VectorFieldFlowShader
 */

  VectorFieldFlowShader::VectorFieldFlowShader()
   : gl::ShaderProgramObject(
       gl::VertexShader(vertex_shader_source, sizeof(vertex_shader_source)), 
       gl::FragmentShader(fragment_shader_source, sizeof(fragment_shader_source))
     ), 
     noise_map(get_ARB_handle(), "noise_map"),
     min(get_ARB_handle(), "min_value"),
     max(get_ARB_handle(), "max_value"),
     u_axis(get_ARB_handle(), "u_axis"),
     v_axis(get_ARB_handle(), "v_axis")
  {}

