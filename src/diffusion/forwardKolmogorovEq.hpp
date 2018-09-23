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
   * \f[\frac{d p(t,x)}{dt} = \Big(\frac{1}{2}\sigma^2 \frac{\partial^2 }{\partial x^2} - \mu  \frac{\partial^2 }{\partial x}\Big) p(t,x)  \f]
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

    /** \brief Solves
     *
     * \param scheme Differential scheme
     * \param init Initial value
     * \param bcs Boundary conditions
     * \param spatial_grid Spatial grid used to discretize the system
     * \param time_grid Time grid used to discretize the system
     * \returns Solution in form of std::vector
     */
    std::vector<double> solve(SmartPointer<FDScheme> scheme,
			      std::vector<double> init,
			      std::vector<SmartPointer<BoundaryCondition> > bcs,
			      std::vector<double> spatial_grid,
			      std::vector<double> time_grid);
    
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
    std::vector<double> solveAndSave(SmartPointer<FDScheme> scheme,
				     std::vector<double> init,
				     std::vector<SmartPointer<BoundaryCondition> > bcs,
				     std::vector<double> spatial_grid,
				     std::vector<double> time_grid,
				     std::string file_name);

    /** \brief Constructs the discretized linear operator for Forward Kolmogorow Equation in form of Tridiagonal operator
     *
     *
     * The operator is given as:
     * \f[\hat{L} = \frac{1}{2}\sigma^2 \frac{\partial^2 }{\partial x^2} - \mu (t,x) \frac{\partial^2 }{\partial x}  \f]
     */
    TridiagonalOperator getOperator(const std::vector<double>& sgrid);
  private:
    ConvectionDiffusion process_; /*!< \brief Stochastic process  */ 
  };
  
}  // namespace marian

#endif /* MARIAN_FORWARDKOLMOGOROVEQ_HPP */
