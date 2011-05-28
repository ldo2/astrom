#include "Quartic.hpp"

namespace sph {
  namespace Kernel {

    /*
     * class Quartic 
     */
        Quartic::Quartic(double smoothing_length)
         : IKernel(smoothing_length) {
          set_smoothing_length(smoothing_length);
        }

        Quartic::~Quartic() {}


        void Quartic::set_smoothing_length(double h) {
          smoothing_length = h;
          space_factor = 2.08890862808113/(h*h*h); // 105/(16*PI*h**3)
        }

        double Quartic::value(const Geom::Vector3D &dr) const {
          double R = length(dr)/smoothing_length;
          
          if (R <= 1.0) {
            double one_minus_R = 1.0 - R;
            return space_factor * (1.0 + 3.0*R) * 
              one_minus_R * one_minus_R * one_minus_R;
          }

          return 0.0;
        }

        Geom::Vector3D Quartic::gradient(const Geom::Vector3D &dr) const {
          double R = length(dr)/smoothing_length;
          
          if (R <= 1.0) {
            double one_minus_R = 1.0 - R;

            return (-12.0 * space_factor * R * one_minus_R * one_minus_R / 
                     smoothing_length) * normalize(dr);
            //return (-12.0 * space_factor * one_minus_R * one_minus_R / 
            //         (smoothing_length * smoothing_length)) * dr;
          }

          return Geom::Vector3D(0.0, 0.0, 0.0);
        }

        double Quartic::laplacian(const Geom::Vector3D &dr) const  {
          double R = length(dr)/smoothing_length;
          
          if (R <= 1.0) {
            return space_factor * (1 - R) * (36*R - 12) / 
                    (smoothing_length * smoothing_length);
          }

          return 0.0;
        }
    }

}

