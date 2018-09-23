#ifndef MARIAN_CRANKNICOLSONSCHEME_HPP
#define MARIAN_CRANKNICOLSONSCHEME_HPP

#include <FDM/schemes/fdScheme.hpp>
#include <FDM/tridiagonalSolver.hpp>

namespace marian {
  /** \ingroup schemes
   * \brief Class implements Crank-Nicolson Scheme
   *
   * 
   * Crank-Nicolson is a combination of the implicit method and the explicit Euler method. In each time step, two steps: explicit and implicit are performed.
   * The Crank-Nicolson scheme is unconditionally stable and have better convergence that implicit schemes and explicit schemes alone.
   */
  class CrankNicolsonScheme : public DCFDScheme<CrankNicolsonScheme> {
  public:
    /** \brief Constructor
     */
    CrankNicolsonScheme(){};
    /** \brief Provides a solver used in implicit scheme
     */
    CrankNicolsonScheme(SmartPointer<TridiagonalSolver> solver): solver_(solver) {};
	
    void setSolver(const SmartPointer<TridiagonalSolver>& solver) override {
      solver_ = solver;
    }
    std::vector<double> solve(std::vector<double> f,
			      const std::vector<SmartPointer<BoundaryCondition> >& bcs,
			      const std::vector<double>& time_grid,
			      const TridiagonalOperator& L) override;
    std::vector<double> solveAndSave(std::vector<double> f,
				     const std::vector<SmartPointer<BoundaryCondition> >& bcs,
				     const std::vector<double>& spatial_grid,
				     const std::vector<double>& time_grid,
				     const TridiagonalOperator& L,
				     const std::string file_name) override;
    std::string info() const override {
      return "CrankNicolson";
    }
  private:
    SmartPointer<TridiagonalSolver> solver_;   /*!< \brief Sovler used in implicit step*/   
  };
  
} // namespace marian


#endif /* MARIAN_CRANKNICOLSONSCHEME_HPP */
