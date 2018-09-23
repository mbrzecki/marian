#include <marian.hpp>

using namespace marian;

/**
 * @example convergenceExample.cpp
 * 	
 * \brief Example shows how model converges when different schemes and grids are chosen. 
 *
 * We tested following settings:
 * - Explicit scheme with uniform grid
 * - Implicit scheme with uniform grid
 * - Crank-Nicolson scheme with uniform grid
 * - Crank-Nicolson scheme with non-uniform grid with low clustering
 * - Crank-Nicolson scheme with uniform grid with high clustering
 * 
 * We see that non-uniform grid converge faster for small number of spatial steps. 
 * For larger number of spatial steps the differences between schemes are small.
 *  @image html convergence_spatial.png
 *
 * In case of number of time steps, we see advantage of Crank Nicolson scheme, 
 * for which even the small number of time steps ensures convergence.
 * We see that solution differences from the analytical price. 
 * The difference is cause by using small number of spatial steps. 
 * Using larger number of spatial steps would cause the instability of explicit scheme for small number of time steps.
 * 
 *  @image html convergence_time.png
 */

int main() {
  
  //
  // Preparing building blocks of PDE solver
  //
  LUSolver solver;
  UniformGridBuilder ugrid;
  HSineGridBuilder nugrid1(0.75);
  HSineGridBuilder nugrid2(0.25);
  SpotRelatedRange range_setter(0.2, 3.0);
  
  ExplicitScheme scheme_ex;
  ImplicitScheme scheme_im;
  CrankNicolsonScheme scheme_cn;

  
  //
  // Constructing option and market
  //
  double strike = 1.0;
  double tenor = 1.0;
  EuroOpt option(strike, tenor, OptionType::CALL);

  Market market;
  market.spot = 1.05;
  market.vol = 0.25;
  market.r = 0.02;

  //
  // We will use analytical solution as benchmark
  //
  double analytic_price = BSprice(market, option);

  //
  // Preparing pricers and performing test
  //
  FDMPricer pricer1(scheme_ex, solver, ugrid,   ugrid, range_setter);
  FDMPricer pricer2(scheme_im, solver, ugrid,   ugrid, range_setter);
  FDMPricer pricer3(scheme_cn, solver, ugrid,   ugrid, range_setter);
  FDMPricer pricer4(scheme_cn, solver, nugrid1, ugrid, range_setter);
  FDMPricer pricer5(scheme_cn, solver, nugrid2, ugrid, range_setter);
  
  DataFrame results_spatial;
  for (int ns = 40; ns <= 200; ns += 10) {
    
    double fdm_price1 = pricer1.price(market, option, ns, 350);
    double fdm_price2 = pricer2.price(market, option, ns, 350);
    double fdm_price3 = pricer3.price(market, option, ns, 350);
    double fdm_price4 = pricer4.price(market, option, ns, 350);
    double fdm_price5 = pricer5.price(market, option, ns, 350);
    
    DataEntryClerk input;	  
    input.add("NS", ns);
    input.add("Analytic", analytic_price);  
    input.add("Explicit_uniform", fdm_price1);
    input.add("Implicit_uniform", fdm_price2);
    input.add("CrankNicolson_uniform", fdm_price3);
    input.add("CrankNicolson_nonuniform75", fdm_price4);
    input.add("CrankNicolson_nonuniform25", fdm_price5);
    results_spatial.append(input);
  }
  results_spatial.printToCsv("convergenceExample1");

    
  DataFrame results_time;
  for (int nt = 30; nt <= 300; nt += 10) {
    
    double fdm_price1 = pricer1.price(market, option, 50, nt);
    double fdm_price2 = pricer2.price(market, option, 50, nt);
    double fdm_price3 = pricer3.price(market, option, 50, nt);
    double fdm_price4 = pricer4.price(market, option, 50, nt);
    double fdm_price5 = pricer5.price(market, option, 50, nt);
    
    DataEntryClerk input;	  
    input.add("NT", nt);
    input.add("Analytic", analytic_price);  
    input.add("Explicit_uniform", fdm_price1);
    input.add("Implicit_uniform", fdm_price2);
    input.add("CrankNicolson_uniform", fdm_price3);
    input.add("CrankNicolson_nonuniform75", fdm_price4);
    input.add("CrankNicolson_nonuniform25", fdm_price5);
    results_time.append(input);
  }
  results_time.printToCsv("convergenceExample2");
}
