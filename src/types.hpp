#ifndef MARIAN_TYPES_H
#define MARIAN_TYPES_H

namespace marian {
  /** \ingroup utils
   * \brief Types of options
   */
  enum class OptionType {
    PUT  = -1, ///< Put option 
    CALL =  1  ///< Call option
  };
} // namespace marian
#endif /* MARIAN_TYPES_H */
