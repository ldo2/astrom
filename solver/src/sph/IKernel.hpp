#ifndef __sph_IKernel_HPP__
#define __sph_IKernel_HPP__

#include <geom/Vector3D.hpp>

namespace sph {

  class IKernel {
    protected:
      double smoothing_length;
      double effective_area_factor;
      double space_factor;

    public:
      IKernel(double smoothing_length)
       : smoothing_length(smoothing_length),
         effective_area_factor(1.0) {}

      virtual ~IKernel() {}

      double get_effective_area_factor() const {
        return effective_area_factor;
      }

      double get_smoothing_length() const {
        return smoothing_length;
      }

      double get_space_factor() const {
        return space_factor;
      }

      virtual void set_smoothing_length(double h) = 0;

      virtual double value(const Geom::Vector3D &dr) const = 0;
      virtual Geom::Vector3D gradient(const Geom::Vector3D &dr) const = 0;
      virtual double laplacian(const Geom::Vector3D &dr) const = 0;
  };

}

#endif /* __sph_IKernel_HPP__ */

