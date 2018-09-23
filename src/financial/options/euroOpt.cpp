#include <financial/options/euroOpt.hpp>
#include <financial/options/euroOptFactory.hpp>

namespace marian {

  /** \brief Returns strike
   * \return Option's strike
   */
  double EuroOpt::getK() const {
    return strike_;
  }

  /** \brief Returns maturity
   * \return Option's maturity
   */
  double EuroOpt::getT() const {
    return T_;
  }

  /** \brief Returns option's type
   * \return Option's type
   */
  OptionType EuroOpt::getType() const {
    return type_;
  }
  /** \brief Calculates payoff
   *
   * Pay-off:
   * * In case of Call
   * \f[max(spot_{T}-K,0)\f]
   * * In case of Put
   * \f[max(K-spot_{T},0)\f]
   * 
   * \param spot Underlying price
   * \return Returns payoff
   */
   double EuroOpt::payoff(const double spot) const {
    double payoff = 0.0;
    switch (type_) {
    case OptionType::CALL:
      payoff = strike_ > spot ? strike_ - spot : 0.0;
      break;
    case OptionType::PUT:
      payoff  = strike_ < spot ? spot - strike_ : 0.0;
      break;     
    }
    return payoff;
  }

  	/** \brief Method allocating Abstract Factory
	*
	* Method is used by FDM pricer to generate settings of finite difference algorithm. This method returns marian::EuroOptFactory .
	*/
  SmartPointer<AbstractPricerFactory> EuroOpt::allocateFactory() const {
    return EuroOptFactory(*this);
  }
  
  std::ostream& operator<<(std::ostream& s, EuroOpt& o) {
    std::string t;
    switch(o.type_) {
    case OptionType::CALL: t = "Call";break;
    case OptionType::PUT: t = "Put";break;
    }
    s << "Strike: " << o.strike_ << " Tenor " << o.T_ << " Type " << t << "\n"; 
    return s;
  }
}  // namespace marian
