#include <diffusion/backwardKolmogorovEq.hpp>
#include <algorithm>
#include <cmath>

namespace marian {

  /** \brief Solves backward equation
   *
   * \param scheme Differential scheme
   * \param init Initial value
   * \param bcs Boundary conditions
   * \param spatial_grid Spatial grid used to discretize the system
   * \param time_grid Time grid used to discretize the system
   * \returns Solution in form of std::vector
   */
  std::vector<double> BackwardKolmogorowEquation::solve(SmartPointer<FDScheme> scheme,
							std::vector<double> init,
							std::vector<SmartPointer<BoundaryCondition> > bcs,
							std::vector<double> spatial_grid,
							std::vector<double> time_grid) {
    auto L = getOperator(spatial_grid);
    std::reverse(time_grid.begin(), time_grid.end());
    return scheme->solve(init, bcs, time_grid, L);
  }
  /** \brief Solves equation and save it to CSV file 
   *
   * \param scheme Differential scheme
   * \param init Initial value
   * \param bcs Boundary conditions
   * \param spatial_grid Spatial grid used to discretize the system
   * \param time_grid Time grid used to discretize the system
   * \param file_name CSV file name
   * \returns Solution in form of std::vector
   */ 
  std::vector<double> BackwardKolmogorowEquation::solveAndSave(SmartPointer<FDScheme> scheme,
							       std::vector<double> init,
							       std::vector<SmartPointer<BoundaryCondition> > bcs,
							       std::vector<double> spatial_grid,
							       std::vector<double> time_grid,
							       std::string file_name) {
    auto L = getOperator(spatial_grid);
    std::reverse(time_grid.begin(), time_grid.end());
    return scheme->solveAndSave(init, bcs, spatial_grid, time_grid, L, file_name);
  }

  /** \brief Constructs the discretized linear operator for Backward Kolmogorow Equation in form of Tridiagonal operator
   *
   *
   * The operator is given as:
   * \f[\hat{L} = -\frac{1}{2}\sigma^2 \frac{\partial^2 }{\partial x^2} - \mu \frac{\partial }{\partial x}  \f]
   */
  TridiagonalOperator BackwardKolmogorowEquation::getOperator(const std::vector<double>& sgrid) {
    auto d0 = TridiagonalOperator::I(sgrid);
    auto d1 = TridiagonalOperator::DZero(sgrid);
    auto d2 = TridiagonalOperator::DPlusMinus(sgrid);
    return -0.5*std::pow(process_.diffusion, 2)*d2
      - process_.convection*d1
      + process_.decay * d0;
  }
}  // namespace marian
