#include <FDM/gridBuilders/hsineGridBuilder.hpp>
#include <cmath>

namespace marian {

  /** \brief builds non-uniform grid
   *
   * \param low Lower bound
   * \param upp Upper bound
   * \param concentration Concentration point
   * \param N Number of grid points (N-1 intervals between lower and upper bound) 
   */
  std::vector<double> HSineGridBuilder::buildGrid(double low, double upp, int N, double concentration) const {
    std::vector<double> grid(N);
    double K = (concentration - low) / (upp - low);
    double dx = (1.0 / N) * (std::asinh((1.0 - K) / c_) - std::asinh(-K / c_));
    double mid = std::asinh(-K / c_);
    for (int i = 0; i < N-1; ++i) {
      grid.at(i) = low + (K + c_ * std::sinh(mid + i * dx)) * (upp - low);
    }
    grid.back() = upp;
    return grid;
  }

}  // namespace marian
