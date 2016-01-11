#include "formCombiner.hpp"

#define DEBUG

FormCombiner::FormCombiner(Problem *p, AbstractFormConfiguration *form_config_1, AbstractFormConfiguration *form_config_2)
{
	//#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	//#endif

	this->problem       = p;
	this->form_config_1 = form_config_1;
	this->form_config_2 = form_config_2;

	form_2_mirrored = AbstractForm();
	f1 = Form();
	f2 = Form();
	f2_m = Form();

	area_of_biggest_box_of_forms = -1;
	sum_of_bounding_boxes = -1;

	cur_configuration_area = -1;

	cur_position_form_1_x = -1;
	cur_position_form_1_y = -1;
	cur_rotation_form_1   = -1;

	cur_position_form_2_x = -1;
	cur_position_form_2_y = -1;
	cur_rotation_form_2   = -1;
	cur_mirror_form_2 = false;

	cur_total_rotation = 0;

	opt_position_form_1_x = -1;
	opt_position_form_1_y = -1;
	opt_rotation_form_1   = -1;

	opt_position_form_2_x = -1;
	opt_position_form_2_y = -1;
	opt_rotation_form_2   = -1;
	opt_mirror_form_2 = false;

	opt_configuration_area = -1;

	opt_total_rotation = 0;


	allpoints = vector<Point>(0);
	hull_of_tuple = vector<int>(0);

	is_finished = false;
	optimum_found = false;
}

void FormCombiner::init()
{	
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	optimum_found = false;

	form_1 = form_config_1->get_form();
	form_2 = form_config_2->get_form();

	form_2_mirrored = *form_2;
	form_2_mirrored.mirror();

	float area_of_box_1 = form_1->get_dx()*form_1->get_dy();
	float area_of_box_2 = form_2->get_dx()*form_2->get_dy();

	if (area_of_box_1 > area_of_box_2)
		area_of_biggest_box_of_forms = area_of_box_1;
	else
		area_of_biggest_box_of_forms = area_of_box_2;

	sum_of_bounding_boxes = area_of_box_1 + area_of_box_2;

	opt_configuration_area = sum_of_bounding_boxes;

	opt_position_form_1_x = 0;
	opt_position_form_1_y = 0;
	opt_rotation_form_1 = 0;

	opt_position_form_2_x = 0;
	opt_position_form_2_y = 0;
	opt_rotation_form_2 = 0;

	#ifdef DEBUG
		printf("Init:\n\tArea of biggest box of forms: %.2f\n\tSum of bounding box areas: %.2f\n", area_of_biggest_box_of_forms, sum_of_bounding_boxes);
	#endif
}

void FormCombiner::compute_config_form_1(int index_of_point)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	f1 = Form(form_1);

	cur_rotation_form_1 = PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(f1.get_points(), index_of_point, (index_of_point+1)%form_1->get_number_of_points());
	f1.rotate(0,0,cur_rotation_form_1);
	cur_position_form_1_x = -(f1.get_point_at(index_of_point))->get_x();
	cur_position_form_1_y = -(f1.get_point_at(index_of_point))->get_y();
	f1.move_rel(cur_position_form_1_x, cur_position_form_1_y);

	#ifdef DEBUG
		printf("computed configuration of form 1:\n");
		printf("\trotation: %.2f\n\tmovement: %.2f/%.2f\n", cur_rotation_form_1, cur_position_form_1_x, cur_position_form_1_y);
		f1._d_print_points_to_console();
	#endif
}

void FormCombiner::compute_config_form_2(int index_of_point, bool is_mirrored)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	Form *f;
	if (!is_mirrored)
	{
		f2 = Form(form_2);
		f = &f2;
	}
	else
	{
		f2_m = Form(&form_2_mirrored);
		f = &f2_m;
	}

	cur_mirror_form_2 = is_mirrored;

	cur_rotation_form_2 = PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(f->get_points(), index_of_point, (index_of_point+1)%form_2->get_number_of_points());
	f->rotate(0,0,cur_rotation_form_2);
	cur_position_form_2_x = -(f->get_point_at(index_of_point))->get_x();
	cur_position_form_2_y = -(f->get_point_at(index_of_point))->get_y();
	f->move_rel(cur_position_form_2_x, cur_position_form_2_y);

	#ifdef DEBUG
		printf("computed configuration of form 2:\n");
		printf("\trotation: %.2f\n\tmovement: %.2f/%.2f\n", cur_rotation_form_2, cur_position_form_2_x, cur_position_form_2_y);
		f->_d_print_points_to_console();
	#endif
}

void FormCombiner::reset_form_1()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	f1 = Form(form_1);
	f1.rotate(0,0,cur_rotation_form_1);
	f1.move_rel(cur_position_form_1_x, cur_position_form_1_y);
}

