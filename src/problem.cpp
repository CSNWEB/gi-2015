#include "problem.hpp"

Problem::Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	size_of_sheet_x 			= sx;
	size_of_sheet_y 			= sy;
	abstract_forms 				= abst_forms;
	number_of_different_forms 	= abstract_forms.size();
	number_of_forms_needed 		= num_of_forms;

	//number_of_planes 			= 0;
	//planes  					= vector<Plane>();
}

int Problem::get_total_number_of_all_forms()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int sum = 0;
	for (int i=0; i<number_of_forms_needed.size(); ++i)
		sum += number_of_forms_needed[i];

	return sum;
}

/*
void Problem::create_setting_2BPRG()
{

		TO DO:
		1) sort forms by bounding box (smaller edge)
		2) for each form (in ascending order)
			2.1) check all existing shelfs (ordered by time of creation), take the first that has enoug space to fit current form
				-> add form to shelf
			2.2) if no shelf has sufficient space left, check on all existing planes if there is enough space left to create a new shelf for current form
				-> create new shelf, place form on shelf
			2.3) if no plane has sufficient space, create new plane, create new shelf, place form.

		A shelf is a list of indices of forms, and 4 additional values:
		- an index of a plane
		- the y-offset of this shelf from the top of the plane
		- the height of the shelf (i.e. the maximum of the heights of the forms on this shelf)
		- the remaining width on the shelf (i.e. the width of the plane minus the sum of the width of all forms on the shelf)
	
}
*/
