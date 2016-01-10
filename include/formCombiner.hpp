/*!
 * class FORMCOMBINER
 *
 * Checks if a specified form can be aligned with any other form (or a specified second form) such that their combined bounding box has better space utilization than the two original bounding boxes.
 * Can create instances of AbstractFormMulti
 */

#ifndef FORMCOMBINER_H
#define FORMCOMBINER_H

#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "abstractFormConfigurationTuple.hpp"
#include "problem.hpp"
#include "pointSetAlgorithms.hpp"

#include <iterator>
#include <vector>

class AbstractFormConfigurationTuple;

using namespace std;

class FormCombiner
{
private:
	/*!
	 *  Two AbstractFormConfigurations for which an optimized Tuple should be computed.
	 */
	AbstractFormConfiguration *form_config_1;

	/*!
	 *  Two AbstractFormConfigurations for which an optimized Tuple should be computed.
	 */
	AbstractFormConfiguration *form_config_2;

	/*!
	 *  A pointer to the problem. Needed to decide if a combined form still fits on plane.
	 */
	Problem* problem;
public:
	/*!
	 *  Default Constructor
	 */
	FormCombiner(Problem *p, AbstractFormConfiguration *form_config_1, AbstractFormConfiguration *form_config_2);

	/*!
	 *  Compute optimal configuration for the two AbstractForms and creates an AbstractFormConfigurationTuple
	 *
	 *  @return 	the constructed AbstractFormConfigurationTuple, or Null if no efficient combination was found
	 */
	AbstractFormConfigurationTuple compute_optimal_configuration();
};

#endif