#include "pointSetAlgorithms.hpp"

#ifdef DEBUG
	#define DEBUG_PSA
#endif


bool PointSetAlgorithms::unique_indicies_of_points(vector<Point> &points, vector<int> &indices)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (indices.size() < 2)
		return false;

	bool points_deleted = false;

	list<int> unique_points(1, indices[0]);

	for (int i=1; i<indices.size(); ++i)
	{
		float x1 = points[indices[i-1]].get_x();
		float x2 = points[indices[i]].get_x();
        if (fabs(x1 - x2) < GlobalParams::get_tolerance())
		{
			float y1 = points[indices[i-1]].get_y();
			float y2 = points[indices[i]].get_y();
            if (fabs(y1 - y2) < GlobalParams::get_tolerance())
				points_deleted = true;
			else
				unique_points.push_back(indices[i]);
		}
		else
			unique_points.push_back(indices[i]);
	}
	indices = vector<int>(unique_points.begin(), unique_points.end());
}

bool PointSetAlgorithms::rotate_pointset_at_point(vector<Point> &points, float center_x, float center_y, float angle)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (points.size() < 1)
		return false;

	if (angle > GlobalParams::get_tolerance())
		for (int i=0; i<points.size(); ++i)
			points[i].rotate(center_x, center_y, angle);
			
	return true;
}

bool PointSetAlgorithms::rotate_pointset_at_point(
		vector<Point> &points,
		float center_x,
		float center_y,
		float angle,
		float &x_min,
		float &x_max,
		float &y_min,
		float &y_max
	)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (points.size() < 1)
		return false;

	points[0].rotate(center_x, center_y, angle);
	x_min = points[0].get_x();
	x_max = points[0].get_x();
	y_min = points[0].get_y();
	y_max = points[0].get_y();

	for (int i=1; i < points.size(); ++i)
	{

		points[i].rotate(center_x, center_y, angle);

		if (points[i].get_x() < x_min)
			x_min = points[i].get_x();
		else if (points[i].get_x() > x_max)
			x_max = points[i].get_x();

		if (points[i].get_y() < y_min)
			y_min = points[i].get_y();
		else if (points[i].get_y() > y_max)
			y_max = points[i].get_y();
	}
			
	return true;
}

bool PointSetAlgorithms::mirror_pointset_at_axis(vector<Point> &points, float y_min, float y_max)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (points.size() < 1)
		return false;

	#ifdef DEBUG_PSA
		printf("Mirror Pointset with ymin = %.2f, ymax = %.2f\n", y_min, y_max);
	#endif

	for (int point_index = 0; point_index < points.size(); ++point_index)
	{
		float current_y = points[point_index].get_y();
		points[point_index].set_y(y_max + y_min - current_y);
	}

	return true;
}

vector<int> PointSetAlgorithms::sort_points_by_dim_x(vector<Point> &points)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int number_of_entries = points.size();

	if (number_of_entries == 0)
		return vector<int>();
	if (number_of_entries == 1)
		return vector<int>(1,0);
	
	vector<int> sorted_indices = vector<int>(number_of_entries);
	for (int i=0; i<number_of_entries; ++i)
		sorted_indices[i] = i;

	PointComparator pc(&points);
	sort(sorted_indices.begin(), sorted_indices.end(), pc);

	return sorted_indices;
}

