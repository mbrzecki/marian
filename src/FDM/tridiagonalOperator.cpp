#include <FDM/tridiagonalOperator.hpp>
#include <iostream>

namespace marian {
  /** \brief Constructor defining tridiagonal operator filled with zeros.
      \param size Size of tridiagonal operator
  */
  TridiagonalOperator::TridiagonalOperator(unsigned int size = 0) {
    size_ = size;
    if (size > 0) {
      low_.resize(size-1,0.0);
      mid_.resize(size,0.0);
      upp_.resize(size-1,0.0);

    }
  }

  /** \brief Constructor defining tridiagonal operator. 
      \param size Size of tridiagonal operator
      \param low Numbers hold on lower diagonal
      \param mid Numbers hold on mid diagonal
      \param upp Numbers hold on upper diagonal
  */
  TridiagonalOperator::TridiagonalOperator(unsigned int size, double low, double mid, double upp) {
    size_ = size;
    if (size > 0) {
      low_.resize(size-1,low);
      mid_.resize(size,mid);
      upp_.resize(size-1,upp);
    }
  }

  /** \brief Value of r-th row in low diagonal
   *
   * \param r Number of row
   * \return Value of r-th row in low diagonal
   */
  double TridiagonalOperator::low(int r) const {
    return low_.at(r);
  }
  /** \brief Value of r-th row in mid diagonal
   *
   * \param r Number of row
   * \return Value of r-th row in mid diagonal
   */
  double TridiagonalOperator::mid(int r) const {
    return mid_.at(r);
  }
  /** \brief Value of r-th row in upp diagonal
   *
   * \param r Number of row
   * \return Value of r-th row in upp diagonal
   */ 
  double TridiagonalOperator::upp(int r) const {
    return upp_.at(r);
  }
  /** \brief Set first row
   *
   * \param mid Value for mid diagonal in first row
   * \param upp Value for upp diagonal in first row  
   */
  void TridiagonalOperator::setFirstRow(double mid, double upp) {
    mid_.front() = mid;
    upp_.front() = upp;
  }

  /** \brief Set i-th row
   *
   * \param i Number of row
   * \param low Value for lower diagonal in i-th row
   * \param mid Value for mid diagonal in i-th row
   * \param upp Value for upper diagonal in i-th row  
   */
  void TridiagonalOperator::setMidRow(int i, double low, double mid, double upp) {
    low_.at(i-2) = low;
    mid_.at(i-1) = mid;
    upp_.at(i-1) = upp; 
  }

  /** \brief Set middle rows
   *
   * \param low Value for lower diagonal (except first and last row)  
   * \param mid Value for mid diagonal (except first and last row)  
   * \param upp Value for upper diagonal (except first and last row)   
   */
  void TridiagonalOperator::setMidRows(double low, double mid, double upp) {
    for (unsigned int i = 1; i < size_ - 1 ; i++) {
      low_.at(i-1) = low;
      mid_.at(i) = mid;
      upp_.at(i) = upp; 
    }
  }

  /** \brief Set first row
   *
   * \param low Value for lower diagonal in last row
   * \param mid Value for mid diagonal in last row  
   */
  void TridiagonalOperator::setLastRow(double low, double mid) {
    low_.back() = low;
    mid_.back() = mid;
  }

  /** \brief Overloading of << operator
   *
   * Method allows to print the tridiagonal operator on console.
   */
  std::ostream& operator<<(std::ostream& s, const TridiagonalOperator& A) {
    s << ".\t" << A.mid_.front() << "\t" << A.upp_.front() << "\n";
    for (unsigned int i = 1; i < A.size_-1; i++) {
      s << A.low_.at(i-1) << "\t" << A.mid_.at(i) << "\t" << A.upp_.at(i) << "\n";
    }
    s << A.low_.back() << "\t" << A.mid_.back()  << "\t." << "\n";
    return s;
  }

  /** \brief Overloading of + operator
   *
   * Operator defines addition of tridiagonal operators
   *\f[
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} +
   \begin{pmatrix}d_1 & e_1 \\f_1 & d_2 & e_2 \\& f_2 & \ddots & \ddots \\& & \ddots & \ddots & e_{n-1} \\& & & f_{n-1} & d_n\end{pmatrix} =
   \begin{pmatrix}a_1 + d_1 & b_1 + e_1 \\ c_1 + f_1 & a_2 + d_2 & b_2 + e_2 \\& c_2 + f_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} + e_{n-1} \\& & & c_{n-1} + f_{n-1} & a_n + d_n\end{pmatrix}
   \f]
  */
  TridiagonalOperator operator+(const TridiagonalOperator& to1, const TridiagonalOperator& to2) {
    std::vector<double> low,mid,upp;
    
    for (unsigned int i = 0; i < to1.size_-1; i++) {
      low.push_back(to1.low_.at(i) + to2.low_.at(i));
      mid.push_back(to1.mid_.at(i) + to2.mid_.at(i));
      upp.push_back(to1.upp_.at(i) + to2.upp_.at(i));
    }
    mid.push_back(to1.mid_.back() + to2.mid_.back());
    
    return TridiagonalOperator(low,mid,upp);
  }

