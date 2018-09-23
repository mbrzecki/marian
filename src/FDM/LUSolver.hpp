#ifndef MARIAN_LUSOLVER_HPP
#define MARIAN_LUSOLVER_HPP

#include <FDM/tridiagonalSolver.hpp>

namespace marian {
  /** \ingroup fdm
   * \brief Method applying implicit step
   *
   *  Method solves tridiagonal system using LU method (see \cite capinski)
   */

  class LUSolver : public DCTridiagonalSolver<LUSolver> {
  public:
    /** \brief Constructor
     */
    LUSolver(){};

    virtual std::vector<double> solve(const TridiagonalOperator& A,
				      const std::vector<double>& w) const override;

    /** \brief Constructor
     */
    ~LUSolver(){};
  };
  
}  // namespace marian



#endif /* MARIAN_LUSOLVER_HPP */
