#ifndef MARIAN_ANALYTICPRICER_H
#define MARIAN_ANALYTICPRICER_H

#include <utils/mathUtils.hpp>
#include <financial/options/euroOpt.hpp>
#include <financial/market.hpp>

namespace marian {

  double BSprice(const Market& mkt, const EuroOpt& opt);
  
}  // namespace fdm

#endif /* MARIAN_ANALYTICPRIZER_H */
