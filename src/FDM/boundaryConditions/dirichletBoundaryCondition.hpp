#ifndef MARIAN_DIRICHLETBOUNDARYCONDITION_H
#define MARIAN_DIRICHLETBOUNDARYCONDITION_H


#include <vector>
#include <FDM/tridiagonalOperator.hpp>
#include <FDM/boundaryConditions/boundaryCondition.hpp>

namespace marian {

  /** \ingroup boundary
   *
   * \brief Class implements Dirichlet Boundary Condition
   *
   *
   * The condition specifies the value of a solution on the boundary of the domain.
   * \f[y(x,t)|_{x=boundary} = \chi(t) \f]
   */
  template<typename F>
  class DirichletBoundaryCondition: public DCBoundaryCondition<DirichletBoundaryCondition<F> > {
  public:
    /** \brief Default constructor
     */
    DirichletBoundaryCondition() {};

    /** \brief Constructor
     *
     * \param side Side for which boundary condition is set
     * \param value Value that be assigned to solution on the boundary
     */
    DirichletBoundaryCondition(BCSide side, F value):
      side_(side), value_(value) {};

    void beforeExplicitStep(TridiagonalOperator&) override;
    void afterExplicitStep(std::vector<double>&, double t) override;

    void beforeImplicitStep(TridiagonalOperator&, std::vector<double>&, double t) override;
    void afterImplicitStep(std::vector<double>&, double t) override;

    std::string info() const override {
      std::string side;
      switch(side_) {
      case BCSide::LOW:  side = " low"; break;
      case BCSide::UPP:  side = " up";  break;
      case BCSide::FREE: side = " free";break;	
      }
      return "DirichletBC" + side;
    }
    /** \brief Destructor
     */
    virtual ~DirichletBoundaryCondition(){};

  private:
    BCSide side_;    /*!< \brief Side for which boundary condition is set*/
    F value_;         /*!< \brief Value on the boundary.*/
  };

  
  /** \brief Modification of tridiagonal matrix before explicit step
   *
   * Elements of the first (in case of low boundary) or the last (in case of upper boundary) row of tridiagonal operator
   * are set to 0.0, expect the diagonal element which is set to 1.0.
   */
  template<typename F>
  void DirichletBoundaryCondition<F>::beforeExplicitStep(TridiagonalOperator& op) {
    switch (side_) {
    case BCSide::LOW:
      op.setFirstRow(1.0, 0.0);
      break;
    case BCSide::UPP:
      op.setLastRow(0.0, 1.0);
      break;
    case BCSide::FREE:
      break;
    }
  }

  /** \brief Modification of solution after explicit step
   *
   * The first (in case of low boundary) or the last (in case of upper boundary) element is set to certain value.
   */
  template<typename F>
  void DirichletBoundaryCondition<F>::afterExplicitStep(std::vector<double>& f, double t) {
    switch (side_) {
    case BCSide::LOW:
      f.front() = value_(t);
      break;
    case BCSide::UPP:
      f.back() = value_(t);
      break;
    case BCSide::FREE:
      break;
    }
  }

  /** \brief Modification of solution and linear operator before explicit step
   *
   * 
   * Elements of the first (in case of low boundary) or the last (in case of upper boundary) row of tridiagonal operator
   * are set to 0.0, expect the diagonal element which is set to 1.0.
   *
   * The first (in case of low boundary) or the last (in case of upper boundary) element is set to certain value.
   */
  template<typename F>
  void DirichletBoundaryCondition<F>::beforeImplicitStep(TridiagonalOperator& L,
							 std::vector<double>& f,
							 double t) {
    switch (side_) {
    case BCSide::LOW:
      L.setFirstRow(1.0, 0.0);
      f.front() = value_(t);
      break;
    case BCSide::UPP:
      L.setLastRow(0.0, 1.0);
      f.back() = value_(t);
      break;
    case BCSide::FREE:
      break;
    }
  }

  /** \brief Empty method,  no modification performed
   *
   *  
   */
  template<typename F>
  void DirichletBoundaryCondition<F>::afterImplicitStep(std::vector<double>&, double) {
  }
  
} // namespace marian


#endif /* MARIAN_DIRICHLETBOUNDARYCONDITION_H */
