#include "setting.hpp"

Setting::Setting(Problem *p)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: Setting::Setting(Problem *p)\n");
	#endif

	problem = p;

	planes = vector<Plane>();
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