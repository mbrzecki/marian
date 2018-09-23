#ifndef MARIAN_UTILS_HPP
#define MARIAN_UTILS_HPP

#include <map>
#include <diffusion/convectionDiffusionProcess.hpp>
#include <financial/options/euroOpt.hpp>
#include <financial/market.hpp>
#include <utils/dataFrame.hpp>


namespace marian {

  #define SHOW(x) std::cout <<"\nName: "<< #x << "\n" << x << "\n"

  std::map<std::string, EuroOpt> createEuroOpts(DataFrame df);
  
  std::map<std::string, Market>  createMarkets(DataFrame df);

  ConvectionDiffusion mkt2process(Market mkt);
  
} // namespace marian

#endif /* MARIAN_UTILS_HPP */
