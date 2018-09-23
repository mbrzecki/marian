#ifndef MARIAN_HSINEGRIDBUILDER_HPP
#define MARIAN_HSINEGRIDBUILDER_HPP

#include <FDM/gridBuilders/gridBuilder.hpp>

namespace marian {
  /** \ingroup grid
   *
   * \brief Non-uniform grid builder that uses hyperbolic sine function
   * 
   *
   * Class is used to generate non-uniform grid. 
   * The algorithm is basing on method proposed by Tavella & Randall \cite Tavella and Kluge \cite Kluge
   * and briefly described and discussed by Hout & Foulon in \cite Hout.
   *
   * The grid build on interval \f$(x_{min},x_{max})\f$ with a concentration point \f$x_K\f$ and \b c control parameter is constructed in following steps:
   *
   * 1) We define uniform grid 
   * \f[t_i = arcsinh\big(\frac{-k}{c} + i \delta t\big)\f]
   * where \f$k = \frac{x_K-x_{min}}{x_{max} - x_{min}}\f$ and \f$\delta t = \frac{1}{M} \Big(arcsinh\big(\frac{t_{max}-k}{c}\big) - arcsinh\big(\frac{-k}{c}\big)\Big)\f$: 
   *
   * \f[s_i = x_{min} + (k + c \times sinh(t_i))\f]
   *
   * Below plot presents the construction of non-uniform grid for different control parameters
   * @image html nonuniform_param.png
   *
   * Plots below visualize the uniform grid for different values of control parameter and different concentration points.
   * @image html nonuniform.png
   */
  class HSineGridBuilder : public DCGridBuilder<HSineGridBuilder> {
  public:
    /** \brief Constructor
     */
    HSineGridBuilder(double c): c_(c) {}

    std::vector<double> buildGrid(double low, double upp, int N, double concentration) const override;

    /** \brief Destructor
     */
    ~HSineGridBuilder(){};
  private:
    double c_; /*!< \brief Control parameter. Must be greater then 0.0. If the value of parameter is smaller, grid become more concentrated around concentration point. */
  };
}  // namespace marian
#endif /* MARIAN_HSINEGRIDBUILDER_HPP */
