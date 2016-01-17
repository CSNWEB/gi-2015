#include "binPacking.hpp"

#ifdef DEBUG
	#define DEBUG_BP
#endif

BinPacking::BinPacking(Problem &p): problem(p), setting(&problem)
{
	#ifdef DEBUG_BP
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	is_initialized = false;
	index_of_current_tuple = -1;

	minimum_height_of_any_tuple = -1;

	number_of_different_forms = problem.get_number_of_different_forms();

	int n =  number_of_different_forms;
	if (n < 10)
		n = 10;
	all_single_form_tuples.reserve(n);
	all_efficient_form_tuples.reserve((n/2 * (n+1)) + n);
	all_form_tuples_to_use.reserve((n/2 * (n+1)) + n);
	all_tuples_to_use_sorted_by_size.reserve((n/2 * (n+1)) + n);

	bp_planes.reserve(n/2);
	bp_shelves.reserve(n/2);
}

void BinPacking::update_problem(Problem &new_problem)
{
	problem = new_problem;
	is_initialized = false;
	index_of_current_tuple = -1;

	minimum_height_of_any_tuple = -1;

	number_of_different_forms = problem.get_number_of_different_forms();

	int n =  number_of_different_forms;
	if (n < 10)
		n = 10;

	all_single_form_tuples.clear();
	all_single_form_tuples.reserve(n);

	all_efficient_form_tuples.clear();
	all_efficient_form_tuples.reserve((n/2 * (n+1)) + n);

	all_form_tuples_to_use.clear();
	all_form_tuples_to_use.reserve((n/2 * (n+1)) + n);

	all_tuples_to_use_sorted_by_size.clear();
	all_tuples_to_use_sorted_by_size.reserve((n/2 * (n+1)) + n);

	bp_planes.clear();
	bp_planes.reserve(n/2);

	bp_shelves.clear();
	bp_shelves.reserve(n/2);
}

void BinPacking::create_configuration_tuples()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	AbstractFormConfiguration form_config_1;
	AbstractFormConfiguration form_config_2;

	for (int index_form_1 = 0; index_form_1 < number_of_different_forms; ++index_form_1)
	{
		#ifdef DEBUG_BP
			printf("Consider the next form:\n");
			problem.get_abstract_form_at_position(index_form_1)->_d_print_abstract_form();
		#endif

		form_config_1 = AbstractFormConfiguration(problem.get_abstract_form_at_position(index_form_1), problem.get_number_of_form_needed(index_form_1));

		AbstractFormConfigurationTuple simple_tuple(form_config_1);

		all_single_form_tuples.push_back(simple_tuple);

		#ifdef DEBUG_BP
			printf("Created simple tuple based on form at index %i\n", index_form_1);
		#endif

		// if the current form has bad area utilization iterate through all forms and optimal configuration of each tuple:
		if (GlobalParams::do_pre_merge_merge())
		{	
			for (int index_form_2 = index_form_1; index_form_2 < number_of_different_forms; ++index_form_2)
			{
				#ifdef DEBUG_BP
					printf("Next configuration: %i-%i\n", index_form_1, index_form_2);
				#endif

				if ((index_form_2 != index_form_1 || problem.get_number_of_form_needed(index_form_1) > 1) &&
					problem.get_abstract_form_at_position(index_form_1)->optimal_rotation_is_legal() &&
					problem.get_abstract_form_at_position(index_form_2)->optimal_rotation_is_legal())
				{
					#ifdef DEBUG_BP
						printf("Start computing optimal configuration for case %i-%i\n", index_form_1, index_form_2);
					#endif

					form_config_2 = AbstractFormConfiguration(problem.get_abstract_form_at_position(index_form_2), problem.get_number_of_form_needed(index_form_2));

					// compute area utilization. if good enough, skip merging:
					float utilization_of_unmerged_configuration = 
						(form_config_1.get_used_area()/(form_config_1.get_dx() * form_config_1.get_dy()) +
						(form_config_2.get_used_area()/(form_config_2.get_dx() * form_config_2.get_dy()) )) / 2.0;

					if ((1.0 - utilization_of_unmerged_configuration) >GlobalParams::get_tolerance())
					{
						FormCombiner fc(form_config_1, form_config_2);

						AbstractFormConfigurationTuple new_tuple = 	fc.get_optimal_configured_tuple();

						if (new_tuple.get_number_of_forms() > 1)
						{
							all_efficient_form_tuples.push_back(new_tuple);
		
							#ifdef DEBUG_BP
								printf("Added new tuple to all_efficient_form_tuples\n");
							#endif						
						}
						else
						{
							#ifdef DEBUG_BP
								printf("Tuple was not added to all_efficient_form_tuples\n");
							#endif
						}
					}
					else
					{
						#ifdef DEBUG_BP
							printf("No tuple was created because unmerged area utilization was sufficient good.\n");
						#endif
					}
				}
				else
				{
					#ifdef DEBUG_BP
						printf("Current pair %i / %i is not considered\n", index_form_1, index_form_2);
					#endif
				}
			}
		}

		#ifdef DEBUG_BP
			printf("All created tuples:\n");
			for (unsigned int i=0; i < all_efficient_form_tuples.size(); ++i)
			{
				printf("\t%i : %s\n", i, all_efficient_form_tuples[i].to_string().c_str());
			}
			for (unsigned int i=0; i < all_single_form_tuples.size(); ++i)
			{
				printf("\t%i : %s\n", i, all_single_form_tuples[i].to_string().c_str());
			}
		#endif
	}
}

