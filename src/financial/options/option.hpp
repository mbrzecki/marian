#ifndef MARIAN_OPTION_HPP
#define MARIAN_OPTION_HPP

#include <utils/SmartPointer.hpp>
#include <financial/options/pricerAbstractFactory.hpp>

namespace marian {

  /** \brief Interface for financial derivatives
   * \ingroup option
   *
   * Class implements abstraction of financial option. 
   */
  class Option {
  public:
    Option(){};
	/** \brief Method allocating Abstract Factory
	*
	* Method is used by FDM pricer to generate settings of finite difference algorithm.  Compare marian::AbstractPricerFactory
	*/
    virtual SmartPointer<AbstractPricerFactory> allocateFactory() const = 0;
	
	/** \brief Destructor
	*/
    virtual ~Option() {};
	
		
	/** \brief Returns maturity of option
	*/
    virtual double getT() const = 0;
	
	/** \brief Virtual copy constructor
	*/
    virtual Option* clone() const = 0;
  };

   /** \ingroup option 
   *
   * \brief Deeply copyable Option
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
  class DCOption : public Option {
  public:
    /** \brief Virtual copy constructor
     */
    virtual Option* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
}  // namespace marian


#endif /* MARIAN_OPTION_HPP */
