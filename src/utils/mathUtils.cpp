#include <utils/mathUtils.hpp>
#include <cmath>

namespace marian {

  /** \ingroup utils
   * \brief Normal CDF
   *
   * Function calculates Cumulative Distribution Function for standard normal distribution.
   *
   *  \f[CDF_{X}(t) = \int^{t}_{-\infty} \frac{1}{\sqrt{2\pi \sigma^{2}}}e^{-\frac{(x-\mu )^{2}}{2\sigma ^{2}}} dx \f]
   *
   * Algorithm is basing on ERF function and its relation to Standard Normal Distribution (see formula 7.1.26 in \cite abramovitz) 
   *
   * \param t argument. 
   * \return Normal CDF for t
   */
  double normalCDF(double t) {
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    int sign = 1;
    if (t < 0)
      sign = -1;
    t = std::fabs(t) / std::sqrt(2.0);

    double x = 1.0/(1.0 + p*t);
    double y = 1.0 - (((((a5*x + a4)*x) + a3)*x + a2)*x + a1)*x*exp(-t*t);

    return 0.5*(1.0 + sign*y);
  }

  /** \ingroup utils
   * \brief linear local interpolation
   *  
   * The idea of linear interpolation of set of point is to approximate value \f$y\f$ at a point \f$x\f$ by a straight line passing through two data points \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ closest to \f$(x,y)\f$. 
   The formula for linear interpolation is:
   * \f[ y =  y_j + \frac{y_{j+1} - y_j}{x_{j+1} - x_j} (t-x_j)\f]
   * 
   * \param x Vector of arguments
   * \param y Vector of values corresponding to arguments
   * \param t Intermediate point
   * \return Value of interpolant for t
   * \pre x,y vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   */
  double interpolation(const std::vector<double>& x,
		       const std::vector<double>& y,
		       double t) {
    std::vector<double>::const_iterator low;
    low = std::lower_bound(x.begin(), x.end(), t);
    unsigned int position = low - x.begin();

    return (y.at(position-1) * ( x.at(position) - t) + y.at(position) * (t
									 - x.at(position-1)) ) / (x.at(position) - x.at(position-1));
  }
  
}  // namespace marian