void BinPacking::create_all_tuples_to_use()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// sort all efficient tuples, if at least twi have been constructed
	if (all_efficient_form_tuples.size() > 1)
	{
		TupleComparatorUtilization tcu(&all_efficient_form_tuples);
		std::sort(all_efficient_form_tuples.begin(), all_efficient_form_tuples.end(), tcu);
	}

	// after sorting, append single-form-tuples at the end:
	all_efficient_form_tuples.insert(all_efficient_form_tuples.end(), all_single_form_tuples.begin(), all_single_form_tuples.end());

	// delete vector all_single_form_tuples:
	all_single_form_tuples.clear();
	all_single_form_tuples.shrink_to_fit();

	#ifdef DEBUG_BP
		printf("all efficient tuples sorted:\n");
		for (unsigned int i=0; i < all_efficient_form_tuples.size(); ++i)
		{
			printf("\t%i with efficiency %.2f\n", i, all_efficient_form_tuples[i].get_utilization());
			printf("\t%s", all_efficient_form_tuples[i].to_string().c_str());
		}
	#endif

	int total_number_of_all_form_tuples = all_efficient_form_tuples.size();

	for (int tuple_index=0; tuple_index<total_number_of_all_form_tuples; ++tuple_index)
	{
		// init the number of usages:
		int use_number = -1;

		// check if tuple has only single form or is small enough to fit on a plane:
		if ((all_efficient_form_tuples[tuple_index].get_number_of_forms() < 2) ||
			(all_efficient_form_tuples[tuple_index].get_dx() - problem.get_plane_width()< GlobalParams::get_tolerance() &&
			all_efficient_form_tuples[tuple_index].get_dy() - problem.get_plane_height()< GlobalParams::get_tolerance()) ||
			(all_efficient_form_tuples[tuple_index].get_dy() - problem.get_plane_width() < GlobalParams::get_tolerance() &&
			all_efficient_form_tuples[tuple_index].get_dx() - problem.get_plane_height()< GlobalParams::get_tolerance()))
		{
			vector<int> ids_of_forms_used_in_tuple(0);
			int maximum_amount_of_forms_used = 1;
			for (int form_index = 0; form_index < all_efficient_form_tuples[tuple_index].get_number_of_forms(); ++form_index)
			{
				int current_form_id = all_efficient_form_tuples[tuple_index].get_configuration_of_form(form_index)->get_id_of_form();
				int current_form_amount = number_of_forms_needed[current_form_id];

				bool id_not_found = true;
				for (int i=0; i<ids_of_forms_used_in_tuple.size() && id_not_found; ++i)
					if (ids_of_forms_used_in_tuple[i] == current_form_id)
					{
						id_not_found = false;
						maximum_amount_of_forms_used++;
					}
				if (id_not_found)
					ids_of_forms_used_in_tuple.push_back(current_form_id);

				if (use_number == -1)
					use_number = current_form_amount;
				else if (current_form_amount < use_number)
					use_number = current_form_amount;

				#ifdef DEBUG_BP
					printf("Considering form %i of tuple %i:\n", form_index, tuple_index);
					printf("\tHas id: %i and amount: %i\n", current_form_id, current_form_amount);
				#endif
			}

			use_number /= maximum_amount_of_forms_used;

			if (use_number > 0)
			{
				for (int form_index = 0; form_index < all_efficient_form_tuples[tuple_index].get_number_of_forms(); ++form_index)
				{
					number_of_forms_needed[all_efficient_form_tuples[tuple_index].get_configuration_of_form(form_index)->get_id_of_form()] -= use_number;
				}
				all_efficient_form_tuples[tuple_index].set_number_of_usages(use_number);
				all_form_tuples_to_use.push_back(all_efficient_form_tuples[tuple_index]);
			}
		}
	}

	#ifdef DEBUG_BP
		printf("Finished initializing vector all_form_tuples_to_use:\n\tsize: %i\n", all_form_tuples_to_use.size());
		for (unsigned int i=0; i<all_form_tuples_to_use.size(); ++i)
			printf("\t%i: %s - amount: %i\n", i, all_form_tuples_to_use[i].to_string().c_str(), all_form_tuples_to_use[i].get_number_of_usages());
	#endif
}

