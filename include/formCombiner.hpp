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

//#include <list>
#include <iterator>
#include <vector>

class AbstractFormConfigurationTuple;

using namespace std;

class FormCombiner
{
private:
	/*!
	 *
	 */
	AbstractFormConfiguration *form_config_1;

	AbstractFormConfiguration *form_config_2;

	/*!
	 *  A pointer to the problem. Needed to decide if a combined form still fits on plane.
	 */
	Problem* problem;

	/*!
	 *  A pointer to the first AbstractForm
	 */
	//AbstractForm* abstract_form_1;

	/*!
	 *  A list of possible AbstractFormConfigurations, sorted by optimality of area utilization of the bounding box
	 */
	//list<AbstractFormConfigurationTuple> possible_configurations;

public:
	/*!
	 *  Default Constructor
	 */
	FormCombiner(Problem *p, AbstractFormConfiguration *form_config_1, AbstractFormConfiguration *form_config_2);

	/*!
	 *  Search all other forms for optimal configurated tuple
	 */
	//void search_for_optimal_configuratioon_global();

	/*!
	 *  Compute optimal configuration for the two AbstractForms and creates an AbstractFormConfigurationTuple
	 *
	 *  @return 	the constructed AbstractFormConfigurationTuple, or Null if no efficient combination was found
	 */
	AbstractFormConfigurationTuple compute_optimal_configuration();

	/*!
	 *  Get the best AbstractFormConfiguration that does not use any AbstractForm from a given vector
	 */
	//AbstractFormConfigurationTuple get_best_tuple(vector<int> forbidden_forms);

};

#endif