#include "binPacking.hpp"

BinPacking::BinPacking(Problem *p)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	problem = p;
	is_initialized = false;
}

void BinPacking::initialize_algorithm()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
	
	create_initial_sorting();

	minimum_height_of_any_form = problem->get_abstract_form_at_position(all_forms_sorted_by_size[all_forms_sorted_by_size.size()-1])->get_dy();

	index_of_current_form = 0;

	bp_planes = vector<BinPackingPlane>();//1, BinPackingPlane(problem->get_plane_width(), problem->get_plane_height()));

	setting = Setting(problem);

	is_initialized = true;
}

void BinPacking::create_initial_sorting()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int total_number_of_all_forms = problem->get_total_number_of_all_forms();

	all_forms_sorted_by_size = vector<int> (total_number_of_all_forms, 0);

	#ifdef DEBUG
		printf("Total number of all forms: %i\n", total_number_of_all_forms);
	#endif

	int k = 0;
	int number_of_different_forms = problem->get_number_of_different_forms();
	for (int i=0; i<number_of_different_forms; ++i)
	{
		#ifdef DEBUG
			printf("Consider abstract form number %i\n",i);
		#endif

		int number_needed_of_specific_form = problem->get_number_of_form_needed(i);

		#ifdef DEBUG
			printf("Number of forms needed: %i\n",number_needed_of_specific_form);
		#endif

		for (int j=0; j<number_needed_of_specific_form; ++j)
		{
			#ifdef DEBUG
				printf("Add form number %i at to all_forms_sorted_by_size[%i]\n",i,k);
			#endif

			all_forms_sorted_by_size[k] = i;
			++k;
		}
	}

	#ifdef DEBUG
		printf("Finished initializing all_forms_sorted_by_size:\n");
		for (int i=0; i < all_forms_sorted_by_size.size(); ++i)
			printf("\tForm at position %i: %i\n", i, all_forms_sorted_by_size[i]);
	#endif

	FormComparator formComparator(problem);
	std::sort(all_forms_sorted_by_size.begin(), all_forms_sorted_by_size.end(), formComparator);

	#ifdef DEBUG
		printf("\tall_forms_sorted_by_size:\n");
		for (int i=0; i < all_forms_sorted_by_size.size(); ++i)
			printf("\tForm at position %i: %i\n", i, all_forms_sorted_by_size[i]);
	#endif
}

Setting BinPacking::get_packed_setting()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (!problem->is_solveable())
	{
		#ifdef DEBUG
			printf("ERROR: No Setting created because problem is not solveable.\n");
		#endif

		return NULL;
	}

	while(next_step_of_algorithm())
	{
		#ifdef DEBUG
			printf("\n--- Iteration %s finished ---\n\n", __PRETTY_FUNCTION__);
		#endif
	}

	return setting;
}

bool BinPacking::next_step_of_algorithm()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// TO DO: Check if problem is solveable and contains forms

	if (!is_initialized)
		initialize_algorithm();

	if(all_forms_sorted_by_size.size() == 0){
        #ifdef DEBUG
            printf("ERROR: No Forms in Problem.\n");
        #endif

        return false;
    }

	if (get_number_of_missing_forms() > 0)
	{
		if (!try_add_form_on_existing_shelf(index_of_current_form))
			add_form_on_new_shelf(index_of_current_form);
		index_of_current_form++;
		return true;
	}

	return false;

}

