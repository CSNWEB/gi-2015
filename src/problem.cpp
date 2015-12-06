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

    check_if_solveable();

	//number_of_planes 			= 0;
	//planes  					= vector<Plane>();
}

void Problem::check_if_solveable()
{
    #ifdef DEBUG
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif

    for (int index_of_form = 0; index_of_form < abstract_forms.size(); ++index_of_form)
    {
        #ifdef DEBUG
            printf("Check if form %i fits on plane.\n", index_of_form);
        #endif

        int optimal_rotation = abstract_forms[index_of_form].check_for_optimal_legal_rotation(size_of_sheet_x, size_of_sheet_y);
        if (optimal_rotation < 0)
        {
            #ifdef DEBUG
                printf("Form %i does not fit on given plane dimensions.\n", index_of_form);
            #endif

            too_large_forms.push_back(index_of_form);
        }
        else
        {
            #ifdef DEBUG
                printf("After rotating by %i degrees, form %i fits optimized on given plane dimensions.\n", optimal_rotation, index_of_form);
            #endif

            abstract_forms[index_of_form].rotate_form_by_degrees(optimal_rotation);
            abstract_forms[index_of_form].normalize_position(size_of_sheet_x, size_of_sheet_y);
        }
    }
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

float Problem::get_plane_width()
{
    #ifdef DEBUG
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return size_of_sheet_x;
}

float Problem::get_plane_height()
{
    #ifdef DEBUG
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return size_of_sheet_y;
}

bool Problem::is_solveable()
{
    return too_large_forms.size() == 0;
}

AbstractForm* Problem::get_abstract_form_at_position(int i)
{
    #ifdef DEBUG
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    if (i >= 0 && i < number_of_different_forms)
        return &abstract_forms[i];
    else return 0;
}