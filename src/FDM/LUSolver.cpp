#include <FDM/LUSolver.hpp>

namespace marian {

  /** \brief Method solves tridiagonal system using algorithm implemented in derived classes
   *
   * Method solves below system  using LU method see \cite capinski)
   * \f[w = A \times v\f] 
   *
   * \todocument Add detailed description of algorithm.
   *
   * \param A Tridiagonal matrix defining tridiagonal system
   * \param w Vector of real numbers
   * \return Vector of real numbers being solution of system: \f$w = A \times v\f$ 
   */  
  std::vector<double> LUSolver::solve(const TridiagonalOperator& A,
				      const std::vector<double>& w) const {
    auto size = A.size();
    std::vector<double> ret  (size, 0.0);
    std::vector<double> temp (size, 0.0);
    double bet = A.mid(0);

    ret.at(0) = w.at(0) / bet;
    for (int j = 1; j <= size - 1; ++j) {
      temp.at(j) = A.upp(j-1) / bet;
      bet = A.mid(j) - A.low(j-1) * temp.at(j);
      ret.at(j) = ( w.at(j) - A.low(j-1) * ret.at(j-1) ) / bet;
    }

    for (int j = size - 2; j>0; --j)
      ret.at(j) -= temp.at(j+1)*ret.at(j+1);
    ret.at(0) -= temp.at(1)*ret.at(1);
    return ret;
  }
  
}  // namespace marian
