#ifndef MARIAN_UNIFORMGRIDBUILDER_HPP
#define MARIAN_UNIFORMGRIDBUILDER_HPP

#include <FDM/gridBuilders/gridBuilder.hpp>

namespace marian {

  /** \brief Uniform grid builder
   * \ingroup grid
   *
   * Class is used to generate uniform grid, a grid with constant distance between points.
   *  
   * The grid is defined as:
   * \f[x_0 = x_{low} \f]
   * \f[ x_{i+1} = x_i + i \delta_x \f]
   * for \f$ i=1,\dots,N\f$, where \f$\delta_x = \frac{x_{upp} - x_{low}}{N}\f$
   *
   * Below the code generating 2d grid and its visualization.
   \code{.cpp}
   UniformGridBuilder ugb;
   auto grid1 = ugb.buildGrid(0.0, 10.0, 25);
   auto grid2 = ugb.buildGrid(0.0,  5.0, 20);
   for (auto x : grid1) {
     for (auto y : grid2) {
       std::cout << x << ";" << y << std::endl;
     }
   }
   \endcode
   *
   * @image html uniform.png
   */
  class UniformGridBuilder : public DCGridBuilder<UniformGridBuilder> {
  public:
    /** \brief Constructor
     */
    UniformGridBuilder() {}

    std::vector<double> buildGrid(double low, double upp, int N, double concentration = 0.0) const override;

    /** \brief Destructor
     */
    ~UniformGridBuilder(){};
  };
  
}  // namespace marian

#endif /* MARIAN_UNIFORMGRIDBUILDER_HPP */
