#ifndef MARIAN_TRIDIAGONALOPERATOR_HPP
#define MARIAN_TRIDIAGONALOPERATOR_HPP

#include <vector>
#include <iostream>

namespace marian {

  /** \ingroup fdm 
   * \brief TridiagonalOperator is used to define differentiating operator for PDE being solved
   *
   * TridiagonalOperator is tridiagonal matrix is a band matrix that has non-zero elements only on the main diagonal, 
   * the first diagonal below this, and the first diagonal above the main diagonal. 
   *
   *\f[Tridiag = \begin{pmatrix}a_1 & b_1 \\c_1 & a_2 & b_2 \\& c_2 & \ddots & \ddots \\& & \ddots & \ddots & b_{n-1} \\& & & c_{n-1} & a_n\end{pmatrix}\f]
   *
   * As a sparse matrix having non-zero elements only on its diagonals it can be represented by three number vectors representing below lower, upper and mid diagonal.
   *
   * Tridiagonal matrices are convenient way to represent finite different problem. For example, forward difference formula:
   * \f[f''(x_i)\approx {\frac {\delta _{h}^{2}f(x_i)}{h^{2}}}={\frac {f(x_i+h)-2f(x_i)+f(x_i-h)}{h^{2}}}\f] 
   *
   * can be represent by following matrix:
   *
   * \f[f''(x) \approx {\frac {f(x_i+h)-2f(x_i)+f(x_i-h)}{h^{2}}}=\frac{1}{h^2}
   \begin{pmatrix} -2.0 & 1.0 \\  1.0 & -2.0 & 1.0  \\ & 1.0 & -2.0 & 1.0 \\ & & \ddots & \ddots & \ddots \\
   & & 1.0 & -2.0 & 1.0 & \\ & &   & 1.0 & -2.0 \end{pmatrix}
   \begin{pmatrix} f(x_1) \\ f(x_2) \\ f(x_3) \\ \vdots \\ f(x_{n-1}) \\ f_n\end{pmatrix}
   \f]
   * where first and last row should be properly handled by boundary conditions and \f$x_{i+1} = x_{i} + h\f$.
   *
   * TridiagonalOperator class encapsulates the logic of tridiagonal matrix and provides simple methods to handle this mathematical objects.
   * More details see \cite london \cite capinski
   */

  class TridiagonalOperator {   
  public:
    /*! \name Constructors
     */
    /** \brief Default constructor*/
    TridiagonalOperator(){};
    explicit TridiagonalOperator(unsigned int size);
    TridiagonalOperator(unsigned int size, double low, double mid, double upp);
    
    /** \brief Constructor
	\param low Lower diagonal
	\param mid Mid diagonal
	\param upp Upper diagonal
    */
    TridiagonalOperator(const std::vector<double>& low, const std::vector<double>& mid, const std::vector<double>& upp):
      size_(mid.size()), low_(low), mid_(mid), upp_(upp) {};
    //@}

    /*! \name Differential Operators
     */
    //@{
    
    static TridiagonalOperator DPlus(int n, double h);
    static TridiagonalOperator DMinus(int n, double h);  
    static TridiagonalOperator DZero(int n, double h);
    static TridiagonalOperator DZero(const std::vector<double>& grid);
    static TridiagonalOperator DPlusMinus(int n, double h);
    static TridiagonalOperator DPlusMinus(const std::vector<double>& grid);
    static TridiagonalOperator I(int n);
    static TridiagonalOperator I(const std::vector<double>& grid);
    //@}
    /*! \name Getters
     */
    //@{
    /** \brief Return size of tridiagonal matrix
     */
    int size() const { return size_; }
    double low(int) const;
    double mid(int) const;
    double upp(int) const;
    //@}
    /*! \name Setters
     */
    void setFirstRow(double, double);
    void setMidRow(int, double, double, double);
    void setMidRows(double, double, double);
    void setLastRow(double, double);

    //@}
    
    virtual ~TridiagonalOperator(){};
    
