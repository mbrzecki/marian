#ifndef MARIAN_MATHUTILS_HPP
#define MARIAN_MATHUTILS_HPP

#include <vector>
#include <limits>
namespace marian {

  #define INFTY std::numeric_limits<double>::infinity()
  
  double normalCDF(double t);
  
  double interpolation(const std::vector<double>& x,
		       const std::vector<double>& y,
		       double t);
  
  
} // namespace  marian


#endif /* MARAIN_MATHUTILS_HPP */
