#ifndef MARIAN_EXPLICITSCHEME_HPP
#define MARIAN_EXPLICITSCHEME_HPP

#include <FDM/schemes/fdScheme.hpp>

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
   \text{in case of Forward Equation: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j+1}) \Rightarrow f(x_i,t_{j+1})= (I + (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j}) \\
   \text{in case of Backward Equation: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j}) \Rightarrow f(x_i,t_{j+1})= (I - (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j+1}) 
   \end{aligned}
   \f]
   * For more information see  \cite DuffyFDM \cite ClarkFx \cite MortonMayers . 
   */
  class ExplicitScheme : public DCFDScheme<ExplicitScheme> {
  public:
    ExplicitScheme(){};
    /** \brief Provides a solver used in implicit scheme.
     *
     *
     * For explicit method this method is empty.
     */
    void setSolver(const SmartPointer<TridiagonalSolver>&) override {
    }
	
    /** \brief Solves PDE defined by provided linear operator \b L and initial and boundary conditions
     * 
     * \param f Initial condition 
     * \param bcs Boundary conditions
     * \param time_grid Time grid used in
     * \param L Linear operator defining PDE
     * \returns Solution in form of std::vector
     */
    std::vector<double> solve(std::vector<double> f,
			      const std::vector<SmartPointer<BoundaryCondition> >& bcs,
			      const std::vector<double>& time_grid,
			      const TridiagonalOperator& L) override;
				  
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
    std::vector<double> solveAndSave(std::vector<double> f,
				     const std::vector<SmartPointer<BoundaryCondition> >& bcs,
				     const std::vector<double>& spatial_grid,
				     const std::vector<double>& time_grid,
				     const TridiagonalOperator& L,
				     const std::string file_name) override;
					 
    /** \brief  Returns scheme name
     */
    std::string info() const override {
      return "explicit";
    }
  };
} // namespace marian


#endif /* MARIAN_EXPLICITSCHEME_HPP */
