#include <financial/analyticPricer.hpp>
#include <cmath>

namespace marian {

  
  /** \ingroup fin
   * \brief Calculates price of European option using BS model
   *
   * Orion is priced using following formula:
   *
   * \f[ \begin{aligned} Price & = i_{cp} (S N(i_{cp} d_{1}) - K e^{-r T} N(i_{cp} d_{2})) \\ 
   d_{1} & = \frac{ln(\frac{S}{K}) + (r   + \frac{\sigma^2}{2}) T}{\sigma \sqrt{T}} \\
   d_{2} & = \frac{ln(\frac{S}{K}) + (r   - \frac{\sigma^2}{2}) T}{\sigma \sqrt{T}}
   \end{aligned}\f]
   * where:
   * * \f$S\f$ asset prize
   * * \f$K\f$ strike
   * * \f$\sigma\f$ volatility
   * * \f$r\f$ risk free rate
   * * \f$i_{cp}\f$ 1 for Call option; -1 for put option
   * * \f$N()\f$ standard normal distribution
   *
   * \param mkt market data
   * \param opt option to price
   * \return price of option
   */
  double BSprice(const Market& mkt, const EuroOpt& opt) {
    auto K = opt.getK();
    auto T = opt.getT();

    double d1 = std::log(mkt.spot / K) + ( mkt.r + 0.5 * mkt.vol * mkt.vol) * T;
    d1 = d1 / (mkt.vol * std::sqrt(T));

    double d2 = std::log(mkt.spot / K) + ( mkt.r - 0.5 * mkt.vol * mkt.vol) * T;
    d2 = d2 / (mkt.vol * std::sqrt(T));

    double value = 0.0;
    switch (opt.getType()) {
    case OptionType::CALL:
      value = mkt.spot * normalCDF(d1) - exp(-mkt.r*T) * K * normalCDF(d2); break;
    case OptionType::PUT:
      value = -mkt.spot * normalCDF(- d1) + exp(-mkt.r*T) * K * normalCDF(-d2); break;
    }
    return value;
  }
  
}  // namespace marian