void BinPacking::initialize_algorithm()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif

    if(number_of_different_forms == 0){
        return;
    }
	
	init_number_of_forms();

	create_configuration_tuples();

	create_all_tuples_to_use();
	
	create_initial_sorting();

	if (all_form_tuples_to_use.size() == 0)
		minimum_height_of_any_tuple = 0;
	else
		minimum_height_of_any_tuple = all_form_tuples_to_use[all_tuples_to_use_sorted_by_size[all_form_tuples_to_use.size()-1]].get_dy();

	index_of_current_tuple = 0;

	bp_planes = vector<BinPackingPlane>();

	is_initialized = true;
}

void BinPacking::init_number_of_forms()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<number_of_different_forms; ++i)
		{
			number_of_forms_needed[problem.get_abstract_form_at_position(i)->get_id()] = problem.get_number_of_form_needed(i);

			#ifdef DEBUG_BP
				printf("\tInitialized number_of_forms_needed[%i] = %i\n", problem.get_abstract_form_at_position(i)->get_id(), number_of_forms_needed[problem.get_abstract_form_at_position(i)->get_id()]);
			#endif
		}
}

void BinPacking::create_initial_sorting()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	all_tuples_to_use_sorted_by_size = vector<int>(0);

	for (unsigned int tuple_index = 0; tuple_index < all_form_tuples_to_use.size(); ++tuple_index)
	{
		for (int tuple_number = 0; tuple_number < all_form_tuples_to_use[tuple_index].get_number_of_usages(); ++tuple_number)
		{
			all_tuples_to_use_sorted_by_size.push_back(tuple_index);
		}
	}
	int total_number_of_all_form_tuples_to_use = all_tuples_to_use_sorted_by_size.size();

	#ifdef DEBUG_BP
		printf("Finished initializing all_tuples_to_use_sorted_by_size:\n");
		for (unsigned int i=0; i < all_tuples_to_use_sorted_by_size.size(); ++i)
			printf("\tForm at position %i: %i\n", i, all_tuples_to_use_sorted_by_size[i]);
	#endif

	TupleComparatorDimension tcd(&all_form_tuples_to_use);
	std::sort(all_tuples_to_use_sorted_by_size.begin(), all_tuples_to_use_sorted_by_size.end(), tcd);

	#ifdef DEBUG_BP
		printf("All_tuples_to_use_sorted_by_size:\n");
		for (unsigned int i=0; i < all_tuples_to_use_sorted_by_size.size(); ++i)
			printf("\tTuple at position %i: %i\n", i, all_tuples_to_use_sorted_by_size[i]);
	#endif
}

