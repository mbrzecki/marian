#ifndef MARIAN_EUROOPT_HPP
#define MARIAN_EUROOPT_HPP

#include <iostream>
#include <types.hpp>
#include <financial/options/option.hpp>
namespace marian {

  /** \ingroup option
   * \brief Class implementing a European options
   */ 
  class EuroOpt : public DCOption<EuroOpt>  {
  public:
    /*! \name Constructors
     */
    //@{
    /** \brief Default constructor
     */
    EuroOpt() {};
    /** \brief Constructor
     *
     * \param strike Option's strike
     * \param T Option's maturity
     * \param type Option's type
     */
    EuroOpt(double strike, double T, OptionType type):
      strike_(strike), T_(T), type_(type) {}

    SmartPointer<AbstractPricerFactory> allocateFactory() const override;
    
    //@}
    /*! \name Getters
     */
    //@{
    double getK() const;
    double getT() const override;
    OptionType getType() const;
    //@}
    double payoff(const double s) const;
    
    friend std::ostream& operator<<(std::ostream&, EuroOpt&);  
  private:
    double strike_;   /*!< \brief Option's strike*/
    double T_;        /*!< \brief Option's maturity*/
    OptionType type_; /*!< \brief Option's type*/
  };
}  // namespace marian

#endif /* MARIAN_EUROOPT_HPP */
