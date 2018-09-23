#ifndef MARIAN_IMPLICITSCHEME_HPP
#define MARIAN_IMPLICITSCHEME_HPP

#include <FDM/schemes/fdScheme.hpp>
#include <FDM/tridiagonalSolver.hpp>

namespace marian {
  /** \ingroup schemes
   * \brief Class implements implicit schemes
   *
   *
   * When we solve following parabolic PDE:
   * \f[\frac{df(x,t)}{dt} = L f(x,t)\f]
   * where \b L is linear operator, we can use different time discretization scheme, for example:
   * \f[
   \begin{aligned}
   \text{in case of Forward Equation: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j+1}) \Rightarrow f(x_i,t_{j})= (I + (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j+1}) \\
   \text{in case of Backward Equation: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j}) \Rightarrow f(x_i,t_{j+1})= (I - (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j}) 
   \end{aligned}
   \f]
   * For more information see  \cite DuffyFDM \cite ClarkFx \cite MortonMayers . 
   */
  class ImplicitScheme : public DCFDScheme<ImplicitScheme> {
  public:
    /** \brief defualt constructor
     */
    ImplicitScheme(){};

    /** \brief constructor
     */
    ImplicitScheme(SmartPointer<TridiagonalSolver> solver): solver_(solver) {};
    void setSolver(const SmartPointer<TridiagonalSolver>& solver) override {
      solver_ = solver;
    }
    std::vector<double> solve(std::vector<double> f,
			      const std::vector<SmartPointer<BoundaryCondition> >& bcs,
			      const std::vector<double>& time_grid,
			      const TridiagonalOperator& L)  override;
    std::vector<double> solveAndSave(std::vector<double> f,
				     const std::vector<SmartPointer<BoundaryCondition> >& bcs,
				     const std::vector<double>& spatial_grid,
				     const std::vector<double>& time_grid,
				     const TridiagonalOperator& L,
				     const std::string file_name) override;
    std::string info() const override {
      return "implicit";
    }
  private:
    SmartPointer<TridiagonalSolver> solver_; /*!< \brief Sovler used in implicit step*/ 
  };

} // namespace marian

#endif /* MARIAN_IMPLICITSCHEME_HPP */