bool BinPacking::try_add_form_on_existing_shelf(int form_index)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bool form_added_successfully = false;

	AbstractForm *current_form = problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]);

	for (int shelf_index=0; shelf_index < bp_shelves.size() && !form_added_successfully; ++shelf_index)
	{
		// try to add form:
		float result = bp_shelves[shelf_index].add_form(current_form, form_index);

		if (result >= 0)
		{
			form_added_successfully = true;

			// add Form to setting:
			float x_offset_on_current_plane = bp_shelves[shelf_index].get_offset_x();
			float y_offset_on_current_plane = bp_shelves[shelf_index].get_offset_y();

			int index_of_plane = bp_shelves[shelf_index].get_plane();

			float x_offset_on_shelf = bp_shelves[shelf_index].get_width() - bp_shelves[shelf_index].get_remaining_width() - current_form->get_dx();

			setting.get_plane_at(index_of_plane)->add_form_at_position(current_form, x_offset_on_current_plane + x_offset_on_shelf, y_offset_on_current_plane);
			
			// add subshelf:
			if (result + GlobalParams::get_tolerance() > minimum_height_of_any_form)
				create_subshelf(shelf_index, current_form, result);
		}
	}

	return form_added_successfully;
}

void BinPacking::add_form_on_new_shelf(int form_index)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	AbstractForm* current_form = problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]);

	bool form_added_successfully = false;

	float height_of_current_form = current_form->get_dy();

	for (int plane_index = 0; plane_index < bp_planes.size() && !form_added_successfully; ++plane_index)
	{
		if (bp_planes[plane_index].get_remaining_height() + GlobalParams::get_tolerance() > height_of_current_form)
		{
			float offset_x = 0;
			float offset_y = problem->get_plane_height()-bp_planes[plane_index].get_remaining_height();
			float size_x   = problem->get_plane_width();
			float size_y   = height_of_current_form;

			#ifdef DEBUG
				printf("Create new shelf on existing plane.\n\toff_x = %.2f, off_y = %.2f\n\ts_x = %.2f, s_y = %.2f\n",offset_x, offset_y, size_x, size_y);
			#endif

			create_shelf(plane_index, size_x, size_y, offset_x, offset_y);
			bool success = bp_planes[plane_index].add_shelf(height_of_current_form);

			bp_shelves[bp_shelves.size()-1].add_form(current_form, form_index);

			// add form to setting:
			setting.get_plane_at(plane_index)->add_form_at_position(current_form, offset_x, offset_y);

			form_added_successfully = true;
		}
	}

	if (!form_added_successfully)
	{
		#ifdef DEBUG
			printf("No new shelf on any existing plane could be created to hold form %i.\nAdd new Plane\n", form_index);
		#endif

		bp_planes.push_back(BinPackingPlane(problem->get_plane_width(), problem->get_plane_height()));
		int plane_index = bp_planes.size()-1;

		#ifdef DEBUG
			printf("\tNew plane created with index %i\n", plane_index);
		#endif

		create_shelf(plane_index, problem->get_plane_width(), height_of_current_form, 0, 0);
			
		bp_planes[plane_index].add_shelf(height_of_current_form);

		bp_shelves[bp_shelves.size()-1].add_form(current_form, form_index);

		// add form to setting:
		setting.add_plane();
		setting.get_plane_at(plane_index)->add_form_at_position(current_form, 0, 0);
	}
}

void BinPacking::create_shelf(int index_of_mothershelf, float size_x, float size_y, float offset_x, float offset_y)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bp_shelves.push_back(BinPackingShelf(index_of_mothershelf, size_x, size_y, offset_x, offset_y));
}

void BinPacking::create_subshelf(int index_of_mothershelf, AbstractForm* form_on_top, float remaining_height)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int plane_index = bp_shelves[index_of_mothershelf].get_plane();
	float offset_x  = bp_shelves[index_of_mothershelf].get_offset_x() + bp_shelves[index_of_mothershelf].get_width() - bp_shelves[index_of_mothershelf].get_remaining_width() - form_on_top->get_dx();
	float offset_y  = bp_shelves[index_of_mothershelf].get_offset_y() + form_on_top->get_dy();
	float size_x    = form_on_top->get_dx();
	float size_y    = remaining_height;

	create_shelf(plane_index, size_x, size_y, offset_x, offset_y);
}

int BinPacking::get_number_of_missing_forms()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (is_initialized)
		return all_forms_sorted_by_size.size()-index_of_current_form;
	else
		return problem->get_total_number_of_all_forms();
}

Setting BinPacking::get_current_setting()
{
    return setting;
}
