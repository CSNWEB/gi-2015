#include "problem.hpp"

Problem::Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms)
{
	size_of_sheet_x 			= sx;
	size_of_sheet_y 			= sy;
	abstract_forms 				= abst_forms;
	number_of_different_forms 	= abstract_forms.size();
	number_of_forms_needed 		= num_of_forms;

	number_of_planes 			= 0;
	planes  					= list<Plane>();
}

void Problem::create_initial_setting()
{
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