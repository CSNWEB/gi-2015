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

int Problem::get_number_of_different_forms()
{
    #ifdef DEBUG
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return number_of_different_forms;
}

int Problem::get_number_of_form_needed(int i)
{
    #ifdef DEBUG
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    if (i>=0 && i<number_of_different_forms)
        return number_of_forms_needed[i];
    else return 0;
}