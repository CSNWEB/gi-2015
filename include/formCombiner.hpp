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
#include "problem.hpp"

#include <list>
#include <iterator>
#include <vector>

using namespace std;

class FormCombiner
{
private:
	/*!
	 *  A pointer to the problem. Needed to decide if a combined form still fits on plane.
	 */
	Problem* problem;

	/*!
	 *  A pointer to the first AbstractForm
	 */
	AbstractForm* abstract_form_1;

	/*!
	 *  A list of possible AbstractFormConfigurations, sorted by optimality of area utilization of the bounding box
	 */
	list<AbstractFormConfiguration> possible_configurations

public:
	/*!
	 *  Default Constructor
	 */
	FormCombiner(Problem *problem, AbstractForm* abstract_form);

	/*!
	 *  Search all other forms for optimal configurated tuple
	 */
	void search_for_optimal_configuratioon_global();

	/*!
	 *  Search for optimal configuration with a specific form. The found configuration is added to the list possible_configurations
	 */
	void search_for_optimal_configuratioon_local(AbstractForm* other_form);

	/*!
	 *  Get the best AbstractFormConfiguration that does not use any AbstractForm from a given vector
	 */
	AbstractFormConfiguration get_best_configuration(vector<int> forbidden_forms);

};

#endif