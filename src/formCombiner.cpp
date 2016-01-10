#include "formCombiner.hpp"

FormCombiner::FormCombiner(Problem *p, AbstractFormConfiguration *form_config_1, AbstractFormConfiguration *form_config_2)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->problem       = p;
	this->form_config_1 = form_config_1;
	this->form_config_2 = form_config_2;
}

AbstractFormConfigurationTuple FormCombiner::compute_optimal_configuration()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// stop the computation if no better configuration can be found.
	bool optimum_found = false;

	AbstractForm *form_1 = form_config_1->get_form();
	AbstractForm *form_2 = form_config_2->get_form();

	float area_of_box_1 = form_1->get_dx()*form_1->get_dy();
	float area_of_box_2 = form_2->get_dx()*form_2->get_dy();

	float biggest_box;
	if (area_of_box_1 > area_of_box_2)
		biggest_box = area_of_box_1;
	else
		biggest_box = area_of_box_2;

	float sum_of_bounding_boxes = area_of_box_1 + area_of_box_2;
	float unmerged_utilization = (form_1->get_size_of_area() + form_2->get_size_of_area()) / sum_of_bounding_boxes;

	#ifdef DEBUG
		printf("Consider form %i and form %i\n", form_1->get_id(), form_2->get_id());
		printf("\tAdded area of both bounding boxes is %.2f\n", sum_of_bounding_boxes);
		printf("\tArea utilization of unmerged configuration is %.2f\n", unmerged_utilization);
	#endif

	// temp_opt = seperated setting
	// for each p in form_1->points:
	// 		for each q in form_2->points:
	//			temp_bounding_box = form_1->bounding_box
	//			compute angle a of vector p -> (p+1)
	//			place q at p and (q+1) in direction defined by a
	//			compute shift of form_2
	//			for each r in form_2->points:
	//				compute new position of r
	//				update temp_bounding_box
	//				if form_2 crosses form_1
	//					is_legal = false
	//					break
	//			if is_legal
	//				if utilizaion of combined form  is better than (form_1->utilization + form_2->utilization) / 2
	//					temp_opt = this configuration

	float minimum_configuration_area = sum_of_bounding_boxes;

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

	AbstractForm form_2_mirrored = *form_2;
	form_2_mirrored.mirror();

	for (int point_1=0; point_1 < form_1->get_number_of_points() && !optimum_found; ++point_1)
	{
		Form f1 = Form(form_1);

		float rotation_form1 = PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(f1.get_points(), point_1, (point_1+1)%form_1->get_number_of_points());
		f1.rotate(0,0,rotation_form1);
		float position_form1_x = -(f1.get_point_at(point_1))->get_x();
		float position_form1_y = -(f1.get_point_at(point_1))->get_y();
		f1.move_rel(position_form1_x, position_form1_y);

		for (int point_2=0; point_2 < form_2->get_number_of_points() && !optimum_found; ++point_2)
		{
			Form f2 = Form(form_2);

			float rotation_form2 = PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(f2.get_points(), point_2, (point_2+1)%form_2->get_number_of_points());
			f2.rotate(0,0,rotation_form2);
			float position_form2_x = -(f2.get_point_at(point_2))->get_x();
			float position_form2_y = -(f2.get_point_at(point_2))->get_y();
			f2.move_rel(position_form2_x, position_form2_y);

			#ifdef DEBUG
				printf("Consider configuration:\n\tForm 1: point %i\n\tForm 2: point %i\n", point_1, point_2);
				f1._d_print_points_to_console();
				f2._d_print_points_to_console();
			#endif

			// check if f1 and f2 overlap:
			// if no, get new bounding box, check if minimal
			if (!f1.check_for_overlap(&f2))
			{
				#ifdef DEBUG
					printf("Forms do not overlap:\n\tConfiguration okay\n");
				#endif

				vector<Point> allpoints(*f1.get_points());
					vector<Point>::iterator insert_point = allpoints.begin() + point_1;
					vector<Point>::iterator begin_of_f2_points = f2.get_points()->begin();
					vector<Point>::iterator end_of_f2_points = f2.get_points()->end();
					vector<Point>::iterator begin_of_f2_hull = f2.get_points()->begin() + point_2;
					allpoints.insert(insert_point, begin_of_f2_hull, end_of_f2_points);
					vector<Point>::iterator insert_point_2 = allpoints.begin() + point_1 + point_2;
					allpoints.insert(insert_point_2, begin_of_f2_points, begin_of_f2_hull);

				vector<int> hull_of_tuple = PointSetAlgorithms::compute_convex_hull(&allpoints);

				float optimal_rotation = PointSetAlgorithms::find_rotation_with_minimum_bounding_box(&allpoints, &hull_of_tuple);

				f1.rotate(0,0, optimal_rotation);
				f2.rotate(0,0, optimal_rotation);

				float current_xmin = min(f1.get_bounding_xmin(), f2.get_bounding_xmin());
				float current_xmax = max(f1.get_bounding_xmax(), f2.get_bounding_xmax());
				float current_ymin = min(f1.get_bounding_ymin(), f2.get_bounding_ymin());
				float current_ymax = max(f1.get_bounding_ymax(), f2.get_bounding_ymax());

				float current_area = (current_xmax - current_xmin)*(current_ymax - current_ymin);

				#ifdef DEBUG
					printf("Combined bounding box has area %.2f\n", current_area);
				#endif

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
				#ifdef DEBUG
					printf("Forms do overlap:\n\tConfiguration illegal!\n");
				#endif

				Form f2_m = Form(&form_2_mirrored);

				rotation_form2 = PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(f2_m.get_points(), point_2, (point_2+1)%form_2->get_number_of_points());
				f2_m.rotate(0,0,rotation_form2);
				position_form2_x = -(f2_m.get_point_at(point_2))->get_x();
				position_form2_y = -(f2_m.get_point_at(point_2))->get_y();
				f2_m.move_rel(position_form2_x, position_form2_y);

				#ifdef DEBUG
					printf("Consider mirrored configuration:\n\tForm 1: point %i\n\tForm 2: point %i\n", point_1, point_2);
					f1._d_print_points_to_console();
					f2_m._d_print_points_to_console();
				#endif

				// check if f1 and f2_m overlap
				// if no:
				// TO DO:
				// 1) merge convex hulls
				// 2) get optimized rotation
				// 3) get new bounding box, check if minimal

				// get new bounding box, check if minimal:
				if (!f1.check_for_overlap(&f2_m))
				{
					#ifdef DEBUG
						printf("Forms do not overlap:\n\tConfiguration okay\n");
					#endif

					vector<Point> allpoints(*f1.get_points());
					vector<Point>::iterator insert_point = allpoints.begin() + point_1;
					vector<Point>::iterator begin_of_f2_points = f2_m.get_points()->begin();
					vector<Point>::iterator end_of_f2_points = f2_m.get_points()->end();
					vector<Point>::iterator begin_of_f2_hull = f2_m.get_points()->begin() + point_2;
					allpoints.insert(insert_point, begin_of_f2_hull, end_of_f2_points);
					vector<Point>::iterator insert_point_2 = allpoints.begin() + point_1 + point_2;
					allpoints.insert(insert_point_2, begin_of_f2_points, begin_of_f2_hull);

					vector<int> hull_of_tuple = PointSetAlgorithms::compute_convex_hull(&allpoints);

					float optimal_rotation = PointSetAlgorithms::find_rotation_with_minimum_bounding_box(&allpoints, &hull_of_tuple);

					f1.rotate(0,0, optimal_rotation);
					f2_m.rotate(0,0, optimal_rotation);

					float current_xmin = min(f1.get_bounding_xmin(), f2_m.get_bounding_xmin());
					float current_xmax = max(f1.get_bounding_xmax(), f2_m.get_bounding_xmax());
					float current_ymin = min(f1.get_bounding_ymin(), f2_m.get_bounding_ymin());
					float current_ymax = max(f1.get_bounding_ymax(), f2_m.get_bounding_ymax());

					float current_area = (current_xmax - current_xmin)*(current_ymax - current_ymin);

					#ifdef DEBUG
						printf("Combined bounding box has area %.2f\n\tcurrent minimum has area %.2f\n", current_area, minimum_configuration_area);
					#endif

					if (current_area < minimum_configuration_area)
					{
						#ifdef DEBUG
							printf("Optimized configuration found!\n");
						#endif

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
				else
				{		
					#ifdef DEBUG
						printf("Forms do overlap:\n\tConfiguration illegal!\n");
					#endif
				}
			}
			if (minimum_configuration_area - biggest_box < GlobalParams::get_tolerance())
				optimum_found = true;
		}
	}

	AbstractFormConfigurationTuple result;
	if (config_point_1 != -1)
	{
		vector<AbstractFormConfiguration> result_configs = vector<AbstractFormConfiguration>(2);
		// a merged configuration with optimized bounding box was found.
		// TO DO: normalize form, i.e. move bounding box to (0/0)
		// create an abstractFormConfiguration:
		result_configs[0] = AbstractFormConfiguration(
								form_1,
								opt_position_form1_x,
								opt_position_form1_y,
								opt_rotation_form1,
								false,
								form_config_1->get_number_of_forms_needed()
								);
		if (point_2_mirrored)
			result_configs[1] = AbstractFormConfiguration(
								form_2,
								opt_position_form2_x,
								opt_position_form2_y,
								opt_rotation_form2,
								true,
								form_config_2->get_number_of_forms_needed()
								);
		else
			result_configs[1] = AbstractFormConfiguration(
								form_2,
								opt_position_form2_x,
								opt_position_form2_y,
								opt_rotation_form2,
								false,
								form_config_2->get_number_of_forms_needed()
								);

		result = AbstractFormConfigurationTuple(result_configs);
	}
	else
	{
		result = AbstractFormConfigurationTuple(AbstractFormConfiguration(form_1, 0, 0, 0, false));
	}

	return result;
}

/*
AbstractFormConfigurationTuple FormCombiner::get_best_tuple(vector<int> forbidden_forms)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	possible_configurations.sort();

	bool found = false;
	list<AbstractFormConfigurationTuple>::iterator it;
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
*/