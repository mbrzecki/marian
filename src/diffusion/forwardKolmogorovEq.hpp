#ifndef MARIAN_FORWARDKOLMOGOROVEQ_HPP
#define MARIAN_FORWARDKOLMOGOROVEQ_HPP

#include <utils/smartPointer.hpp>
#include <diffusion/convectionDiffusionProcess.hpp>
#include <FDM/tridiagonalSolver.hpp>
#include <FDM/schemes/fdScheme.hpp>
#include <FDM/boundaryConditions/boundaryCondition.hpp>

namespace marian {

  /** \ingroup diffusion
   * \brief Class implements Forward Kolmogorow Equation
   *
   *
   * Forward Kolmogorow Equation arise in the theory of continuous-time continuous-state Markov processes.
   * Let's assume that the physical system state \b x(t) evolves according to the stochastic differential equation
   * \f[ dx(t)=\mu dt+\sigma dW(t)\f]
   * then probability distribution p(t,x) of \b x is governed by the Kolmogorov forward equation
   * \f[\frac{d p(t,x)}{dt} = \Big(\frac{1}{2}\sigma^2 \frac{\partial^2 }{\partial x^2} - \mu  \frac{\partial }{\partial x}\Big) p(t,x)  \f]
   * More information see \cite Huang \cite kineticsPhysics
   *
   * This class is used to construct the PDE basing on diffusion process and solve it using finite difference method.
   */   
  class ForwardKolmogorowEquation {
  public:
    /** \brief constructor
     */
    ForwardKolmogorowEquation(ConvectionDiffusion process):
      process_(process) {}

    std::vector<double> solve(SmartPointer<FDScheme> scheme,
			      std::vector<double> init,
			      std::vector<SmartPointer<BoundaryCondition> > bcs,
			      std::vector<double> spatial_grid,
			      std::vector<double> time_grid);
    
    std::vector<double> solveAndSave(SmartPointer<FDScheme> scheme,
				     std::vector<double> init,
				     std::vector<SmartPointer<BoundaryCondition> > bcs,
				     std::vector<double> spatial_grid,
				     std::vector<double> time_grid,
				     std::string file_name);

    TridiagonalOperator getOperator(const std::vector<double>& sgrid);
  private:
    ConvectionDiffusion process_; /*!< \brief Stochastic process  */ 
  };
  
}  // namespace marian

#endif /* MARIAN_FORWARDKOLMOGOROVEQ_HPP */
