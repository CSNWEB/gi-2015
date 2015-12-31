#include "formCombiner.hpp"

FormCombiner::FormCombiner(Problem* problem, AbstractForm* abstract_form)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

}

AbstractFormConfiguration FormCombiner::search_for_optimal_configuration_global()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// for each AbstractForm in problem->abstract_forms:
	// 		search_for_optimal_configuration_local (form)
	// return best
}

AbstractFormConfiguration FormCombiner::search_for_optimal_configuration_local(AbstractForm* other_form)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// estimate minimum nonmerged configuration, i.e. best way to place both forms adjacent
	// such that the bounding box of both forms is minimal.
	// 0 : both forms unrotated
	// 1 : other_form rotated
	// 2 : this form rotated
	// 3 : both forms rotated
	
	// 0:
	int minimum_nonmerged_configuration = 0;
	float current_combined_dx = max(abstract_form_1->get_dx(), other_form->get_dx());
	float current_combined_dy = abstract_form_1->get_dy() + other_form->get_dy();
	
	float minimum_nonmerged_bounding_box = current_combined_dx * current_combined_dy;

	float dx_1[3] = {abstract_form_1->get_dx(), abstract_form_1->get_dy(), abstract_form_1->get_dy()};
	float dx_2[3] = {other_form->get_dy(),  other_form->get_dx(),  other_form->get_dy()};
	float dy_1[3] = {abstract_form_1->get_dy(), abstract_form_1->get_dx(), abstract_form_1->get_dx()};
	float dy_2[3] = {other_form->get_dx(), other_form->get_dy(), other_form->get_dx()}

	for (int i=0; i<4; ++i)
	{
		current_combined_dx = max(dx_1[i], dx_2[i]);
		current_combined_dy = dy_1[i] + dy_2[i];

		if (current_combined_dx * current_combined_dy < minimum_nonmerged_bounding_box)
		{
			minimum_nonmerged_configuration = i;
			minimum_nonmerged_bounding_box = current_combined_dx * current_combined_dy;
		}
	}

	// temp_opt = seperated setting
	// for each p in abstract_form_1->points:
	// 		for each q in other_form->points:
	//			temp_bounding_box = abstract_form_1->bounding_box
	//			compute angle a of vector p -> (p+1)
	//			place q at p and (q+1) in direction defined by a
	//			compute shift of other_form
	//			for each r in other_form->points:
	//				compute new position of r
	//				update temp_bounding_box
	//				if other_form crosses abstract_form_1
	//					is_legal = false
	//					break
	//			if is_legal
	//				if utilizaion of combined form  is better than (abstract_form_1->utilization + other_form->utilization) / 2
	//					temp_opt = this configuration

	float minimum_configuration_area = minimum_nonmerged_bounding_box;

	int config_point_1 = -1;
	int config_point_2 = -1;
	bool point_2_mirrored = false;

	// init position values:
	float opt_position_form1_x = 0;
	float opt_position_form1_y = 0;
	float opt_rotation_form1 = 0;

	float opt_position_form2_x = 0;
	float opt_position_form2_y = 0;
	float opt_rotation_form2 = 0;

	AbstractForm other_form_mirrored = &other_form;
	other_form_mirrored.mirror();

	for (int point_1=0; point_1 < abstract_form_1->get_number_of_points(); ++point_1)
	{
		Form f1 = Form(abstract_form_1);

		float rotation_1 = abstract_form_1->compute_rotation_angle_for_points_parallel_to_axis(point_1, (point_1+1)%abstract_form_1->get_number_of_points());
		float position_form1_x = -(f1.get_point_at(point_1))->get_x();
		float position_form1_y = -(f1.get_point_at(point_1))->get_y();
		f1.rotate(0,0,rotation_form1);
		f1.move_rel(position_form1_x, position_form1_y);

		for (int point_2=0; point_2 < other_form->get_number_of_points(); ++point_2)
		{
			Form f2 = Form(other_form);

			float rotation_form2 = other_form->compute_rotation_angle_for_points_parallel_to_axis(point_2, (point_2+1)%other_form->get_number_of_points());
			float position_form2_x = -(f2.get_point_at(point_2))->get_x();
			float position_form2_y = -(f2.get_point_at(point_2))->get_y()
			f2.rotate(0,0,rotation_form2);
			f2.move_rel(position_form2_x, position_form2_y);

			// check if f1 and f2 overlap:
			// if no, get new bounding box, check if minimal
			if (!f1.check_for_overlap(&f2))
			{
				float current_xmin = min(f1.get_bounding_xmin(), f2.get_bounding_xmin())
				float current_xmax = max(f1.get_bounding_xmax(), f2.get_bounding_xmax())
				float current_ymin = min(f1.get_bounding_ymin(), f2.get_bounding_ymin())
				float current_ymax = max(f1.get_bounding_ymax(), f2.get_bounding_ymax())

				float current_area = (current_xmax - current_xmin)*(current_ymax - current_ymin);
				if (current_area < minimum_configuration_area)
				{
					minimum_configuration_area = current_area;
					config_point_1 = point_1;
					config_point_2 = point_2;
					point_2_mirrored = false;

					opt_position_form1_x = position_form1_x;
					opt_position_form1_y = position_form1_y;
					opt_rotation_form1 = rotation_form1;

					opt_position_form2_x = position_form2_x;
					opt_position_form2_y = position_form2_y;
					opt_rotation_form2 = rotation_form2;
				}
			}
			else
			{
				Form f2_m = Form(&other_form_mirrored);

				rotation_form2 = other_form_mirrored.compute_rotation_angle_for_points_parallel_to_axis(point_2, (point_2+1)%other_form->get_number_of_points());
				position_form2_x = -(f2_m.get_point_at(point_2))->get_x();
				position_form2_y = -(f2_m.get_point_at(point_2))->get_y();
				f2_m.rotate(0,0,rotation_form2);
				f2_m.move_rel(position_form2_x, position_form2_y);

				// check if f1 and f2_m overlap
				// if no, get new bounding box, check if minimal
				if (!f1.check_for_overlap(&f2_m))
				{
					float current_xmin = min(f1.get_bounding_xmin(), f2_m.get_bounding_xmin())
					float current_xmax = max(f1.get_bounding_xmax(), f2_m.get_bounding_xmax())
					float current_ymin = min(f1.get_bounding_ymin(), f2_m.get_bounding_ymin())
					float current_ymax = max(f1.get_bounding_ymax(), f2_m.get_bounding_ymax())

					float current_area = (current_xmax - current_xmin)*(current_ymax - current_ymin);
					if (current_area < minimum_configuration_area)
					{
						minimum_configuration_area = current_area;
						config_point_1 = point_1;
						config_point_2 = point_2;
						point_2_mirrored = true;

						opt_position_form1_x = position_form1_x;
						opt_position_form1_y = position_form1_y;
						opt_rotation_form1 = rotation_form1;

						opt_position_form2_x = position_form2_x;
						opt_position_form2_y = position_form2_y;
						opt_rotation_form2 = rotation_form2;
					}
				}
			}
		}
	}

	AbstractFormConfiguration result;
	if (config_point_1 != -1)
	{
		// a merged configuration with optimized bounding box was found.
		// create an abstractFormConfiguration:
		result = AbstractFormConfiguration(abstract_form_1,
								  opt_position_form1_x,
								  opt_position_form1_y,
								  opt_rotation_form1
								  );
		if (point_2_mirrored)
			result.add_abstract_form(
								other_form_mirrored,
								opt_position_form2_x,
								opt_position_form2_y,
								opt_rotation_form2
								);
		else
			result.add_abstract_form(
								other_form,
								opt_position_form2_x,
								opt_position_form2_y,
								opt_rotation_form2
								);
	}
	else
	{
		result = AbstractFormConfiguration(abstract_form_1, 0, 0, 0);
	}

	// insert result in possible_configurations
}

AbstractFormConfiguration FormCombiner::get_best_configuration(vector<int> forbidden_forms)
{
	bool found = false;
	list<AbstractFormConfiguration>::iterator it;
	for (it = possible_configurations.begin(); it != possible_configurations.end() && !found; it++)
	{
		bool is_legal = true;
		for (int current_form = 0; current_form < forbidden_forms.size() && is_legal; current_form++)
		{
			if (it->contains_form(forbidden_forms[current_form]))
				is_legal = false;
		}

		if (is_legal)
			found = true;
	}
	return *it;
}