#ifndef MARIAN_CONVECTIONDIFFUSIONPROCESS_HPP
#define MARIAN_CONVECTIONDIFFUSIONPROCESS_HPP

namespace marian {

  /** \ingroup diffusion
   * \brief Data structure holding the parameters of diffusion-convection equation
   *
   * Diffusion convection PDE is given by formula:
   * \f[dX_t = c(t,X)dt+\sigma dW_t\f]
   * where D is diffusion term, c is convection term. Decay represent increase/decrease of diffusion process proportional to the value of diffusion.
   */   
  struct ConvectionDiffusion {
    double diffusion; ///< Diffusion \b \a D
    double convection; ///< Convection \b \a c
    double decay;  ///< Convection \b \a d
  };
  
}  // namespace marian

#endif /* MARIAN_CONVECTIONDIFFUSIONPROCESS_HPP */
