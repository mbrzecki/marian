#ifndef MARIAN_EUROOPTFACTORY_HPP
#define MARIAN_EUROOPTFACTORY_HPP

#include <financial/options/pricerAbstractFactory.hpp>
#include <financial/options/euroOpt.hpp>


namespace marian {

  /** \brief Class implements factory for European Option
   * \ingroup option
   *
   * Class is implementation of marian::AbstractPricerFactory. 
   * It is use to create objects that parametrize the FDM pricer used to value European Option.
   *
   * Parametrization provided by the class is as follows:
   *
   * Initial  condition
   * ---------------
   *  \f[f(s) = max(i_{cp}(S-K))\f]
   *  where \f$i_{cp}\f$ is equal to 1 if option type is CALL and -1 otherwise.
   * Boundary  condition
   * ---------------
   * For call option
   * - lower boundary: Dirichlet condition \f$\lim_{S \to 0} C(S) = 0\f$ 
   * - upper boundary: Dirichlet condition \f$\lim_{S \to \infty} f(x) = S-K\f$  
   *
   * For put option
   * - lower boundary: Dirichlet condition \f$\lim_{S \to 0} C(S) = K-S\f$ 
   * - upper boundary: Dirichlet condition \f$\lim_{S \to \infty} f(x) = 0\f$  
   *
   * Concentration parameter for non-uniform grid
   * ------------------------------------------- 
   * Option's strike   
   * 
   */
  class EuroOptFactory : public DCAbstractPricerFactory<EuroOptFactory> {
  public:
   /** \brief Default constructor 
   */
    EuroOptFactory(){};

	/** \brief Constructor 
	*
	* \param option European option for which factory will be constructed
   */
    EuroOptFactory(EuroOpt option):
      k_(option.getK()), t_(option.getT()), type_(option.getType()) {}
    
    std::vector<SmartPointer<BoundaryCondition> > getBoundarySpotConditions(Market m, double low,double upp) override;
    std::vector<double> initialCondition(const std::vector<double>& grid);
    double lowerSpotLmt() override;
    double upperSpotLmt() override;
    double getConcentrationPoint()  override;
  private:
    double k_; /*!< \brief Strike of the option */
    double t_; /*!< \brief Maturity of the option */
    OptionType type_;  /*!< \brief Type of option*/
  };
}  // namespace marian

#endif /* MARIAN_EUROOPTFACTORY_HPP */