    friend std::ostream & operator<<(std::ostream &s, const TridiagonalOperator& A);
    friend TridiagonalOperator operator+(const TridiagonalOperator&, const TridiagonalOperator&);
    friend TridiagonalOperator operator-(const TridiagonalOperator&, const TridiagonalOperator&);
    friend TridiagonalOperator operator*(double, const TridiagonalOperator&);
    friend TridiagonalOperator operator*(const TridiagonalOperator&, double);
    friend TridiagonalOperator operator/(const TridiagonalOperator&, double);
    friend std::vector<double> operator*(const TridiagonalOperator&, std::vector<double>);
  private:
    unsigned int size_;    /*!< \brief Size of matrix*/
    std::vector<double> low_;  /*!< \brief Lower diagonal*/
    std::vector<double> mid_;  /*!< \brief Mid diagonal*/
    std::vector<double> upp_;  /*!< \brief upper diagonal*/ 
  };

  /** \brief Creates tridiagonal operator representing forward differentiating of function f
   *
   * The differential operator \f$ D_{+} \f$ discretizes the first derivative with the forward differencing scheme
   * \f[ \frac{\partial u}{\partial x}\Big|_{x=x_i} \approx \frac{u_{i+1}-u_{i}}{h} = D_{+} u_{i} \f]
   * where \f$u_i = f(x_i), u_{i+1} = f(x_i + h)\f$
   *
   * The matrix form is:
     \f[\begin{pmatrix} 1 & 0 \\ 0 & -\frac{1}{h} & \frac{1}{h}  \\
     & 0 & -\frac{1}{h} & \frac{1}{h} \\ & & \ddots & \ddots & \ddots \\
     & &  & 0 & -\frac{1}{h} & \frac{1}{h} & \\ & & &   & 0 & 1  \end{pmatrix}\f]
   *
   * \param n Size of matrix
   * \param h Increment used in differentiating scheme 
   */
  inline TridiagonalOperator TridiagonalOperator::DPlus(int n, double h) {
    TridiagonalOperator to(n);
    double inv = 1.0 / h;
    to.setFirstRow(1.0, 0.0);          
    to.setMidRows(0.0, -inv, inv);
    to.setLastRow(0.0, 1.0);
    return to;
  }

  
  /** \brief Creates tridiagonal operator representing backward differentiating of function f
   *
   * The differential operator \f$ D_{-} \f$ discretizes the first derivative with the backward differencing scheme
   * \f[ \frac{\partial u}{\partial x}\Big|_{x=x_i} \approx \frac{u_{i}-u_{i-1}}{h} = D_{-} u_{i} \f]
   * where \f$u_i = f(x_i), u_{i-1} = f(x_i - h)\f$
   *
   The matrix form is:
   \f[\begin{pmatrix}1 & 0 \\ -\frac{1}{h} & \frac{1}{h} & 0 \\
   & -\frac{1}{h} & \frac{1}{h} & 0 \\ & & \ddots & \ddots & \ddots \\
   &  &  & -\frac{1}{h} & \frac{1}{h} & 0  &\\  & &   &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param n Size of matrix
   * \param h Increment used in differentiating scheme 
   */
  inline TridiagonalOperator TridiagonalOperator::DMinus(int n, double h) {
    TridiagonalOperator to(n);
    double inv = 1.0 / h;
    to.setFirstRow(1.0, 0.0);          
    to.setMidRows(-inv, inv, 0.0);
    to.setLastRow(0.0, 1.0);
    return to;
  }

  /** \brief Creates tridiagonal operator representing central differentiating of function f
   *
   * The differential operator \f$ D_{0} \f$ discretizes the first derivative with the central differencing scheme
   * \f[ \frac{\partial u}{\partial x}\Big|_{x=x_i} \approx \frac{u_{i+1}-u_{i-1}}{2h} = D_{0} u_{i} \f]
   * where \f$u_{i+1} = f(x_{i}+h), u_{i-1} = f(x_i - h)\f$
   *
   The matrix form is:
   \f[\begin{pmatrix} 1 & 0 \\ -\frac{1}{2h} &0& \frac{1}{2h}  \\  &  -\frac{1}{2h} &0& \frac{1}{2h} \\
   & & \ddots & \ddots & \ddots \\ & & &  -\frac{1}{2h}  &0& \frac{1}{2h} & \\ & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param n Size of matrix
   * \param h Increment used in differentiating scheme 
   */
  inline TridiagonalOperator TridiagonalOperator::DZero(int n, double h) {
    TridiagonalOperator to(n);
    double inv = 1.0 / (2.0*h);
    to.setFirstRow(1.0, 0.0);          
    to.setMidRows(-inv, 0.0, inv);
    to.setLastRow(0.0, 1.0);
    return to;
  }

