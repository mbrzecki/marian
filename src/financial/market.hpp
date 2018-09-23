#ifndef MARIAN_MARKET_HPP
#define MARIAN_MARKET_HPP

#include <iostream>


namespace marian {
  /** \ingroup fin
   * \brief Data structure holding the market data
   */ 
  struct Market {
    double spot; ///< Price of underlying 
    double vol;  ///< Volatility 
    double r;    ///< Risk free rate
  };

  inline std::ostream& operator<<(std::ostream& s, Market& mkt) {
    s << "Spot: " << mkt.spot << " Vol " << mkt.vol << " Rate " << mkt.r << "\n"; 
    return s;
  }
}  // namespace market

#endif /* MARIAN_MARKET_HPP */
