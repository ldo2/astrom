#ifndef __sph_Kernel_Quartic_HPP__
#define __sph_Kernel_Quartic_HPP__

#include <sph/IKernel.hpp>

namespace sph {
  namespace Kernel {

    class Quartic : public IKernel {
      public: 
        Quartic(double smoothing_length);

        virtual ~Quartic();

        virtual void set_smoothing_length(double h);

        virtual double value(const Geom::Vector3D &dr) const;
        virtual Geom::Vector3D gradient(const Geom::Vector3D &dr) const;
        virtual double laplacian(const Geom::Vector3D &dr) const;
    };

  }
}

#endif /* __sph_Kernel_Quartic_HPP__ */

