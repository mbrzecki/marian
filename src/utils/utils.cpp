#include <utils/utils.hpp>
#include <cmath>

namespace marian {

  /** \ingroup utils
   * \brief Converts data stored in dataframe to European option
   *
   * Data frame should contain following columns:
   * * \b Id: String identification 
   * * \b Strike: double number representing strike 
   * * \b Tenor: double number representing tenor of option
   * * \b Type: 'C' or 'P' 
   *
   * \param df Dataframe containing parametrization of European options 
   * \return Map with options as values and ids as map's keys. 
   */
  std::map<std::string, EuroOpt> createEuroOpts(DataFrame df) {
    std::map<std::string, EuroOpt> ret;
    for (auto r = 1; r <= df.getNumberOfRows(); ++r) {
      auto id       = df("Id", r);
      auto strike   = df.getNumber("Strike", r);
      auto tenor    = df.getNumber("Tenor", r);
      auto type_str = df("Type", r);
      
      if (type_str == "C") {
    	EuroOpt opt(strike, tenor, OptionType::CALL);
    	ret[id] = opt;
      } else if (type_str == "P") {
    	EuroOpt opt(strike, tenor, OptionType::PUT);
    	ret[id] = opt;
      } else {
    	std::cout << "Unknown option type " + type_str << std::endl;
      }
    }
    return ret;
  }

  
  /** \ingroup utils
   * \brief Converts data stored in dataframe to market data
   *
   * Data frame should contain following columns:
   * * \b Id: String identification 
   * * \b Spot: double number representing value of underlying 
   * * \b Vol: double number representing volatility
   * * \b Rate: double number representing the risk free interest rate 
   *
   * \param df Dataframe containing parametrization of market 
   * \return Map with options as values and ids as map's keys. 
   */
  std::map<std::string, Market>  createMarkets(DataFrame df) {
    std::map<std::string, Market> ret;
    for (auto r = 1; r <= df.getNumberOfRows(); ++r) {
      auto id    = df("Id", r);
      auto spot = df.getNumber("Spot", r);
      auto vol  = df.getNumber("Vol", r);
      auto rate = df.getNumber("Rate", r);
      Market mkt {spot, vol, rate};
      ret[id] = mkt;
    }
    return ret;
  }

  /** \ingroup utils
   * \brief Converts the option market data to diffusion process
   *
   *  The data defining : asset price, risk free rate and volatility of asset price. Under the assumptions of Black-Scholes model (see \cite BlackScholes) the price of derivative instruments
   *  satisfies the equation: 
   * \f[{\frac {\partial V}{\partial t}}+{\frac {1}{2}}\sigma ^{2}S^{2}{\frac {\partial ^{2}V}{\partial S^{2}}}+rS{\frac {\partial V}{\partial S}}-rV=0\f]
   * where: \f$V\f$ is the price of derivative,\f$s\f$ asset price, \f$\sigma\f$ volatility and \f$r\f$ is risk free rate.
   * 
   * After applying transformation \f$x=ln S\f$ the PDE will have a form:
   * \f[{\frac {\partial V}{\partial t}}+{\frac {1}{2}}\sigma ^{2}{\frac {\partial ^{2}V}{\partial x^{2}}}+(r-\frac{\sigma^2}{2}){\frac {\partial V}{\partial x}}-rV=0\f]
   * 
   * Above PDE is a Backward Kolmogorov Equation  associated with stochastic process: diffusion term \f$\frac{\sigma^2}{2}\f$, convection term \f$r-\frac{\sigma^2}{2}\f$ and decay term \f$r\f$.  
   * 
   */
  ConvectionDiffusion mkt2process(Market mkt) {
    ConvectionDiffusion diffusion {mkt.vol, mkt.r-mkt.vol*mkt.vol*0.5, mkt.r};
    return diffusion;
  }

}  // namespace marian
