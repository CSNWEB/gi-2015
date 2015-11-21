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

	all_forms_sorted_by_size = vector<int> (problem->get_total_number_of_all_forms(), 0);
	int k = 0;
	for (int i=0; i<problem->get_number_of_different_forms(); ++i)
		for (int j=0; j<problem->get_number_of_form_needed(i); ++j)
		{
			all_forms_sorted_by_size[k] = i;
			++k;
		}

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

	for (int form_index = 0; form_index<all_forms_sorted_by_size.size(); ++form_index)
	{
		#ifdef DEBUG
			printf("consider form at index %i: is form %i\n", form_index, all_forms_sorted_by_size[form_index]);
		#endif

		bool form_added_successfully = false;

		for (int plane_index = 0; plane_index < bp_planes.size() && !form_added_successfully; ++plane_index)
		{
			#ifdef DEBUG
				printf("Try to place form on plane %i\n", plane_index);
			#endif

			for (int shelf_index=0; shelf_index < bp_planes[plane_index].get_number_of_shelfs() && !form_added_successfully; ++shelf_index)
			{
				#ifdef DEBUG
					printf("Try to place form on shelf %i of plane %i.\n", shelf_index, plane_index);
				#endif

				if (!bp_planes[plane_index].get_shelf_at(shelf_index)->add_form(problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]), form_index))
				{
					#ifdef DEBUG
						printf("Add form %i to shelf %i on plane %i failed!\n", form_index, shelf_index, plane_index);
					#endif
				}
				else
				{
					#ifdef DEBUG
						printf("Successfully added form %i to shelf %i on plane %i!\n", form_index, shelf_index, plane_index);
					#endif

					form_added_successfully = true;
				}
			}

			if (!form_added_successfully)
			{
				#ifdef DEBUG
					printf("Form %i could not be placed on a existing shelf on plane %i.\nTry to create a new shelf.\n", form_index, plane_index);
				#endif

				if (bp_planes[plane_index].add_shelf(problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index])->get_dy()))
				{
					bp_planes[plane_index].get_shelf_at(bp_planes[plane_index].get_number_of_shelfs()-1)->add_form(problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]), form_index);
					form_added_successfully = true;
				}
			}
		}

		if (!form_added_successfully)
		{
			#ifdef DEBUG
				printf("Form %i could not be placed on any existing plane.\nCreate new plane.\n", form_index);
			#endif

			bp_planes.push_back(BinPackingPlane(problem->get_plane_width(), problem->get_plane_height()));
			int plane_index = bp_planes.size()-1;

			if (bp_planes[plane_index].add_shelf(problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index])->get_dy()))
				bp_planes[plane_index].get_shelf_at(0)->add_form(problem->get_abstract_form_at_position(all_forms_sorted_by_size[form_index]), form_index);

		}
	}



	Setting result(problem);

	for (int plane_index=0; plane_index < bp_planes.size(); ++plane_index)
	{
		result.add_plane();
		float y_offset_on_current_plane = 0;
		for (int shelf_index=0; shelf_index < bp_planes[plane_index].get_number_of_shelfs(); ++shelf_index)
		{
			float x_offset_on_current_shelf = 0;
			for (int form_index=0; form_index < bp_planes[plane_index].get_shelf_at(shelf_index)->get_number_of_forms_on_shelf(); ++form_index)
			{
				int index_of_abst_form = bp_planes[plane_index].get_shelf_at(shelf_index)->get_abstract_index_of_form_at(form_index);

				#ifdef DEBUG
					printf("Create Setting:\n");
					printf("\tForm (index of abstract form): %i\n", all_forms_sorted_by_size[index_of_abst_form]);
					printf("\tPlane: %i\n", plane_index);
					printf("\t(Shelf: %i)\n", shelf_index);
					printf("\tPosition x: %.2f\n\tPosition y: %.2f\n", x_offset_on_current_shelf, y_offset_on_current_plane);
				#endif

				result.get_plane_at(plane_index)->add_form_at_position(problem->get_abstract_form_at_position(all_forms_sorted_by_size[index_of_abst_form]), x_offset_on_current_shelf, y_offset_on_current_plane);
				
				#ifdef DEBUG
					printf("Form successfully added to plane.\n");
				#endif

				x_offset_on_current_shelf += problem->get_abstract_form_at_position(all_forms_sorted_by_size[index_of_abst_form])->get_dx();
			}

			#ifdef DEBUG
				printf("Successfully added all forms of shelf to plane.\n");
			#endif
				
			y_offset_on_current_plane += bp_planes[plane_index].get_shelf_at(shelf_index)->get_height();
		}
	}

	return result;
}