void FormCombiner::compute_optimal_rotation_and_area_for_tuple_config(int index_of_point_1, int index_of_point_2)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// init pointer to second form, depending on if its currently mirrored.
	Form *f2_temp;
	if (!cur_mirror_form_2)
		f2_temp = &f2;
	else
		f2_temp = &f2_m;

	#ifdef DEBUG
		printf("f2_temp initialized\n");
	#endif

	// compute combined pointset of both Forms:
	/*vector<Point>*/ allpoints = vector<Point>(f1.get_points()->begin(), f1.get_points()->end());
	vector<Point>::iterator insert_point = allpoints.begin() + index_of_point_1;
	vector<Point>::iterator begin_of_f2_points = f2_temp->get_points()->begin();
	vector<Point>::iterator end_of_f2_points = f2_temp->get_points()->end();
	vector<Point>::iterator begin_of_f2_hull = f2_temp->get_points()->begin() + index_of_point_2;

	allpoints.insert(insert_point, begin_of_f2_hull, end_of_f2_points);
	vector<Point>::iterator insert_point_2 = allpoints.begin() + index_of_point_1 + index_of_point_2;
	allpoints.insert(insert_point_2, begin_of_f2_points, begin_of_f2_hull);

	//#ifdef DEBUG
		printf("allpoints initialized\n");

		for (int i=0; i<allpoints.size(); ++i)
			printf("Point %i: (%.2f/%.2f)\n", i, allpoints[i].get_x(), allpoints[i].get_y());
	//#endif

	printf("\nBLA\n\n");

	// compute convex hull
	PointSetAlgorithms::compute_convex_hull(allpoints, hull_of_tuple);

	#ifdef DEBUG
		printf("convex hull computed\n");
	#endif

	cur_total_rotation = PointSetAlgorithms::find_rotation_with_minimum_bounding_box(&allpoints, &hull_of_tuple);

	#ifdef DEBUG
		printf("optimal rotation computed\n");
	#endif

	//printf("Rotate by %.2f degrees...\n", cur_total_rotation);
	f1.rotate(0,0, cur_total_rotation);
	f2_temp->rotate(0,0, cur_total_rotation);

	#ifdef DEBUG
		printf("Forms post-rotation:\n");
		f1._d_print_points_to_console();
		f2_temp->_d_print_points_to_console();
	#endif

	float current_xmin = min(f1.get_bounding_xmin(), f2_temp->get_bounding_xmin());
	float current_xmax = max(f1.get_bounding_xmax(), f2_temp->get_bounding_xmax());
	float current_ymin = min(f1.get_bounding_ymin(), f2_temp->get_bounding_ymin());
	float current_ymax = max(f1.get_bounding_ymax(), f2_temp->get_bounding_ymax());

	cur_configuration_area = (current_xmax - current_xmin)*(current_ymax - current_ymin);
	#ifdef DEBUG
		printf("xmin = %.2f, xmax = %.2f, ymin = %.2f, ymax = %.2f\n", current_xmin, current_xmax, current_ymin, current_ymax);
		printf("Computed minimum area: %.2f x %.2f\nArea is %.2f\n", current_xmax - current_xmin, current_ymax - current_ymin, cur_configuration_area);
	#endif
}

bool FormCombiner::update_if_better()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (opt_configuration_area - cur_configuration_area > GlobalParams::get_tolerance())
	{
		opt_configuration_area = cur_configuration_area;

		opt_position_form_1_x = cur_position_form_1_x;
		opt_position_form_1_y = cur_position_form_1_y;
		opt_rotation_form_1   = cur_rotation_form_1;

		opt_position_form_2_x = cur_position_form_2_x;
		opt_position_form_2_y = cur_position_form_2_y;
		opt_rotation_form_2   = cur_rotation_form_2;
		opt_mirror_form_2     = cur_mirror_form_2;

		float opt_crit = opt_configuration_area - area_of_biggest_box_of_forms;

		//printf("Optimum criteria: %.2f - %.2f = %.2f\n", opt_configuration_area, area_of_biggest_box_of_forms, opt_crit);

		if (opt_crit < GlobalParams::get_tolerance())
		{
			#ifdef DEBUG
				printf("Found configuration with minimum possible area: %.2f\n", opt_configuration_area);
			#endif

			optimum_found = true;
		}

		return true;
	}
	else
		return false;
}

