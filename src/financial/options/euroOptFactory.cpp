#include <financial/options/euroOptFactory.hpp>
#include <utils/mathUtils.hpp>
#include <FDM/boundaryConditions/dirichletBoundaryCondition.hpp>
#include <cmath>


namespace marian {

   /** \brief Returns vector of boundary conditions for European Option
   *
   * For call option
   * - lower boundary: Dirichlet condition \f$\lim_{S \to 0} C(S) = 0\f$ 
   * - upper boundary: Dirichlet condition \f$\lim_{S \to \infty} f(x) = S-K\f$  
   *
   * For put option
   * - lower boundary: Dirichlet condition \f$\lim_{S \to 0} C(S) = K-S\f$ 
   * - upper boundary: Dirichlet condition \f$\lim_{S \to \infty} f(x) = 0\f$  
   */
  std::vector<SmartPointer<BoundaryCondition> > EuroOptFactory::getBoundarySpotConditions(Market m, double low_boundary, double upp_boundary) {
    std::vector<SmartPointer<BoundaryCondition> > ret;
	if  (OptionType::CALL == type_)  {
		auto low_dbc_func = [](double)->double{return 0.0;};
		DirichletBoundaryCondition<decltype(low_dbc_func)> low(BCSide::LOW, low_dbc_func);

		auto k = k_;
		auto r = m.r;

		auto upp_dbc_func = [k, r, upp_boundary](double )->double{
		  return upp_boundary - k;
		};
		DirichletBoundaryCondition<decltype(upp_dbc_func)> upp(BCSide::UPP, upp_dbc_func);
		ret.push_back(low);
		ret.push_back(upp);
	} else if (OptionType::PUT == type_)  {
		auto upp_dbc_func = [](double)->double{return 0.0;};
		DirichletBoundaryCondition<decltype(upp_dbc_func)> upp(BCSide::UPP, upp_dbc_func);

		auto k = k_;
		auto r = m.r;

		auto low_dbc_func = [k, r, low_boundary](double )->double{
		  return k - low_boundary;
		};
		DirichletBoundaryCondition<decltype(low_dbc_func)> low(BCSide::LOW, low_dbc_func);
		ret.push_back(low);
		ret.push_back(upp);		
		
	}
    return ret;
  }

  /** \brief Returns vector initializing value of the option
  *
   *  \f[initial(s) = max(i_{cp}(S-K))\f]
   *  where \f$i_{cp}\f$ is equal to 1 if option type is CALL and -1 otherwise.
  */
  std::vector<double> EuroOptFactory::initialCondition(const std::vector<double>& grid) {
    std::vector<double> ret;
    if (OptionType::CALL == type_) {
      for (auto g : grid) {
	double temp = g > k_ ? g - k_ : 0.0;
	ret.push_back(temp);
      }
    } else {
      for (auto g : grid) {
	double temp = g < k_ ? k_ - g : 0.0;
	ret.push_back(temp);
      }
    }
    return ret;
  }
  
   /** \brief Returns \b 0 as upper limit of the spot 
  */  
  double EuroOptFactory::lowerSpotLmt() {
    return 0.0;
  }
  
   /** \brief Returns \f$-\infty\f$ as upper limit of the spot 
  */
  double EuroOptFactory::upperSpotLmt() {
    return INFTY;
  }

  /** \brief Returns strike as concentration point 
  */
  double EuroOptFactory::getConcentrationPoint() {
    return k_;
  }
  
}  // namespace marian
