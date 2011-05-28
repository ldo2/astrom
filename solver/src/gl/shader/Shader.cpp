#include "Shader.hpp"

#include <iostream>
#include <fstream>

namespace gl {

/*
 * class Shader
 */

  Shader::Shader() {}
  Shader::Shader(GLhandleARB shader)
   : shader(shader) {}

  GLhandleARB Shader::get_ARB_handle() const {
    return shader;
  }

  void Shader::load_shader_source(const char *filename, 
                                   char *&source, int &source_size) {
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open()) {
      source_size = (int) file.tellg();

      source = new char [source_size];

      file.seekg(0, std::ios::beg);
      file.read (source, source_size);
      file.close();
    } else {
      source = NULL;
      source_size = 0;

      std::cerr << "Unable to read shader source \"" << filename 
                << "\"" << std::endl;
    }
  }

}

