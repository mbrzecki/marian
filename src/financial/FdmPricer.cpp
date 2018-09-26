#include <financial/FdmPricer.hpp>
#include <utils/mathUtils.hpp>
#include <diffusion/backwardKolmogorovEq.hpp>
#include <utils/utils.hpp>
#include <cmath>

namespace marian {

  /** \brief  Method pricing option
   *
   *  The steps of algorithm are as follows:
   * - Obtaining concentration point and limits of the grid 
   * - Creating the grid
   * - Calculating initial condition
   * - Obtaining boundary condition   
   * - Creating diffusion process
   * - Solving Backward Kolmogorov Equation
   * - Interpolating results
   *
   * \param mkt Market data
   * \param option Financial option
   * \param Ns Number of spatial steps, default number 100
   * \param Nt Number of time steps, default number 200
   */
  double FDMPricer::price(Market mkt, SmartPointer<Option> option, int Ns, int Nt) {
    auto factory = option->allocateFactory();
    // Generating grid's range and concentration points
    auto low = factory->lowerSpotLmt();
    auto upp = factory->upperSpotLmt();
    auto concentration_point = factory->getConcentrationPoint();
	
	// Converting infinite range to finite 
    if (low == 0.0) {
      low = range_setter_->getLowerBound(mkt, option);
    }
    if (upp == INFTY) {
      upp = range_setter_->getUpperBound(mkt, option);
    }
  
    // Generating grid
    auto sgrid = sgrid_->buildGrid(std::log(low), std::log(upp), Ns, concentration_point);
    auto tgrid = tgrid_->buildGrid(0.0, option->getT(), Nt, 0.0);
    
    // Initial condition
    std::vector<double> grid;
    for (auto i : sgrid) {
      grid.push_back(std::exp(i));
    }
    auto initial = factory->initialCondition(grid);
 
    // Boundary conditions
    auto boundary_condition = factory->getBoundarySpotConditions(mkt, low, upp);

    // Generating stochastic process from market data
    ConvectionDiffusion diffusion = mkt2process(mkt);

    // Formulating PDE problem
    BackwardKolmogorowEquation bpde(diffusion);
    auto fdm_solution  = bpde.solve(scheme_, initial,  boundary_condition, sgrid, tgrid);
    return interpolation(grid, fdm_solution , mkt.spot);
  }
   /** \brief  Method solves pricing PDE and save results to csv
   *
   *  The steps of algorithm are as follows:
   * - Obtaining concentration point and limits of the grid 
   * - Creating the grid
   * - Calculating initial condition
   * - Obtaining boundary condition   
   * - Creating diffusion process
   * - Solving Backward Kolmogorov Equation
   * - Saves results to CSV
   *
   * \param mkt Market data
   * \param option Financial option
   * \param file Name of CSV file
   * \param Ns Number of spatial steps
   * \param Nt Number of time steps
   */
  void FDMPricer::solveAndSave(Market mkt, SmartPointer<Option> option, std::string file, int Ns, int Nt) {
    auto factory = option->allocateFactory();
    // Generating grid's range and concentration points
    auto low = factory->lowerSpotLmt();
    auto upp = factory->upperSpotLmt();
    auto concentration_point = factory->getConcentrationPoint();
	
	// Converting infinite range to finite 
    if (low == 0.0) {
      low = range_setter_->getLowerBound(mkt, option);
    }
    if (upp == INFTY) {
      upp = range_setter_->getUpperBound(mkt, option);
    }
  
    // Generating grid
    auto sgrid = sgrid_->buildGrid(std::log(low), std::log(upp), Ns, concentration_point);
    auto tgrid = tgrid_->buildGrid(0.0, option->getT(), Nt, 0.0);
    
    // Initial condition
    std::vector<double> grid;
    for (auto i : sgrid) {
      grid.push_back(std::exp(i));
    }
    auto initial = factory->initialCondition(grid);
	
    // Boundary conditions
    auto boundary_condition = factory->getBoundarySpotConditions(mkt, low, upp);

	// Generating stochastic process from market data
    ConvectionDiffusion diffusion = mkt2process(mkt);

	// Formulating PDE problem
    BackwardKolmogorowEquation bpde(diffusion);
    bpde.solveAndSave(scheme_, initial,  boundary_condition, sgrid, tgrid, file);
  }
  
}  // namespace marian
