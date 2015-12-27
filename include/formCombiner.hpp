/*!
 * class FORMCOMBINER
 *
 * Checks if a specified form can be aligned with any other form (or a specified second form) such that their combined bounding box has better space utilization than the two original bounding boxes.
 * Can create instances of AbstractFormMulti
 */

#ifndef FORMCOMBINER_H
#define FORMCOMBINER_H

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
	 *  A pointer to the second AbstractForm
	 */
	AbstractForm* abstract_form_2;


public:
	/*!
	 *  Default Constructor
	 */
	FormCombiner(Problem *problem, AbstractForm* abstract_form);

	/*!
	 *  Search all other forms for optimal configurated tuple
	 */
	ReturnType search_for_optimal_configuratioon_global();

	/*!
	 *  Search for optimal configuration with specific form
	 */
	ReturnType search_for_optimal_configuratioon_local(AbstractForm* other_form);

};

#endif