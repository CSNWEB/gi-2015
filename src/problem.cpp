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