  /** \brief Overloading of - operator
   *
   * Operator defines subtraction of tridiagonal operators
   *\f[
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} -
   \begin{pmatrix}d_1 & e_1 \\f_1 & d_2 & e_2 \\& f_2 & \ddots & \ddots \\& & \ddots & \ddots & e_{n-1} \\& & & f_{n-1} & d_n\end{pmatrix} =
   \begin{pmatrix}a_1 - d_1 & b_1 - e_1 \\ c_1 - f_1 & a_2 - d_2 & b_2 - e_2 \\& c_2 - f_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} - e_{n-1} \\& & & c_{n-1} - f_{n-1} & a_n - d_n\end{pmatrix}
   \f]
  */
  TridiagonalOperator operator-(const TridiagonalOperator& to1, const TridiagonalOperator& to2) {
    std::vector<double> low,mid,upp;
    
    for (unsigned int i = 0; i < to1.size_-1; i++) {
      low.push_back(to1.low_.at(i) - to2.low_.at(i));
      mid.push_back(to1.mid_.at(i) - to2.mid_.at(i));
      upp.push_back(to1.upp_.at(i) - to2.upp_.at(i));
    }
    mid.push_back(to1.mid_.back() - to2.mid_.back());
    
    return TridiagonalOperator(low,mid,upp);
  }

  /** \brief Overloading of * operator for TridiagonalOperator and a real number
   *
   * Operator defines left multiplication of tridiagonal operators and real number
   *\f[
   x \times
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} =
   \begin{pmatrix}x \times a_1 & x \times b_1 \\x \times c_1 & x \times a_2 & x \times b_2 
   \\& x \times c_2 & \ddots & \ddots \\& & \ddots & \ddots & x \times b_{n-1} \\& & & x \times c_{n-1} & x \times a_n\end{pmatrix}
   \f]
  */
  TridiagonalOperator operator*(double x, const TridiagonalOperator& to) {
    std::vector<double> low,mid,upp;
    for (unsigned int i = 0; i < to.size_-1; i++) {
      low.push_back(to.low_.at(i) * x);
      mid.push_back(to.mid_.at(i) * x);
      upp.push_back(to.upp_.at(i) * x);
    }
    mid.push_back(to.mid_.back() * x);

    return TridiagonalOperator(low,mid,upp);
  }

  /** \brief Overloading of * operator for TridiagonalOperator and a real number
   *
   * Operator defines right multiplication of tridiagonal operators and real number
   *\f[
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} \times x =
   x \times \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} =
   \begin{pmatrix}x \times a_1 & x \times b_1 \\x \times c_1 & x \times a_2 & x \times b_2 
   \\& x \times c_2 & \ddots & \ddots \\& & \ddots & \ddots & x \times b_{n-1} \\& & & x \times c_{n-1} & x \times a_n\end{pmatrix}
   \f]
  */
  TridiagonalOperator operator*(const TridiagonalOperator& to, double x) {
    std::vector<double> low,mid,upp;
    
    for (unsigned int i = 0; i < to.size_-1; i++) {
      low.push_back(to.low_.at(i) * x);
      mid.push_back(to.mid_.at(i) * x);
      upp.push_back(to.upp_.at(i) * x);
    }
    mid.push_back(to.mid_.back() * x);

    return TridiagonalOperator(low,mid,upp);
  }

  /** \brief Overloading of / operator for TridiagonalOperator and a real number
   *
   *
   * Operator defines division of tridiagonal operators by real number
   *\f[
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} \div x =
   \begin{pmatrix}a_1 \div x &  b_1 \div x \\ c_1 \div x &  a_2 \div x &  b_2 \div x
   \\&  c_2 \div x & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \div x \\& & &  c_{n-1} \div x &  a_n \div x\end{pmatrix}
   \f]
  */
  TridiagonalOperator operator/(const TridiagonalOperator& to, double a) {
    std::vector<double> low,mid,upp;
    
    for (unsigned int i = 0; i < to.size_-1; i++) {
      low.push_back(to.low_.at(i) / a);
      mid.push_back(to.mid_.at(i) / a);
      upp.push_back(to.upp_.at(i) / a);
    }
    mid.push_back(to.mid_.back() / a);
    
    return TridiagonalOperator(low, mid, upp);
  }

  /** \brief Overloading of * operator for TridiagonalOperator and a vector of real number
   *
   * \f[w = A \times v =
   \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix} 
   \times \begin{pmatrix} v_1 \\ v_2 \\ v_3  \\ \vdots \\ v_{n-1} \\ v_n\end{pmatrix} =
   \begin{pmatrix} a_1 v_1 + v_2 b_1 \\ c_1 v_1 + a_2 v_2 + b_2 v_3 \\ \vdots  \\ \vdots \\ c_{n-2} v_{n-2} + a_{n-1} v_{n-1} + b_{n-1} v_{n} \\ c_{n-1} v_{n-1} + a_n v_n  \end{pmatrix} 
   \f]
   *
   * \param A Tridiagonal matrix
   * \param v Vector transformed by tridiagonal matrix A
   * \return Vector w, after transformation  
   */ 
  std::vector<double> operator*(const TridiagonalOperator& A, std::vector<double> v) {
    auto n = A.size();
    std::vector<double>	result(n);
    result[0] = A.mid(0)*v[0] + A.upp(0)*v[1];

    for (int j=1; j <= n-2; j++)
      result[j] = A.low(j-1) * v[j-1] + A.mid(j) * v[j] + A.upp(j) * v[j+1];

    result[n-1] = A.low(n-2) * v[n-2] + A.mid(n-1) * v[n-1];

    return result;
  }
}  // namespace marian
