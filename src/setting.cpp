#include "setting.hpp"

Setting::Setting(Problem *p)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: Setting::Setting(Problem *p)\n");
	#endif

	problem = p;

	planes = vector<Plane>();

	missing_forms = vector<int>(problem->get_number_of_different_forms());
	for (int i=0; i<missing_forms.size(); ++i)
		missing_forms[i] = problem->get_number_of_form_needed(i);
}


float Setting::get_total_utilization()
{
	#ifdef DEBUG
		printf("FUNCTION: Setting::get_total_utilization\n");
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

void Setting::create_initial_setting()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int number_of_planes = 0;
	for (int i=0; i<problem->get_number_of_different_forms(); ++i)
		number_of_planes += problem->get_number_of_form_needed(i);
	planes = vector<Plane>(number_of_planes);

	missing_forms = vector<int>(problem->get_number_of_different_forms(), 0);

	int k=0;

	for (int i=0; i<problem->get_number_of_different_forms(); ++i)
	{
		for (int j=0; j<problem->get_number_of_form_needed(i); ++j)
		{
			planes[k] = Plane(problem->get_plane_width(), problem->get_plane_height());
			planes[k].add_form_at_position(problem->get_abstract_form_at_position(i), 0,0);

			k++;

			#ifdef DEBUG
				printf("check edges in %s\n", __PRETTY_FUNCTION__);
				planes[k-1].get_form_at(0)->_d_print_edges_to_console();
			#endif
		}
	}
}

void Setting::add_plane()
{
	#ifdef DEBUG
		printf("FUNCITON: %s\n", __PRETTY_FUNCTION__);
	#endif

	planes.push_back(Plane(problem->get_plane_width(), problem->get_plane_height()));
}

int Setting::get_number_of_planes()
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif
		
    return planes.size();
}

int Setting::get_number_of_missing_pieces_of_form(int form_index)
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	int current_number_of_forms = 0;
	for (int current_plane = 0; current_plane < get_number_of_planes(); ++current_plane)
	{
		for (int current_form = 0; current_form < planes[current_plane].get_number_of_forms(); ++current_form)
		{
			if (planes[current_plane].get_form_at(current_form)->get_mother()->get_id() == form_index)
				current_number_of_forms++;
		}
	}

	return get_problem()->get_number_of_form_needed(form_index)-current_number_of_forms;
}