#ifndef MARIAN_FDMPRIZER_H
#define MARIAN_FDMPRIZER_H

#include <FDM/schemes/fdScheme.hpp>
#include <FDM/gridBuilders/gridBuilder.hpp>
#include <financial/options/option.hpp>
#include <financial/market.hpp>
#include <financial/gridRange/rangeSetup.hpp>

namespace marian {

  /** \brief Class implements algorithm solving pricing PDE.
   * \ingroup fin
   *
   *
   * Class is implementation of strategy pattern (see \cite GoF). 
   * Strategy pattern defines a family of algorithms, encapsulate each one, and make them interchangeable. 
   * The algorithms encapsulated in this class are:
   * - Scheme for FD method
   * - Spatial discretization 
   * - Time discretization
   * - FDM Grid builder
   * 
   * Other object required by FDM solver (boundary and initial conditions) are obtained from abstract factory allocated by option being priced
   */
  class FDMPricer {
  public:
    /** \brief Constructor
     */
    FDMPricer(SmartPointer<FDScheme> scheme,
	      SmartPointer<TridiagonalSolver> solver,
	      SmartPointer<GridBuilder> sgrid,
	      SmartPointer<GridBuilder> tgrid,
	      SmartPointer<RangeSetup> range_setter):
      scheme_(scheme), sgrid_(sgrid), tgrid_(tgrid), range_setter_(range_setter) {
      scheme_->setSolver(solver);
    }


    double price(Market m, SmartPointer<Option> o, int Ns = 100, int Nt = 200);
    void solveAndSave(Market market, SmartPointer<Option> option, std::string file, int Ns = 100, int Nt = 200);
  private:
    SmartPointer<FDScheme> scheme_; /*!< \brief FD scheme (Explicit, Implicit, etc)  */
    SmartPointer<GridBuilder> sgrid_; /*!< \brief Algorithm generating spatial grid  */
    SmartPointer<GridBuilder> tgrid_; /*!< \brief Algorithm generating time grid  */
    SmartPointer<RangeSetup> range_setter_;  /*!< \brief Algorithm defining range of grid  */
  };

}  // namespace marian
#endif /* MARIAN_FDMPRIZER_H */
