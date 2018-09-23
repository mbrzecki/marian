#ifndef MARIAN_SPOTRELATEDRANGE_HPP
#define MARIAN_SPOTRELATEDRANGE_HPP

#include <financial/gridRange/rangeSetup.hpp>

namespace marian {

  /** \ingroup gridrange
   * \brief Approximate the boundary condition basing on asset spot price
   *
   * For some options the boundary conditions need to be set in the infinity. When we use numerical routines we must approximate this conditions with finite values.
   * Using this class the spot range is set relatively to the spot price. When object of this class is constructed, the two multipliers \a low and \a upp are used.
   * The lower boundary is approximated \f$\lim_{S \to 0} V(lS_t,t) =  a \Rightarrow \lim_{x \to low*S} V(S_t,t) = a.\f$.
   * The upper boundary is approximated \f$\lim_{S \to \infty} V(lS_t,t) =  a \Rightarrow \lim_{x \to upp*S} V(S_t,t) = a.\f$.
   */ 

  class SpotRelatedRange : public DCRangeSetup<SpotRelatedRange> {
  public:
  /**\brief Defualt constructor
   * 
   * Sets low to 0.5 and up to 2.0 by default
   */
    SpotRelatedRange():
      low_(0.5), up_(2.0) {}
	  
	  /** \brief Constructor
	  *
	  * \param low Multiplier for lower boundary 
	  * \param up Multiplier for upper boundary
	  */
    SpotRelatedRange(double low, double up):
      low_(low),up_(up) {}
    
	/** \brief returns upper boundary value
	*
	* \returns Spot multiplied by upper boundary multiplier
	*/
    double getUpperBound(Market mkt,SmartPointer<Option>) const override {
      return mkt.spot * up_;
    }
  
	/** \brief returns lower boundary value
	*
	* \returns Spot multiplied by lower boundary multiplier
	*/  
    double getLowerBound(Market mkt,SmartPointer<Option>) const override {
      return mkt.spot * low_;
    }
	
	/** \brief Destructor
	*/
    virtual ~SpotRelatedRange(){};
  private:
    double low_;  /*!< \brief Multiplier for lower boundary */
    double up_;   /*!< \brief Multiplier for upper boundary */
  };
  
}  // namespace marian

#endif /* MARIAN_SPOTRELATEDRANGE_HPP */
