#ifndef MARIAN_FDSCHEME_HPP
#define MARIAN_FDSCHEME_HPP

#include <vector>
#include <utils/smartPointer.hpp>
#include <FDM/tridiagonalSolver.hpp>
#include <FDM/boundaryConditions/boundaryCondition.hpp>

namespace marian {

/** \ingroup schemes
   * \brief Class implements interface for differential schemes
   *
   * When we solve following parabolic PDE:
   * \f[\frac{df(x,t)}{dt} = L f(x,t)\f]
   * where \b L is linear operator, we can use different time discretization scheme, for example in case of Forward Kolmogorov Equation:
   * \f[
	    \begin{aligned}
		  \text{in case of explicit scheme: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j}) \Rightarrow f(x_i,t_{j+1})= (I + (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j}) \\
		  \text{in case of explicit scheme: }\frac{f(x_i,t_{j+1})-f(x_i,t_{j})}{t_{j+1}-t_{j}} & = \hat{L} f(x_i,t_{j+1}) \Rightarrow f(x_i,t_{j})= (I - (t_{j+1}-t_{j})\hat{L}) f(x_i,t_{j+1}) 
		\end{aligned}
   \f]

   * The difference between implicit scheme and explicit scheme lies in number of unknown values of on the time level. 
   * In explicit scheme we have three known values (in case of forward equation): \f$f(x_{i-1},t_{i}),f(x_{i},t_{i}),f(x_{i+1},t_{i})\f$ 
   * and one unknown \f$f(x_{i},t_{i+1})\f$. This is why we can explicitly find the unknown values. 
   * In case of implicit we have three unknown values and one known for each time point. 
   * Solving this kind of system requires finding global solution. 
   * Because of that implicit scheme is numerically more demanding, but it is unconditionally stable in contrast to explicit scheme.
   * For more information see  \cite DuffyFDM \cite ClarkFx \cite MortonMayers . 
   */
  class FDScheme {
  public:
  
    /** \brief Provides a solver used in implicit scheme
	*/
    virtual void setSolver(const SmartPointer<TridiagonalSolver>& solver) = 0; 
	/** \brief Solves PDE defined by provided linear operator \b L and initial and boundary conditions
	* 
	* \param f Initial condition 
	* \param bcs Boundary conditions
	* \param time_grid Time grid used in
	* \param L Linear operator defining PDE
	* \returns Solution in form of std::vector
	*/
    virtual std::vector<double> solve(std::vector<double> f,
				      const std::vector<SmartPointer<BoundaryCondition> >& bcs,
				      const std::vector<double>& time_grid,
				      const TridiagonalOperator& L) = 0;
					  
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
    virtual std::vector<double>  solveAndSave(std::vector<double> f,
					      const std::vector<SmartPointer<BoundaryCondition> >& bcs,
					      const std::vector<double>& spatial_grid,
					      const std::vector<double>& time_grid,
					      const TridiagonalOperator& L,
					      const std::string file_name) = 0;
						  
	/** \brief  Returns scheme name
	*/
    virtual std::string info() const = 0;
	
	/** \brief  Virtual copy constructor
	*/
    virtual FDScheme* clone() const = 0;
	
	/** \brief  Deconstructor
	*/
    virtual ~FDScheme(){};
  };

  /** \ingroup schemes
   *
   * \brief Deeply copyable BoundaryCondition
   *
   * Class implements Curiously Recurring Template Pattern (see [Wikipedia site](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)).
   *
   * When using polymorphism, one sometimes needs to create copies of objects by the base class pointer. 
   * A commonly used idiom for this is adding a virtual clone function that is defined in every derived class. 
   * The CRTP can be used to avoid having to duplicate that function or other similar functions in every derived class.
   *
   * For more information about virtual copy constructor see \cite joshi
   */
  template<typename T>
  class DCFDScheme : public FDScheme {
  public:
    /** \brief Virtual copy constructor
     */
    virtual FDScheme* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
} // namespace marian


#endif /* MARIAN_FDSCHEME_HPP */
