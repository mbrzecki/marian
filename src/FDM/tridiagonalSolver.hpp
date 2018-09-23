#ifndef MARIAN_TRIDIAGONALSOLVER_HPP
#define MARIAN_TRIDIAGONALSOLVER_HPP

#include <FDM/tridiagonalOperator.hpp>

namespace marian {

  /** \ingroup fdm
   *
   * \brief Interface of tridiagonal system solvers
   *
   * Method solves below system
   * \f[w = A \times v\f] 
   * 
   * where \f$w\f$ is real number vector, and \f$A\f$ is tridiagonal operator.
   * This class is used to perform implicit step in FDM algorithm 
   *
   * \todo Implement Successive over-relaxation method \cite sor
   */
  class TridiagonalSolver {
  public:
    /** \brief Constructor
     */
    TridiagonalSolver() {
    }

    /** \brief Method solves tridiagonal system using algorithm implemented in derived classes
     *
     * Method solves below system
     * \f[w = A \times v\f] 
     *
     * \param A Tridiagonal matrix defining tridiagonal system
     * \param w Vector of real numbers
     * \return Vector of real numbers being solution of system: \f$w = A \times v\f$ 
     */  
    virtual std::vector<double> solve(const TridiagonalOperator& A,
				      const std::vector<double>& w) const = 0;

    /** \brief Virtual copy constructor
     */
    virtual TridiagonalSolver* clone() const = 0;

    /** \brief Destructor
     */
    virtual ~TridiagonalSolver() {
    }
  };

  /** \ingroup fdm 
   *
   * \brief Deeply copyable TridiagonalSolver
   *
   * Class implements Curiously Recurring Template Pattern (see [Wikipedia site](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)).
   *
   * When using polymorphism, one sometimes needs to create copies of objects by the base class pointer. 
   * A commonly used idiom for this is adding a virtual clone function that is defined in every derived class. 
   * The CRTP can be used to avoid having to duplicate that function or other similar functions in every derived class.
   *
   * For more information about virtual copy constructor see \cite joshi
   */
  template<typename T>
  class DCTridiagonalSolver : public TridiagonalSolver {
  public:
    /** \brief Virtual copy constructor
     */
    virtual TridiagonalSolver* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
  
}  // namespace marian


#endif /* MARIAN_TRIDIAGONALSOLVER_HPP */
