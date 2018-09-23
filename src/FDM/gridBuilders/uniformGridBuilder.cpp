#include <FDM/gridBuilders/uniformGridBuilder.hpp>

#include <iostream>

namespace marian {

  /** \brief builds uniform grid
   *
   * \param low Lower bound
   * \param upp Upper bound
   * \param N Number of grid points (N-1 intervals between lower and upper bound) 
   */
  std::vector<double> UniformGridBuilder::buildGrid(double low, double upp, int N, double ) const {
    std::vector<double> grid(N);
    double spacing  = (upp - low) / (N-1);
    grid.at(0) = low;
    for (int i = 0; i < N; i++ ) {
      grid[i+1] = (grid.at(i) + spacing);
    }
    return grid;
  }

}  // namespace marian
