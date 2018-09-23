#ifndef MARIAN_RANGESETUP_HPP
#define MARIAN_RANGESETUP_HPP

#include <financial/options/option.hpp>
#include <financial/market.hpp>

namespace marian {

  /** \ingroup gridrange
   * \brief Class implements algorithm to approximate indefinite boundaries 
   *
   * For some options the boundary conditions need to be set in the infinity. When we use numerical routines we must approximate this conditions with finite values. 
   * Because we can achieve this in difference ways, we introduce the common interface for range setting algorithm. 
   * Using the getUpperBound and getLowerBound methods we receive the end points of interval.
   *
   * For example: In case of European option we have the boundary conditions: \f$\lim_{x \to -\infty} V(ln S_t,t) = 0.\f$ and  \f$\lim_{x \to \infty} V(ln S_t,t) = S.\f$
   * We can approximate this boundaries assuming that the same condition can be applied for finite values of x, like \b 0.2 \b S and \b 3.0 \b S.
   * The method of approximating the boundaries is delegated to derived classes. 
   */ 
  class RangeSetup {
  public:
   /** \brief Returns the upper boundary for a given market and option. 
   */
    virtual double getUpperBound(Market ,SmartPointer<Option>) const = 0;
	
   /** \brief Returns the lower boundary for a given market and option. 
   */
    virtual double getLowerBound(Market ,SmartPointer<Option>) const = 0;
	
   /** \brief Virtual copy constructor 
   */
    virtual RangeSetup* clone() const = 0;
	
	/** \brief Destructor
	*/
    virtual ~RangeSetup(){}

  };
  
    /** \ingroup gridrange 
   *
   * \brief Deeply copyable RangeSetup
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
  class DCRangeSetup : public RangeSetup {
  public:
    /** \brief Virtual copy constructor
     */
    virtual RangeSetup* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
}  // namespace marian

#endif /* MARIAN_RANGESETUP_HPP */
