#ifndef _ALL_MARIAN
#define _ALL_MARIAN

/** \defgroup diffusion Diffusion 
 * \brief Object used to model diffusion process
 *
 * To this module we assign objects that are related to diffusion.  
 */
#include <diffusion/convectionDiffusionProcess.hpp>
#include <diffusion/backwardKolmogorovEq.hpp>
#include <diffusion/forwardKolmogorovEq.hpp>

/** \defgroup fdm Finite Difference Method 
 * \brief Building blocks of FDM solver
 *
 * To achieve flexibility of FDM solver algorithm we need to construct building blocks that can be freely interchangeable.
 *  
 */
#include <FDM/tridiagonalOperator.hpp>
#include <FDM/tridiagonalSolver.hpp>
#include <FDM/LUSolver.hpp>

/** \defgroup boundary Boundary Conditions 
 * \ingroup fdm
 * \brief Boundary conditions for PDE
 */
#include <FDM/boundaryConditions/boundaryCondition.hpp>
#include <FDM/boundaryConditions/dirichletBoundaryCondition.hpp>

/** \defgroup grid Grid builders
 * \ingroup fdm
 * \brief Classes used generate grid for PDE solver
 */
#include <FDM/gridBuilders/gridBuilder.hpp>
#include <FDM/gridBuilders/uniformGridBuilder.hpp>
#include <FDM/gridBuilders/hsineGridBuilder.hpp>

/** \defgroup schemes Differentiating schemes
 * \ingroup fdm
 * \brief Schemes for numerical solver
 * 
 */

#include <FDM/schemes/fdScheme.hpp>
#include <FDM/schemes/explicitScheme.hpp>
#include <FDM/schemes/implicitScheme.hpp>
#include <FDM/schemes/crankNicolsonScheme.hpp>
 
/** \defgroup fin Financial engineering 
 * \brief General financial engineering objects
 */
#include <financial/market.hpp>
#include <financial/analyticPricer.hpp>
#include <financial/FdmPricer.hpp>
/** \defgroup gridrange Grid Ranges
 * \ingroup fin
 * \brief Object helping in construction of FDM problem for option pricing 
 */
 
#include <financial/gridRange/rangeSetup.hpp>
#include <financial/gridRange/spotRelatedRange.hpp>

/** \defgroup option Financial options
 * \ingroup fin 
 * \brief Options and pricer factories
 */
 
#include <financial/options/option.hpp>
#include <financial/options/euroOpt.hpp>
#include <financial/options/pricerAbstractFactory.hpp>
#include <financial/options/euroOptFactory.hpp>

/** \defgroup utils Utils 
 * \brief Small classes and routines used in project
 */
#include <utils/smartPointer.hpp>
#include <utils/dataFrame.hpp>
#include <utils/utils.hpp>
#include <utils/mathUtils.hpp>

#endif /* _ALL_MARIAN*/