bool PointSetAlgorithms::compute_convex_hull(vector<Point> &points, vector<int> &hull)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		for (int i=0; i<points.size(); ++i)
			printf("Point %i: (%.2f/%.2f)\n", i, points[i].get_x(), points[i].get_y());
	#endif

	vector<int> convex_hull = vector<int>(0);

	if (points.size() < 3)
	{
		#ifdef DEBUG_PSA
			printf("No hull created\n");
		#endif

		hull = convex_hull;
		return false;
	}

	vector<int> convex_hull_lower	= vector<int>(0);
	vector<int> ordered_indices		= vector<int>(0);
	vector<int> convex_hull_upper	= vector<int>(0);

	ordered_indices = PointSetAlgorithms::sort_points_by_dim_x(points);

	PointSetAlgorithms::unique_indicies_of_points(points, ordered_indices);

	#ifdef DEBUG_PSA
		printf("Back in compute_convex_hull.\nOrdered indices:\n");
		for (int i=0; i<ordered_indices.size(); ++i)
			printf("\t%i\n", ordered_indices[i]);
	#endif

	//int first_element = *ordered_indices.begin();
	convex_hull_lower = vector<int>(1, ordered_indices[0]);
	convex_hull_lower.insert(convex_hull_lower.end(), ordered_indices.begin(), ordered_indices.end());

	#ifdef DEBUG_PSA
		printf("Init lower_hull finished\n");
		for (int i=0; i<convex_hull_lower.size(); ++i)
			printf("point at position %i: %i\n",i, convex_hull_lower[i]);
	#endif

	int i=0;
	while (i < convex_hull_lower.size()-2)
	{
		#ifdef DEBUG_PSA
			printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_lower.size());
		#endif

		int ind_p1 = convex_hull_lower[i];
		int ind_p2 = convex_hull_lower[i+1];
		int ind_p3 = convex_hull_lower[i+2];

		#ifdef DEBUG_PSA
			printf("now check if %i is left of %i->%i\n", ind_p2, ind_p1, ind_p3);
		#endif

		Point line_begin = points[ind_p1];
		Point line_end   = points[ind_p3];

		if (points[ind_p2].is_left_of(&line_begin, &line_end) > 0)
		{
			// p2 is not part of convex hull
			#ifdef DEBUG_PSA
				printf("\terase point %i from hull\n", i+1);
				printf("\tthis is: %i\n", *(convex_hull_lower.begin()+(i+1)));
			#endif

			convex_hull_lower.erase(convex_hull_lower.begin()+i+1);
			--i;
		}
		else
			++i;
	}

	convex_hull_lower.erase(convex_hull_lower.begin());

	#ifdef DEBUG_PSA
		printf("lower hull complete\n");
		for (int k=0; k<convex_hull_lower.size(); ++k)
			printf("\tpoint %i is %i\n", k, convex_hull_lower[k]);
	#endif

	convex_hull_upper = ordered_indices;
	convex_hull_upper.push_back(ordered_indices[ordered_indices.size()-1]);

	#ifdef DEBUG_PSA
		printf("Init upper_hull finished\n");
		for (int i=0; i<convex_hull_upper.size(); ++i)
			printf("point at position %i: %i\n",i, convex_hull_upper[i]);
	#endif

	i = convex_hull_upper.size()-1;
	while (i >= 2)
	{
		#ifdef DEBUG_PSA
			printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_upper.size());
		#endif
		int ind_p1 = convex_hull_upper[i];
		int ind_p2 = convex_hull_upper[i-1];
		int ind_p3 = convex_hull_upper[i-2];

		#ifdef DEBUG_PSA
			printf("now check if %i is left of %i->%i\n", ind_p2, ind_p1, ind_p3);
		#endif

		if (points[ind_p2].is_left_of(&(points[ind_p1]), &(points[ind_p3])) > 0)
		{
			// p2 is not part of convex hull
			#ifdef DEBUG_PSA
				printf("\terase point %i from hull\n", i-1);
				printf("\tthis is: %i\n", *(convex_hull_upper.begin()+i-1));
			#endif

			convex_hull_upper.erase(convex_hull_upper.begin()+i-1);
			++i;
		}
		else
			--i;
	}

	#ifdef DEBUG_PSA
		printf("upper hull complete:\n");
		for (int k=0; k<convex_hull_upper.size(); ++k)
			printf("\tpoint %i is %i\n", k, convex_hull_upper[k]);
	#endif

	// concatenate lower and upper hull:
	convex_hull = convex_hull_lower;

	for (int k=convex_hull_upper.size()-3; k>=0; --k)
		convex_hull.push_back(convex_hull_upper[k]);

	// check if hull and points have equal orientation
	// if not, reverse hull:
	if (convex_hull[2] < convex_hull[1])
	{
		int size_of_hull = convex_hull.size();
		for (int i=0; i < size_of_hull/2; ++i)
		{
			int tmp = convex_hull[i];
			convex_hull[i] = convex_hull[size_of_hull-1-i];
			convex_hull[size_of_hull-1-i] = tmp;
		}
	}


	#ifdef DEBUG_PSA
		printf("convex hull finished\n");
		for (int i=0; i<convex_hull.size(); ++i)
			printf("\t%i\n", convex_hull[i]);
	#endif

		hull = convex_hull;
	return true;
}


