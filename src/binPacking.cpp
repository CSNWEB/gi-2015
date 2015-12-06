#include "binPacking.hpp"

BinPacking::BinPacking(Problem *p)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	problem = p;

	create_initial_sorting();

	bp_planes = vector<BinPackingPlane>(1, BinPackingPlane(problem->get_plane_width(), problem->get_plane_height()));
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
			printf("No Setting created because problem is not solveable.\n");
		#endif

		return NULL;
	}

	float minimum_height_of_any_form = problem->get_abstract_form_at_position(all_forms_sorted_by_size[all_forms_sorted_by_size.size()-1])->get_dy();

	for (int form_index = 0; form_index<all_forms_sorted_by_size.size(); ++form_index)
	{
		#ifdef DEBUG
			printf("consider form at index %i: is form %i\n", form_index, all_forms_sorted_by_size[form_index]);
		#endif

		bool form_added_successfully = false;

		AbstractForm *current_form = problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]);

		for (int shelf_index=0; shelf_index < bp_shelves.size() && !form_added_successfully; ++shelf_index)
		{
			#ifdef DEBUG
				printf("Try to place form on shelf %i.\n", shelf_index);
			#endif

			float result = bp_shelves[shelf_index].add_form(current_form, form_index);

			if (result < 0)
			{
				#ifdef DEBUG
					printf("Add form %i to shelf %i failed!\n", form_index, shelf_index);
				#endif
			}
			else
			{
				#ifdef DEBUG
					printf("Successfully added form %i to shelf %i!\n", form_index, shelf_index);
				#endif
				form_added_successfully = true;

				if (result + TOLERANCE > minimum_height_of_any_form)
				{
					float offset_x = bp_shelves[shelf_index].get_offset_x() + bp_shelves[shelf_index].get_width() - bp_shelves[shelf_index].get_remaining_width() - current_form->get_dx();
					float offset_y = bp_shelves[shelf_index].get_offset_y() + current_form->get_dy();
					float size_x   = current_form->get_dx();
					float size_y   = result;

					#ifdef DEBUG
						printf("\tEnough space below new form to add subshelf with dimensions:\n\toff_x = %.2f, off_y = %.2f\n\ts_x = %.2f, s_y = %.2f\n",offset_x, offset_y, size_x, size_y);
					#endif

					bp_shelves.push_back(BinPackingShelf(bp_shelves[shelf_index].get_plane(), size_x, size_y, offset_x, offset_y));
				}
			}
		}

		if (!form_added_successfully)
		{
			#ifdef DEBUG
				printf("Form %i could not be placed on a existing shelf.\nTry to create a new shelf.\n", form_index);
			#endif

			float height_of_current_form = current_form->get_dy();

			for (int plane_index = 0; plane_index < bp_planes.size() && !form_added_successfully; ++plane_index)
			{
				if (bp_planes[plane_index].get_remaining_height() + TOLERANCE > height_of_current_form)
				{
					float offset_x = 0;
					float offset_y = problem->get_plane_height()-bp_planes[plane_index].get_remaining_height();
					float size_x   = problem->get_plane_width();
					float size_y   = height_of_current_form;

					#ifdef DEBUG
						printf("Create new shelf on existing plane.\n\toff_x = %.2f, off_y = %.2f\n\ts_x = %.2f, s_y = %.2f\n",offset_x, offset_y, size_x, size_y);
					#endif

					bp_shelves.push_back(BinPackingShelf(plane_index, size_x, size_y, offset_x, offset_y));
					bool success = bp_planes[plane_index].add_shelf(height_of_current_form);

					bp_shelves[bp_shelves.size()-1].add_form(current_form, form_index);

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

				bp_shelves.push_back(BinPackingShelf(plane_index, problem->get_plane_width(), height_of_current_form, 0, 0));
				
				bp_planes[plane_index].add_shelf(height_of_current_form);

				bp_shelves[bp_shelves.size()-1].add_form(current_form, form_index);
			}
		}
	
	}

	Setting result(problem);

	for (int shelf_index = 0; shelf_index < bp_shelves.size(); ++shelf_index)
	{
		int index_of_plane = bp_shelves[shelf_index].get_plane();

		#ifdef DEBUG
			printf("index_of_plane: %i\n", index_of_plane);
		#endif

		if (index_of_plane >= result.get_number_of_planes())
			result.add_plane();

		float x_offset_on_current_plane = bp_shelves[shelf_index].get_offset_x();
		float y_offset_on_current_plane = bp_shelves[shelf_index].get_offset_y();
		for (int index_of_form_on_shelf = 0; index_of_form_on_shelf < bp_shelves[shelf_index].get_number_of_forms_on_shelf(); ++index_of_form_on_shelf)
		{
			#ifdef DEBUG
				printf("index_of_form_on_shelf: %i\n",index_of_form_on_shelf);
			#endif

			int index_of_abst_form = bp_shelves[shelf_index].get_abstract_index_of_form_at(index_of_form_on_shelf);
			AbstractForm* form_to_add = problem->get_abstract_form_at_position(all_forms_sorted_by_size[index_of_abst_form]);

			result.get_plane_at(index_of_plane)->add_form_at_position(form_to_add, x_offset_on_current_plane, y_offset_on_current_plane);
			#ifdef DEBUG
				printf("Finished adding form %i on shelf.\n", index_of_form_on_shelf);
			#endif

			x_offset_on_current_plane += form_to_add->get_dx();

			#ifdef DEBUG
				printf("Finished updating offset.\n");
			#endif
		}
	}

	return result;
}