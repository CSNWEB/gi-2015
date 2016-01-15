#include "problem.hpp"

#ifdef DEBUG
    #define DEBUG_P
#endif

Problem::Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms, vector<string> name_forms)
{
	#ifdef DEBUG_P
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	size_of_sheet_x 			= sx;
	size_of_sheet_y 			= sy;
	abstract_forms 				= abst_forms;
	number_of_different_forms 	= abstract_forms.size();
	number_of_forms_needed 		= num_of_forms;
    name_of_forms               = name_forms;
}

Problem::Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms)
{
    #ifdef DEBUG_P
        printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
    #endif
        
    size_of_sheet_x             = sx;
    size_of_sheet_y             = sy;
    abstract_forms              = abst_forms;
    number_of_different_forms   = abstract_forms.size();
    number_of_forms_needed      = num_of_forms;
}

void Problem::check_if_solveable()
{
    #ifdef DEBUG_P
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif

    for (int index_of_form = 0; index_of_form < abstract_forms.size(); ++index_of_form)
    {
        #ifdef DEBUG_P
            printf("Check if form %i fits on plane.\n", index_of_form);
        #endif

        abstract_forms[index_of_form]._d_print_abstract_form();

        float optimal_rotation_by_convex_hull;
        bool optimal_rotation_is_legal = abstract_forms[index_of_form].find_rotation_with_minimum_bounding_box_and_check_if_legal(size_of_sheet_x, size_of_sheet_y, optimal_rotation_by_convex_hull);

        abstract_forms[index_of_form]._d_print_abstract_form();

        if (optimal_rotation_is_legal)
        {   
            abstract_forms[index_of_form].rotate_form_by_degrees(optimal_rotation_by_convex_hull);
        
            abstract_forms[index_of_form].normalize_position(size_of_sheet_x, size_of_sheet_y);

            #ifdef DEBUG_P
                printf("After rotating by %.2f degrees, form %i fits optimized on given plane dimensions.\n", optimal_rotation_by_convex_hull, index_of_form);
            #endif
        }
        else
        {
            int optimal_rotation = abstract_forms[index_of_form].check_for_optimal_legal_rotation(size_of_sheet_x, size_of_sheet_y);

            if (optimal_rotation < 0)
            {
                #ifdef DEBUG_P
                    printf("Form %i does not fit on given plane dimensions.\n", index_of_form);
                #endif

                too_large_forms.push_back(index_of_form);
            }
            else
            {
                abstract_forms[index_of_form].rotate_form_by_degrees(optimal_rotation);
                abstract_forms[index_of_form].normalize_position(size_of_sheet_x, size_of_sheet_y);

                #ifdef DEBUG_P
                    printf("After rotating by %i degrees, form %i fits optimized on given plane dimensions.\n", optimal_rotation, index_of_form);
                #endif
            }

        }
    }
}

int Problem::get_total_number_of_all_forms()
{
	#ifdef DEBUG_P
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int sum = 0;
	for (int i=0; i<number_of_forms_needed.size(); ++i)
		sum += number_of_forms_needed[i];

	return sum;
}

int Problem::get_number_of_different_forms()
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return number_of_different_forms;
}

int Problem::get_number_of_form_needed(int i)
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    if (i>=0 && i<number_of_different_forms)
        return number_of_forms_needed[i];
    else return 0;
}

string Problem::get_name_of_form(int i)
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    if (i>=0 && i<number_of_different_forms)
        return name_of_forms[i];
    else return 0;
}

float Problem::get_plane_width()
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return size_of_sheet_x;
}

float Problem::get_plane_height()
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    return size_of_sheet_y;
}

bool Problem::is_solveable()
{
    too_large_forms.clear();
    check_if_solveable();
    return too_large_forms.size() == 0;
}

AbstractForm* Problem::get_abstract_form_at_position(int i)
{
    #ifdef DEBUG_P
        printf("GETTER: %s\n", __PRETTY_FUNCTION__);
    #endif

    if (i >= 0 && i < number_of_different_forms)
        return &abstract_forms[i];
    else return 0;
}


void Problem::set_plane_width(float width){
    size_of_sheet_x = width;
}

void Problem::set_plane_height(float height){
    size_of_sheet_y = height;
}

void Problem::add_abstract_form(string name, AbstractForm form){
    abstract_forms.push_back(form);
    ++number_of_different_forms;
    number_of_forms_needed.push_back(0);
    name_of_forms.push_back(name);
}

void Problem::rename_abstract_form(int i, string name)
{
    if(i < number_of_different_forms){
        name_of_forms[i] = name;
    }
}

void Problem::erase_abstract_form(int i){
    abstract_forms.erase(abstract_forms.begin() + i);
    --number_of_different_forms;
    number_of_forms_needed.erase(number_of_forms_needed.begin() +i);
    name_of_forms.erase(name_of_forms.begin() +i);
}

void Problem::set_amount_of_form(int i, int amount)
{
    if(i >= 0 && i < number_of_forms_needed.size()){
        number_of_forms_needed[i] = amount;
    }
}
