#ifndef MARIAN_BOUNDARYCONDITION_HPP
#define MARIAN_BOUNDARYCONDITION_HPP

#include <vector>
#include <FDM/tridiagonalOperator.hpp>

namespace marian {
  /** \ingroup boundary
   * \brief Types of boundary conditions
   */
  enum class BCSide {LOW, ///< Condition set on lower boundary of FDM grid
		     UPP, ///< Condition set on upper boundary of FDM grid
		     FREE ///< Free-boundary condition
  };

  /** \ingroup boundary
   * \brief Interface for boundary conditions
   *
   *
   * Class implements the boundary condition interface. It modifies tridiagonal operator and solution 
   * to ensure proper value of solution on boundaries.
   */
  class BoundaryCondition {    
  public:
    /** \brief Constructor
     */
    BoundaryCondition(){};

    /** \brief Modification of tridiagonal matrix before explicit step
     *
	 *
	 * Modification of tridiagonal matrix before explicit step
     * \param L Linear operator of PDE 
     */
    virtual void beforeExplicitStep(TridiagonalOperator& L) = 0;

    /** \brief Modification of solution of after explicit step
     *
	 *
	 * Modification of solution of after explicit step
     * \param f Solution after calculating derivative 
     * \param t Actual time, passing time value enables using time-dependent boundary conditions 
     */
    virtual void afterExplicitStep(std::vector<double>& f, double t) = 0;

    /** \brief Modification of tridiagonal matrix before equation f'=Lf is solved
     *
	 *
	 * Modification of tridiagonal matrix before equation f'=Lf is solved
     * \param L Linear operator of PDE 
     * \param f Function before solving 
     * \param t Actual time, passing time value enables using time-dependent boundary conditions 
     */
    virtual void beforeImplicitStep(TridiagonalOperator& L,
				    std::vector<double>& f,
				    double t) = 0;

    /** \brief Modification of solution of after solving equation f'=Lf is solved
     *
	 *
	 * Modification of solution of after solving equation f'=Lf is solved
     * \param f Solution after calculating derivative
     * \param t Actual time, passing time value enables using time-dependent boundary conditions 
     */
    virtual void afterImplicitStep(std::vector<double>& f,double t) = 0;

    /** \brief Returns the type of boundary condition
	*
	* Returns the type of boundary condition
     */
    virtual std::string info() const = 0;
    
    /** \brief Virtual copy constructor
     */
    virtual BoundaryCondition* clone() const = 0;

    /** \brief Destructor
     */
    virtual ~BoundaryCondition(){};

  private:

  };

  /** \ingroup boundary
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
  class DCBoundaryCondition : public BoundaryCondition {
  public:
    /** \brief Virtual copy constructor
     */
    virtual BoundaryCondition* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
} // namespace marian


#endif /* MARIAN_BOUNDARYCONDITION_HPP */
