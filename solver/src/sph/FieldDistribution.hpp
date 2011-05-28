#ifndef __sph_FieldDistribution_HPP__
#define __sph_FieldDistribution_HPP__

#include <geom/Vector3D.hpp>

namespace sph {

  template <typename FieldType>
  class IFieldDistribution {
    public:
      virtual ~IFieldDistribution() {}
      virtual FieldType value(const Geom::Vector3D &point) = 0;
  };

  template <typename FieldType, typename Callable>
  class FieldDistribution : public IFieldDistribution<FieldType> {
    public:
      Callable function;

      FieldDistribution(const Callable &function)
       : function(function) {}

      virtual FieldType value(const Geom::Vector3D &point) {
        return function(point);
      }
  };

}

#endif /* __sph_FieldDistribution_HPP__ */

