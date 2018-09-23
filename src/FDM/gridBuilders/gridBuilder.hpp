#ifndef MARIAN_GRIDBUILDER_HPP
#define MARIAN_GRIDBUILDER_HPP

#include <vector>

namespace marian {

  /** \brief Interface for classes building grids
   ** \ingroup grid
   *
   *
   * Class is an interface for grid building algorithm 
   */
  class GridBuilder {
  public:
    /** \brief Discretize the interval
     *
     * \param low Lower bound of interval
     * \param upp Upper bound of interval
     * \param N Number of grid points (N-1 intervals between lower and upper bound)
     * \param concentration Concentration parameter used to build non-uniform grid
     * \returns Set of doubles
     */
    virtual std::vector<double> buildGrid(double low, double upp, int N, double concentration) const = 0;
	
    /** \brief virtual copy constructor
     */
    virtual GridBuilder* clone() const;
		
    /** \brief destructor
     */
    virtual ~GridBuilder(){};
  };

  /** \ingroup grid
   *
   * \brief Deeply copyable GridBuilder
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
  class DCGridBuilder : public GridBuilder {
  public:
    /** \brief Virtual copy constructor
     */
    virtual GridBuilder* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
  
}  // namespace marian


#endif /* MARIAN_GRIDBUILDER_HPP */
