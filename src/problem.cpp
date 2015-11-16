#include "problem.hpp"

Problem::Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: Problem\n");
	#endif
		
	size_of_sheet_x 			= sx;
	size_of_sheet_y 			= sy;
	abstract_forms 				= abst_forms;
	number_of_different_forms 	= abstract_forms.size();
	number_of_forms_needed 		= num_of_forms;

	//number_of_planes 			= 0;
	planes  					= vector<Plane>();
}

void Problem::create_initial_setting()
{
	#ifdef DEBUG
		printf("FUNCTION: Problem::create_initial_setting\n");
	#endif

	for (int i=0; i<number_of_different_forms; ++i)
	{
		for (int j=0; j<number_of_forms_needed[i]; ++j)
		{
			Plane newplane = Plane(size_of_sheet_x, size_of_sheet_y);
			newplane.add_form_at_position(&abstract_forms[i], 0,0);
			planes.push_back(newplane);
		}
	}
}

void Problem::create_setting_2BPRG()
{
	/*
		TO DO:
		1) sort forms by bounding box (smaller edge)
		2) for each form (in ascending order)
			2.1) check all existing strips (ordered by time of creation), take the first that has enoug space to fit current form
				-> add form to strip
			2.2) if no strip has sufficient space left, check on all existing planes if there is enough space left to create a new strip for current form
				-> create new strip, place form on strip
			2.3) if no plane has sufficient space, create new plane, create new stripp, place form.

		A strip is a list of indices of forms, and 4 additional values:
		- an index of a plane
		- the y-offset of this strip from the top of the plane
		- the height of the strip (i.e. the maximum of the heights of the forms on this strip)
		- the remaining width on the strip (i.e. the width of the plane minus the sum of the width of all forms on the strip)
	*/
}

float Problem::get_total_utilization()
{
	#ifdef DEBUG
		printf("FUNCTION: Problem::get_total_utilization\n");
	#endif

	float utilization = 0;

	for (int i=0; i<planes.size(); ++i)
		utilization += planes[i].compute_utilization();

	utilization /= planes.size();

	#ifdef DEBUG
		printf("Total utilization is: %.2f\n", utilization);
	#endif
	
	return utilization;
}