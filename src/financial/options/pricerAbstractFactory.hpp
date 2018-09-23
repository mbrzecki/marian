#ifndef MARIAN_PRICERABSTRACTFACTORY_HPP
#define MARIAN_PRICERABSTRACTFACTORY_HPP

#include <FDM/boundaryConditions/boundaryCondition.hpp>
#include <financial/market.hpp>
#include <utils/SmartPointer.hpp>

namespace marian {

  /** \brief Class implements the interface for Abstract Factory 
   * \ingroup option
   *
   *
   * Class implements the interface for Abstract Factory (see \cite GoF).
   * When we price an option using FDM method we need to transform financial contract terms into boundary and initial conditions, discrete grid etc. 
   * This tasks are delegated to separate classes: factories with common interface defined here. 
   */
  class AbstractPricerFactory {
  public:
  /** \brief Default constructor
  */
    AbstractPricerFactory(){};
    /** \brief Returns boundary conditions
	*
	* \param mkt Market data needed to construct boundary conditions
	* \param low Lower boundary
	* \param upp Upper boundary
	* \returns Vector of boundary conditions
	*/
	virtual std::vector<SmartPointer<BoundaryCondition> > getBoundarySpotConditions(Market mkt ,double low,double upp) = 0;
		
    /** \brief Calculates initial condition for a given vector of spots
	*/
    virtual std::vector<double> initialCondition(const std::vector<double>&) = 0;
	
	/** \brief Returns lower boundary level 
	*/
    virtual double lowerSpotLmt() = 0;
	
	/** \brief Returns upper boundary level 
	*/
    virtual double upperSpotLmt() = 0;
	
	/** \brief Returns concentration point used by non-uniform grid builders 
	*/
    virtual double getConcentrationPoint() = 0;
	
	/** \brief Virtual copy construct
	*/
    virtual AbstractPricerFactory* clone() const = 0;
	
	/** \brief destructor
	*/
    virtual ~AbstractPricerFactory(){};
  };

  
  /** \ingroup option 
   *
   * \brief Deeply copyable AbstractPricerFactory
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
  class DCAbstractPricerFactory : public AbstractPricerFactory {
  public:
    /** \brief Virtual copy constructor
     */
    virtual AbstractPricerFactory* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
}  // namespace marian

#endif /* MARIAN_PRICERABSTRACTFACTORY_HPP */
