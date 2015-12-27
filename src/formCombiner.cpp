#include "formCombiner.hpp"

FormCombiner::FormCombiner(Problem* problem, AbstractForm* abstract_form)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

}

ReturnType FormCombiner::search_for_optimal_configuration_global()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// for each AbstractForm in problem->abstract_forms:
	// 		search_for_optimal_configuration_local (form)
	// return best
}

ReturnType FormCombiner::search_for_optimal_configuration_local(AbstractForm* other_form)
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

	AbstractForm other_form_mirrored = &other_form;
	other_form_mirrored.mirror();

	for (int point_1=0; point_1 < abstract_form_1->get_number_of_points(); ++point_1)
	{
		float base_rotation = abstract_form_1->compute_rotation_angle_for_points_parallel_to_axis(point_1, (point_1+1)%abstract_form_1->get_number_of_points());
		Form f1 = Form(abstract_form_1);
		f1.rotate(0,0,base_rotation);

		for (int point_2=0; point_2 < other_form->get_number_of_points(); ++point_2)
		{
			Form f2 = Form(other_form);
			float other_rotation = other_form->compute_rotation_angle_for_points_parallel_to_axis(point_2, (point_2+1)%other_form->get_number_of_points());
			f2.rotate(0,0,other_rotation);
			// check if f1 and f2 ovwerlap
			// if no, get new bounding box, check if minimal

			Form f2_m = Form(&other_form_mirrored);
			float other_mirror_rotation = other_form_mirrored.compute_rotation_angle_for_points_parallel_to_axis(point_2, (point_2+1)%other_form->get_number_of_points());
			f2_m.rotate(0,0,other_mirror_rotation);
			// check if f1 and f2_m ovwerlap
			// if no, get new bounding box, check if minimal
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
}