bool BinPacking::create_packed_setting()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		bool stop_each_step = true;
	#endif

	int iteration = 0;

	if (!problem.is_solveable())
	{
		#ifdef DEBUG_BP
			printf("ERROR: No Setting created because problem is not solveable.\n");
		#endif

		return false;
	}

	while(next_step_of_algorithm())
	{
		++iteration;

		#ifdef DEBUG_BP
			//char t;
			printf("\n--- Iteration %i of %s finished ---\n\n", iteration, __PRETTY_FUNCTION__);
			if (stop_each_step)
			{
				//printf("- press [enter] to proceed or [q] + [enter] to finish computation -\n\n");
				//scanf("%c", &t);
				//if (t == 'q')
					stop_each_step = false;
			}
		#endif
	}

	#ifdef DEBUG_BP
		printf("\n--- Function %s finished ---\n\n", __PRETTY_FUNCTION__);
	#endif

	return true;
}

bool BinPacking::next_step_of_algorithm()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (!is_initialized)
		initialize_algorithm();

	if(all_tuples_to_use_sorted_by_size.size() == 0){
        #ifdef DEBUG_BP
            printf("ERROR: No Forms in Problem.\n");
        #endif

        return false;
    }

	if (get_number_of_missing_tuples() > 0)
	{
		AbstractFormConfigurationTuple *current_tuple = &all_form_tuples_to_use[all_tuples_to_use_sorted_by_size[index_of_current_tuple]];

		//printf("%s\n",current_tuple->to_string().c_str());

		if (!try_add_form_configuration_tuple_on_existing_shelf(*current_tuple))
			add_form_configuration_tuple_on_new_shelf(*current_tuple);

		index_of_current_tuple++;

		return true;
	}

	return false;

}

bool BinPacking::try_add_form_configuration_tuple_on_existing_shelf(AbstractFormConfigurationTuple &tuple)
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bool tuple_added_successfully = false;

	for (unsigned int shelf_index=0; shelf_index < bp_shelves.size() && !tuple_added_successfully; ++shelf_index)
	{
		// try to add tuple:
		float result = bp_shelves[shelf_index].try_add_form_config_tuple(tuple);

		if (result >= 0)
		{
			tuple_added_successfully = true;

			// add all configurations of tuple to setting:
			float x_offset_on_plane = bp_shelves[shelf_index].get_offset_x();
			float y_offset_on_plane = bp_shelves[shelf_index].get_offset_y();

			int index_of_plane = bp_shelves[shelf_index].get_plane();

			float x_offset_on_shelf = bp_shelves[shelf_index].get_width() - bp_shelves[shelf_index].get_remaining_width() - tuple.get_dx();

			add_form_config_tuple_to_setting(
				tuple,
				index_of_plane,
				x_offset_on_plane + x_offset_on_shelf,
				y_offset_on_plane
				);

			// add subshelf:
			if (result + GlobalParams::get_tolerance() > minimum_height_of_any_tuple)
				create_subshelf(shelf_index, tuple, result);
			
		}
	}

	return tuple_added_successfully;
}

void BinPacking::add_form_configuration_tuple_on_new_shelf(AbstractFormConfigurationTuple &tuple)
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bool form_added_successfully = false;
	float height_of_tuple = tuple.get_dy();

	for (unsigned int plane_index = 0; plane_index < bp_planes.size() && !form_added_successfully; ++plane_index)
	{
		if (bp_planes[plane_index].get_remaining_height() + GlobalParams::get_tolerance() > height_of_tuple)
		{
			float offset_x = 0;
			float offset_y = problem.get_plane_height()-bp_planes[plane_index].get_remaining_height();
			float size_x   = problem.get_plane_width();
			float size_y   = height_of_tuple;

			#ifdef DEBUG_BP
				printf("Create new shelf on existing plane.\n\toff_x = %.2f, off_y = %.2f\n\ts_x = %.2f, s_y = %.2f\n",offset_x, offset_y, size_x, size_y);
			#endif

			create_shelf(plane_index, size_x, size_y, offset_x, offset_y);
			bool success = bp_planes[plane_index].add_shelf(height_of_tuple);

			// size() > 0 because a new shelf was added in the line above
			bp_shelves[bp_shelves.size()-1].try_add_form_config_tuple(tuple);

			// add form to setting:
			add_form_config_tuple_to_setting(tuple, plane_index, offset_x, offset_y);

			form_added_successfully = true;
		}
	}

	if (!form_added_successfully)
	{
		#ifdef DEBUG_BP
			printf("No new shelf on any existing plane could be created to hold the tuple.\nAdd new Plane\n");
		#endif

		bp_planes.push_back(BinPackingPlane(problem.get_plane_width(), problem.get_plane_height()));

		// size() > 0 because a new plane was added
		int plane_index = bp_planes.size()-1;

		#ifdef DEBUG_BP
			printf("\tNew plane created with index %i\n", plane_index);
		#endif

		create_shelf(plane_index, problem.get_plane_width(), height_of_tuple, 0, 0);
			
		bp_planes[plane_index].add_shelf(height_of_tuple);

		bp_shelves[bp_shelves.size()-1].try_add_form_config_tuple(tuple);

		// add form to setting:
		setting.add_plane();
		add_form_config_tuple_to_setting(tuple, plane_index, 0, 0);

		form_added_successfully = true;
	}
}

