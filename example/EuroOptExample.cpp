#include <marian.hpp>

using namespace marian;

/**
 * @example EuroOptExample.cpp
 * 	
 * \brief Example shows how to calculate euro option price using FDM pricer. 
 *
 *  Below we compare analytic solution with FDIFF method (plot based on EuroOptExample_sample.csv). We see perfect match 
 *  @image html EuroOptExample.png
 * 
 * Here we see the intermediate steps in solution. We see how diffusion process of option's 
 * value starts from payoff and ends as presents value while time is going backwards
 *  @image html EuroOptExample_solution.gif
 *
 * Output
 * ------
 *
 * @verbinclude EuroOptExample.dox 
 */
int main () {
  //
  // Reading option and market sample
  //
  DataFrame opt_df("../data/euroOpt.csv",';',true);
  DataFrame mkt_df("../data/mkt.csv",';',true);

  std::map<std::string, EuroOpt> options = createEuroOpts(opt_df);
  std::map<std::string, Market>  markets = createMarkets(mkt_df);

  opt_df.print();
  mkt_df.print();
  
  //
  // Preparing building blocks of PDE solver
  //
  LUSolver solver;
  UniformGridBuilder grid;
  SpotRelatedRange range_setter(0.2, 3.0);
  CrankNicolsonScheme scheme;

  //
  // Constructing pricer and pricing option sample
  // 
  FDMPricer pricer(scheme, solver, grid, grid, range_setter);
  
  DataFrame results;
  for (auto market : markets) {
    for (auto option : options) {
      double analytic_price = BSprice(market.second, option.second);
      double fdm_price = pricer.price(market.second, option.second, 500, 800);
      
      DataEntryClerk input;
      input.add("Market", market.first);
      input.add("Option", option.first);
      input.add("Analytic", analytic_price);
      input.add("FDM", fdm_price);
      input.add("Diff", fdm_price - analytic_price);
      results.append(input);
    }  // options
  }  // markets

  //
  // Saving results to csv file
  //
  results.printToCsv("EuroOptExample_sample");

  //
  // Saving whole solution  for selected market and option to csv file
  //
  auto option = options["Id1"];
  auto market = markets["Id3"];

  SHOW(option);
  SHOW(market);
  
  auto fdm_price      = pricer.price(market, option, 100, 200);
  auto analytic_price = BSprice(market, option);
  
  std::cout << "FDM price\t" << fdm_price << std::endl;
  std::cout << "Analytic price\t" << analytic_price << std::endl;

  pricer.solveAndSave(market, option, "EuroOptExample_solution", 100, 200);
}