  /** \brief Creates tridiagonal operator representing central differentiating of function f on non-uniform grid
   *
   * The differential operator \f$ D_{0} \f$ discretizes the first derivative with the central differencing scheme
   * \f[ \frac{\partial u}{\partial x}\Big|_{x=x_i} \approx \frac{h^2_i u_{i+1} + (h^2_{i+1} - h^2_i) u_i - h^2_{i+1}u_{i-1} }{ h_i h_{i+1} (h_i+h_{i+1})} = D_{0} u_{i} \f]
   * where \f$u_i = f(x_i), h_i = x_i - x_{i-1}\f$
   *
   * The matrix form is:
   \f[\begin{pmatrix} 1& 0 \\
   -\frac{h^2_{1}}{h_0 h_{1}(h_0+h_{1})} & \frac{h^2_1 - h^2_0}{h_0 h_{1}(h_0+h_{1})} & \frac{h^2_0}{h_0 h_{1}(h_0+h_{1})}  \\
   & -\frac{h^2_{2}}{h_1 h_{2}(h_1+h_{2})} & \frac{h^2_2 - h^2_1}{h_1 h_{2}(h_1+h_{2})} & \frac{h^2_1}{h_1 h_{2}(h_1+h_{2})}  \\
   & & \ddots & \ddots & \ddots \\
   & & & -\frac{h^2_{n}}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & \frac{h^2_{n} - h^2_{n-1}}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & \frac{h^2_{n-1}}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & \\ 
   & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param grid Grid used for discretization (may be non-uniform) 
   */
  inline TridiagonalOperator TridiagonalOperator::DZero(const std::vector<double>& grid) {
    TridiagonalOperator to(grid.size());
    to.setFirstRow(1.0, 0.0);          
    for (unsigned int i = 2; i < grid.size(); ++i) {
      double hm  = grid.at(i-1) - grid.at(i-2);
      double hp  = grid.at(i)   - grid.at(i-1);
      double num = hm*hp*(hp+hm);
      to.setMidRow(i, -hp*hp / num, (hp*hp - hm*hm) / num  ,hm * hm / num);
    }
    to.setLastRow(0.0, 1.0);
    return to;
  }
  /** \brief Creates tridiagonal operator representing central second differentiating of function f
   *
   * The differential operator \f$ D_{+-} \f$ discretizes the second derivative with the central differencing scheme
   * \f[ \frac{\partial^2 u}{\partial x^2}\Big|_{x=x_i} \approx \frac{u_{i+1} - 2u_{i}+u_{i-1}}{h^2} = D_{+-} u_{i} \f]
   * where \f$u_{i+1} = f(x_{i}+h), u_{i} = f(x_i), u_{i-1} = f(x_i - h)\f$
   *
   The matrix form is:
   \f[\begin{pmatrix} 1  & 0 \\ \frac{1}{h^2}    & -\frac{2}{h^2} &  \frac{1}{h^2}    \\
   &  \frac{1}{h^2}    & -\frac{2}{h^2} & \frac{1}{h^2} \\ & & \ddots & \ddots & \ddots \\
   & & &  \frac{1}{h^2}    & -\frac{2}{h^2}&  \frac{1}{h^2} & \\ & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param n Size of matrix
   * \param h Increment used in differenting scheme 
   */
  inline TridiagonalOperator TridiagonalOperator::DPlusMinus(int n, double h) {
    TridiagonalOperator to(n);
    double inv = 1.0 / (h*h);
    to.setFirstRow(1.0, 0.0);   
    to.setMidRows(inv, -2.0*inv, inv);
    to.setLastRow(0.0, 1.0);   
    return to;
  }