void BinPacking::create_shelf(int index_of_mothershelf, float size_x, float size_y, float offset_x, float offset_y)
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bp_shelves.push_back(BinPackingShelf(index_of_mothershelf, size_x, size_y, offset_x, offset_y));
}

void BinPacking::create_subshelf(int index_of_mothershelf, AbstractForm &form_on_top, float remaining_height)
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int plane_index = bp_shelves[index_of_mothershelf].get_plane();
	float offset_x  = bp_shelves[index_of_mothershelf].get_offset_x() + bp_shelves[index_of_mothershelf].get_width() - bp_shelves[index_of_mothershelf].get_remaining_width() - form_on_top.get_dx();
	float offset_y  = bp_shelves[index_of_mothershelf].get_offset_y() + form_on_top.get_dy();
	float size_x    = form_on_top.get_dx();
	float size_y    = remaining_height;

	create_shelf(plane_index, size_x, size_y, offset_x, offset_y);
}

void BinPacking::create_subshelf(int index_of_mothershelf, AbstractFormConfigurationTuple &tuple_on_top, float remaining_height)
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int plane_index = bp_shelves[index_of_mothershelf].get_plane();
	float offset_x  = bp_shelves[index_of_mothershelf].get_offset_x() + bp_shelves[index_of_mothershelf].get_width() - bp_shelves[index_of_mothershelf].get_remaining_width() - tuple_on_top.get_dx();
	float offset_y  = bp_shelves[index_of_mothershelf].get_offset_y() + tuple_on_top.get_dy();
	float size_x    = tuple_on_top.get_dx();
	float size_y    = remaining_height;

	create_shelf(plane_index, size_x, size_y, offset_x, offset_y);
}

int BinPacking::get_number_of_missing_tuples()
{
	#ifdef DEBUG_BP
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (is_initialized)
	{
		if (all_tuples_to_use_sorted_by_size.size() > index_of_current_tuple)
			return all_tuples_to_use_sorted_by_size.size()-index_of_current_tuple;
		else
			return -1;
	}
	else
		return problem.get_total_number_of_all_forms();
}


Setting BinPacking::get_current_setting()
{
    return setting;
}

void BinPacking::add_form_config_tuple_to_setting(AbstractFormConfigurationTuple &tuple, int plane_index, float position_x, float position_y)
{
	for (int form_index = 0; form_index < tuple.get_number_of_forms(); ++form_index)
	{
		float x_offset_of_form = tuple.get_configuration_of_form(form_index)->get_x();
		float y_offset_of_form = tuple.get_configuration_of_form(form_index)->get_y();
		float rotation_of_form = tuple.get_configuration_of_form(form_index)->get_rotation();
		bool is_mirrored = tuple.get_configuration_of_form(form_index)->is_mirrored();

		setting.add_form_to_plane_at_position(
			tuple.get_configuration_of_form(form_index)->get_form(),
			plane_index,
			position_x + x_offset_of_form,
			position_y + y_offset_of_form,
			rotation_of_form,
			is_mirrored
			);
	}
}