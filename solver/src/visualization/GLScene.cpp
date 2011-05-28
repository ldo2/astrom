#include "GLScene.hpp"

#include <algorithm>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glx.h>

#include <visualization/particle_visualizators/BoundingBoxVisualizator.hpp>

/*
 * class GLScene 
 */

  GLScene::GLScene(IParticlesVisualizationAdaptor *particles) 
   : is_initialized(false), particles(particles) {} 
   
  GLScene::~GLScene() {}

  void GLScene::require_initialization() {
    if (!is_initialized) {
      initialize();
      is_initialized = true;
    }
  }

  void GLScene::camera_centering(DisplayInfo &info) {
    BoundingBoxVisualizator visualizator;

    particles->render_each_with(visualizator);
    Geom::Vector3D range = visualizator.bounding_box.max - 
                           visualizator.bounding_box.min,
                  center = 0.5*(visualizator.bounding_box.max + 
                                visualizator.bounding_box.min);
    // camera distance = scene radius / sin(angle of view / 2)
    double distance = 0.5 * length(range) / 0.38268343236509; 

    info.camera->eye = center - distance * info.camera->view;
  }

  void GLScene::set_projection_matrix(DisplayInfo &info) {
    BoundingBoxVisualizator visualizator;

    particles->render_each_with(visualizator);

    Geom::Vector3D min = visualizator.bounding_box.min,
                   max = visualizator.bounding_box.max;
    
    double distances[] = {
      dot(Geom::Vector3D(min.x, min.y, min.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(max.x, min.y, min.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(min.x, max.y, min.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(min.x, min.y, max.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(min.x, max.y, max.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(max.x, min.y, max.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(max.x, max.y, min.z) - info.camera->eye, info.camera->view),
      dot(Geom::Vector3D(max.x, max.y, max.z) - info.camera->eye, info.camera->view)
    };

    const double gl_min = 1.0, gl_max = 1e+6, gl_range = 1.0;
    double min_distance = std::max(gl_min, 
      *std::min_element(distances, distances + sizeof(distances))
    );
    double max_distance = std::max(gl_min + gl_range, std::min(gl_max, 
      *std::max_element(distances, distances + sizeof(distances))
    ));

    GLfloat aspect_ratio = (GLfloat) info.screen.height / info.screen.width;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0/aspect_ratio, min_distance, max_distance);
  }