    /** \brief Creates tridiagonal operator representing central second differentiating of function f on non-uniform grid
   *
   * The differential operator \f$ D_{+-} \f$ discretizes the second derivative with the central differencing scheme
   * \f[ \frac{\partial^2 u}{\partial x^2}\Big|_{x=x_i} \approx 2\frac{h_i u_{i+1} - (h_{i+1} + h_i) u_i + h_{i+1}u_{i-1} }{ h_i h_{i+1} (h_i+h_{i+1})} = D_{0} u_{i} \f]
   * where \f$u_i = f(x_i), h_i = x_i - x_{i-1}\f$
   *
   * The matrix form is:
   \f[\begin{pmatrix} 1& 0 \\
   \frac{2h_{1}}{h_0 h_{1}(h_0+h_{1})} & -\frac{2(h_1 + h_0)}{h_0 h_{1}(h_0+h_{1})} & \frac{2h_0}{h_0 h_{1}(h_0+h_{1})}  \\
   & \frac{2h_{2}}{h_1 h_{2}(h_1+h_{2})} & -\frac{2(h_2 + h_1)}{h_1 h_{2}(h_1+h_{2})} & \frac{2h_1}{h_1 h_{2}(h_1+h_{2})}  \\
   & & \ddots & \ddots & \ddots \\
   & & & \frac{2h_{n}}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & -\frac{2(h_{n} + h_{n-1})}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & \frac{2h_{n-1}}{h_{n-1} h_{n}(h_{n-1}+h_{n})} & \\ 
   & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param grid Grid used for discretization (may be non-uniform) 
   */
  inline TridiagonalOperator TridiagonalOperator::DPlusMinus(const std::vector<double>& grid) {
    TridiagonalOperator to(grid.size());
    to.setFirstRow(1.0, 0.0);          
    for (unsigned int i = 2; i < grid.size()-1; ++i) {
      double hm  = grid.at(i-1) - grid.at(i-2);
      double hp  = grid.at(i)   - grid.at(i-1);
      double num = hm*hp*(hp+hm);
      to.setMidRow(i, 2.0*hp / num, -2.0*(hp + hm) / num  ,2.0 * hm / num);
    }
    to.setLastRow(0.0, 1.0); 
    return to;
  }

  
  /** \brief Creates tridiagonal operator representing identity matrix
   *
   *
   *  Creates tridiagonal operator representing identity matrix. The matrix form is:
   \f[\begin{pmatrix} 1  & 0 \\ 0 & 1 & 0 \\ & 0 & 1 & 0 \\ & & \ddots & \ddots & \ddots \\ & & & 0 & 1 & 0 & \\ & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param n Size of matrix
   */
  inline TridiagonalOperator TridiagonalOperator::I(int n) {
    TridiagonalOperator to(n);
    to.setFirstRow(1.0, 0.0);   
    to.setMidRows(0.0, 1.0, 0.0);
    to.setLastRow(0.0, 1.0);   
    return to;
  }

  /** \brief Creates tridiagonal operator representing identity matrix
   *
   *
   *  Creates tridiagonal operator representing identity matrix. The matrix form is:
   \f[\begin{pmatrix} 1  & 0 \\ 0 & 1 & 0 \\ & 0 & 1 & 0 \\ & & \ddots & \ddots & \ddots \\ & & & 0 & 1 & 0 & \\ & & &  & 0 & 1 \end{pmatrix}\f]
   *
   * \param grid Grid used for discretization (may be non-uniform) 
   */
  inline TridiagonalOperator TridiagonalOperator::I(const std::vector<double>& grid) {
    TridiagonalOperator to(grid.size());
    to.setFirstRow(1.0, 0.0);   
    to.setMidRows(0.0, 1.0, 0.0);
    to.setLastRow(0.0, 1.0);   
    return to;
  }
} //namespace marian

#endif /* MARIAN_TRIDIAGONALOPERATOR_HPP */