float PointSetAlgorithms::compute_rotation_angle_for_points_parallel_to_axis(vector<Point> &points, int index_of_point_1, int index_of_point_2)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("\t\tPoint1 = %i\n\t\tPoint2 = %i\n", index_of_point_1, index_of_point_2);
	#endif

	float result_angle;

	float p1_orig_x = points[index_of_point_1].get_x();
	float p1_orig_y = points[index_of_point_1].get_y();

	float p2_orig_x = points[index_of_point_2].get_x();
	float p2_orig_y = points[index_of_point_2].get_y();

	if (p1_orig_y < p2_orig_y)
		result_angle =  180 + compute_rotation_angle_for_points_parallel_to_axis(points, index_of_point_2, index_of_point_1);
	else
	{
		float d1_squared = ((p1_orig_x - p2_orig_x) * (p1_orig_x - p2_orig_x)) + ((p1_orig_y - p2_orig_y) * (p1_orig_y - p2_orig_y));
		float d1 = points[index_of_point_1].get_distance_to(&(points[index_of_point_2]));

		float p2_rotated_x = p1_orig_x + d1;
		float p2_rotated_y = p1_orig_y;

		float d2_squared = ((p2_orig_x - p2_rotated_x) * (p2_orig_x - p2_rotated_x)) + ((p2_orig_y- p2_rotated_y) * (p2_orig_y - p2_rotated_y));

		// using law of cosines:
		float cos_of_angle = ((2*d1_squared) - d2_squared)/(2*d1_squared);

		#ifdef DEBUG_PSA
			printf ("\t\tcosine of angle = %.2f\n",cos_of_angle);
		#endif

		result_angle =  acos(cos_of_angle) * 180.0 / GlobalParams::pi();
	}

	return result_angle;
}

float PointSetAlgorithms::find_rotation_with_minimum_bounding_box(vector<Point> &points, vector<int> &convex_hull)
{
	#ifdef DEBUG_PSA
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    if(convex_hull.size() == 0){
        return 0.0;
    }

    vector<float> considered_angles = vector<float>(0);

	float optimal_angle = 0;
	float minimum_area_of_bounding_box = -1;

	for (int configuration = 0; configuration < convex_hull.size()-1; ++configuration)
	{
		#ifdef DEBUG_PSA
			printf("Consider configuration %i\n", configuration);
		#endif

		float current_angle = compute_rotation_angle_for_points_parallel_to_axis(points, convex_hull[configuration], convex_hull[(configuration+1) % (convex_hull.size()-1)]);

		bool angle_already_computed = false;
		for (int angle_index = 0; angle_index < considered_angles.size() && !angle_already_computed; ++angle_index)
		{
			if (fabs(considered_angles[angle_index] - current_angle) < GlobalParams::get_tolerance())
				angle_already_computed = true;
		}

		if (angle_already_computed)
		{
			#ifdef DEBUG_PSA
				printf("This angle (%.2f) was already computed. Skipping...\n", current_angle);
			#endif
		}
		else
		{
			float x_min = 0;
			float x_max = 0;
			float y_min = 0;
			float y_max = 0;
			for (int index_of_hullpoint = 0; index_of_hullpoint < convex_hull.size(); ++index_of_hullpoint)
			{
				float this_x = points[convex_hull[index_of_hullpoint]].compute_pos_after_rotation_x(current_angle);
				float this_y = points[convex_hull[index_of_hullpoint]].compute_pos_after_rotation_y(current_angle);

				if (index_of_hullpoint == 0)
				{
					x_min = this_x;
					x_max = this_x;
					y_min = this_y;
					y_max = this_y;
				}
				else
				{
					if (x_min > this_x)
						x_min = this_x;
					else if (x_max < this_x)
						x_max = this_x;
					if (y_min > this_y)
						y_min = this_y;
					else if (y_max < this_y)
						y_max = this_y;
				}
			}
			float current_area = (x_max-x_min) * (y_max-y_min);
			if (configuration == 0 || current_area < minimum_area_of_bounding_box)
			{
				minimum_area_of_bounding_box = current_area;
				optimal_angle = current_angle;
			}

			#ifdef DEBUG_PSA
				printf("\tCurrente angle: %.2f\n\tArea of bounding box in current configuration: %.2f\n\t optimal configuration so far hast area: %.2f\n", current_angle, current_area, minimum_area_of_bounding_box);
			#endif
		}
	}

	return optimal_angle;
}
