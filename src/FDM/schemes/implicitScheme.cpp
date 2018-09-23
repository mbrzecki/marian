#include <FDM/schemes/implicitScheme.hpp>
#include <utils/DataFrame.hpp>

namespace marian {
  /** \brief Solves PDE defined by provided linear operator \b L and initial and boundary conditions
   * 
   * \param f Initial condition 
   * \param bcs Boundary conditions
   * \param time_grid Time grid used in
   * \param L Linear operator defining PDE
   * \returns Solution in form of std::vector
   */
  std::vector<double> ImplicitScheme::solve(std::vector<double> f,
					    const std::vector<SmartPointer<BoundaryCondition> >& bcs,
					    const std::vector<double>& time_grid,
					    const TridiagonalOperator& L) {
    auto I = TridiagonalOperator::I(L.size());
    for (unsigned int i = 0; i < time_grid.size()-1; i++) {
      auto dt = time_grid.at(i+1) - time_grid.at(i);
      auto diff_operator = I - dt * L;
      for (auto bc : bcs) {
	bc->beforeImplicitStep(diff_operator, f,  time_grid.at(i));
      }
      f = solver_->solve(diff_operator, f);
      for (auto bc : bcs) {
	bc->afterImplicitStep(f, time_grid.at(i));
      }
    }
    return f;
  }

  /** \brief Solves PDE defined by provided linear operator \b L and initial and boundary conditions. Additionally saves solution to CSV file
   * 
   * \param f Initial condition 
   * \param bcs Boundary conditions
   * \param spatial_grid Spatial grid corresponding to initial conditions (used only to save the solution to CSV file)
   * \param time_grid Time grid used for time dimension of FDM
   * \param L Linear operator defining PDE
   * \param file_name Name of CSV file
   * \returns Solution in form of std::vector
   */
  std::vector<double> ImplicitScheme::solveAndSave(std::vector<double> f,
						   const std::vector<SmartPointer<BoundaryCondition> >& bcs,
						   const std::vector<double>& spatial_grid,
						   const std::vector<double>& time_grid,
						   const TridiagonalOperator& L,
						   const std::string file_name) {
    DataFrame df;
    for (unsigned int i = 0; i < f.size(); i++) {
      DataEntryClerk input;
      input.add("T", time_grid.front());
      input.add("S", spatial_grid.at(i));
      input.add("f", f.at(i));
      df.append(input);
    }
    
    auto I = TridiagonalOperator::I(L.size());
    for (unsigned int i = 0; i < time_grid.size()-1; i++) {
      auto dt = time_grid.at(i+1) - time_grid.at(i);
      auto diff_operator = I - dt * L;
      for (auto bc : bcs) {
	bc->beforeImplicitStep(diff_operator, f, time_grid.at(i));
      }
      f = solver_->solve(diff_operator, f);
      for (auto bc : bcs) {
	bc->afterImplicitStep(f, time_grid.at(i));
      }
      for (unsigned int j = 0; j < f.size(); j++) {
	DataEntryClerk input;
	input.add("T", time_grid.at(i+1));
	input.add("S", spatial_grid.at(j));
	input.add("f", f.at(j));
	df.append(input);
      }
    }
    df.printToCsv(file_name,';');
    return f;
  }
}  // namespace fdm