AbstractFormConfigurationTuple FormCombiner::create_config_tuple()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	AbstractFormConfigurationTuple optimal_configured_tuple;

	if (sum_of_bounding_boxes - opt_configuration_area > GlobalParams::get_tolerance())
	{
		vector<AbstractFormConfiguration> result_configs = vector<AbstractFormConfiguration>(2);
		// a merged configuration with optimized bounding box was found.
		// create an abstractFormConfiguration:
		result_configs[0] = AbstractFormConfiguration(
			form_1,
			opt_position_form_1_x,
			opt_position_form_1_y,
			opt_rotation_form_1,
			false,
			form_config_1->get_number_of_forms_needed()
		);
		
		result_configs[1] = AbstractFormConfiguration(
			form_2,
			opt_position_form_2_x,
			opt_position_form_2_y,
			opt_rotation_form_2,
			opt_mirror_form_2,
			form_config_2->get_number_of_forms_needed()
		);

		#ifdef DEBUG
			printf("Create Tuple with:\n");
			printf("Form 1 at position %.2f/%.2f, rotation %.2f\n", opt_position_form_1_x, opt_position_form_1_y, opt_rotation_form_1);
			printf("Form 2 at position %.2f/%.2f, rotation %.2f\n", opt_position_form_2_x, opt_position_form_2_y, opt_rotation_form_2);
		#endif

		optimal_configured_tuple = AbstractFormConfigurationTuple(result_configs);
		optimal_configured_tuple.rotate(opt_total_rotation);
		optimal_configured_tuple.normalize_position();
	}
	else
	{
		#ifdef DEBUG
			printf("No optimal configuration found, create simple tuple.\n");
		#endif

		optimal_configured_tuple = AbstractFormConfigurationTuple(AbstractFormConfiguration(form_1, 0, 0, 0, false, form_config_1->get_number_of_forms_needed()));
	}

	return optimal_configured_tuple;
}

void FormCombiner::compute_optimal_configuration()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	init();

	#ifdef DEBUG
		printf("Consider form %i and form %i\n", form_1->get_id(), form_2->get_id());
		printf("\tAdded area of both bounding boxes is %.2f\n", sum_of_bounding_boxes);
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

	//int config_point_1 = -1;
	//int config_point_2 = -1;
	//bool point_2_mirrored = false;

	for (int point_1=0; point_1 < form_1->get_number_of_points() && !optimum_found; ++point_1)
	{
		#ifdef DEBUG
			printf("iteration on form 1: %i\n", point_1);
		#endif

		compute_config_form_1(point_1);

		for (int point_2=0; point_2 < form_2->get_number_of_points() && !optimum_found; ++point_2)
		{
			reset_form_1();
			compute_config_form_2(point_2, false);

			#ifdef DEBUG
				printf("Consider configuration:\n\tForm 1: point %i\n\tForm 2: point %i\n", point_1, point_2);
				//f1._d_print_points_to_console();
				//f2._d_print_points_to_console();
			#endif

			// check if f1 and f2 overlap:
			// if no, get new bounding box, check if minimal
			if (!f1.check_for_overlap(&f2))
			{
				#ifdef DEBUG
					printf("Forms do not overlap:\n\tConfiguration okay\n");
				#endif

				compute_optimal_rotation_and_area_for_tuple_config(point_1, point_2);

				#ifdef DEBUG
					printf("Combined bounding box has area %.2f\n", cur_configuration_area);
				#endif

				update_if_better();
			}
			else
			{
				#ifdef DEBUG
					printf("Forms do overlap:\n\tConfiguration illegal!\n");
				#endif
/*
				
				compute_config_form_2(point_2, true);

				//#ifdef DEBUG
					printf("Consider mirrored configuration:\n\tForm 1: point %i\n\tForm 2: point %i\n", point_1, point_2);
					f1._d_print_points_to_console();
					f2_m._d_print_points_to_console();
				//#endif

				// check if f1 and f2_m overlap
				// if no:
				// 1) merge point sets, compute convex hull
				// 2) get optimized rotation
				// 3) get new bounding box, check if minimal

				// get new bounding box, check if minimal:
				if (!f1.check_for_overlap(&f2_m))
				{
					//#ifdef DEBUG
						printf("Forms do not overlap:\n\tConfiguration okay\n");
					//#endif

					compute_optimal_rotation_and_area_for_tuple_config(point_1, point_2);
					//#ifdef DEBUG
						printf("Combined bounding box has area %.2f\n\tcurrent minimum has area %.2f\n", cur_configuration_area, opt_configuration_area);
					//#endif

					update_if_better();
				}
				else
				{		
					//#ifdef DEBUG
						printf("Forms do overlap:\n\tConfiguration illegal!\n");
					//#endif
				}
*/
			}
		}
	}

	is_finished = true;
}

AbstractFormConfigurationTuple FormCombiner::get_optimal_configured_tuple()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (!is_finished)
		compute_optimal_configuration();
	return 	create_config_tuple();;
}

#undef DEBUG