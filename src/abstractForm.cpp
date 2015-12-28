#include "abstractForm.hpp"

AbstractForm::AbstractForm(string name, vector<Point> points, int id)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	this->name = name;
	this->points = points;
	this->id = id;

	number_of_points = points.size();

	min_x = points[0].get_x();
	float x_max = points[0].get_x();
	min_y = points[0].get_y();
	float y_max = points[0].get_y();
	for (int i=1; i<number_of_points; ++i)
	{
		if (points[i].get_x() < min_x)
			min_x = points[i].get_x();
		else if (points[i].get_x() > x_max)
			x_max = points[i].get_x();

		if (points[i].get_y() < min_y)
			min_y = points[i].get_y();
		else if (points[i].get_y() > y_max)
			y_max = points[i].get_y();
	}
	dx = x_max-min_x;
	dy = y_max-min_y;

	#ifdef DEBUG
		printf("Created abstractForm with bounding box %.2f/%.2f - %.2f/%.2f\n", min_x, min_y, min_x + dx, min_y + dy);
	#endif

	convex_hull = vector<int>();

	compute_convex_hull();
    
    compute_size_of_area();
}

vector<int> AbstractForm::sort_points_dim_x()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	vector<int> ordered_indices = vector<int>(points.size(),0);
	for (int i=0; i<points.size(); ++i)
		ordered_indices[i] = i;

	for (int i=0; i<points.size()-1; ++i)
	{
		for (int j=i; j<points.size(); ++j)
		{
			if (points[ordered_indices[i]].get_x() > points[ordered_indices[j]].get_x() ||
				(points[ordered_indices[i]].get_x() == points[ordered_indices[j]].get_x() &&
				 points[ordered_indices[i]].get_y() > points[ordered_indices[j]].get_y()) )
			{
				int tmp = ordered_indices[i];
				ordered_indices[i] = ordered_indices[j];
				ordered_indices[j] = tmp;
			}
		}
	}

	#ifdef DEBUG
		printf("finished sorting. result:\n");
		for (int i=0; i<ordered_indices.size(); ++i)
			printf("%i ",ordered_indices[i]);
		printf("\n");
	#endif

	return ordered_indices;
}

void AbstractForm::compute_size_of_area()
{
    // Calculate the size of the area (according to http://www.mathopenref.com/coordpolygonarea.html )

	#ifdef DEBUG
		printf("FUNCITON: %s\n", __PRETTY_FUNCTION__);
	#endif
    
    size_of_area = 0.0;
    
    vector<Point> closed_points = points;
    closed_points.push_back(closed_points[0]);
    
    for (unsigned int index = 0; index < closed_points.size() - 1; index++)
    {
        size_of_area += ((closed_points[index].get_x() * closed_points[index + 1].get_y()) - (closed_points[index].get_y() * closed_points[index + 1].get_x()));
    }
    
    size_of_area /= 2.0;
    
    size_of_area = fabs(size_of_area);
}

float AbstractForm::compute_rotation_angle_for_points_parallel_to_axis(int index_of_point_1, int index_of_point_2)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("\t\tPoint1 = %i\n\t\tPoint2 = %i\n", index_of_point_1, index_of_point_2);
	#endif

	float p1_orig_x = points[index_of_point_1].get_x();
	float p1_orig_y = points[index_of_point_1].get_y();

	float p2_orig_x = points[index_of_point_2].get_x();
	float p2_orig_y = points[index_of_point_2].get_y();

	float d1_squared = ((p1_orig_x - p2_orig_x) * (p1_orig_x - p2_orig_x)) + ((p1_orig_y - p2_orig_y) * (p1_orig_y - p2_orig_y));
	float d1 = points[index_of_point_1].get_distance_to(&points[index_of_point_2]);

	float p2_rotated_x = p1_orig_x + d1;
	float p2_rotated_y = p1_orig_y;

	float d2_squared = ((p2_orig_x - p2_rotated_x) * (p2_orig_x - p2_rotated_x)) + ((p2_orig_y- p2_rotated_y) * (p2_orig_y - p2_rotated_y));

	// using law of cosines:
	float cos_of_angle = ((2*d1_squared) - d2_squared)/(2*d1_squared);

	#ifdef DEBUG
		printf ("\t\tcosine of angle = %.2f\n",cos_of_angle);
	#endif


	return acos(cos_of_angle) * 180.0 / PI;
}

float AbstractForm::find_rotation_with_minimum_bounding_box()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float optimal_angle = 0;
	float minimum_area_of_bounding_box = -1;

	for (int configuration = 0; configuration < convex_hull.size()-1; ++configuration)
	{
		#ifdef DEBUG
			printf("Consider configuration %i\n", configuration);
		#endif

		float current_angle = compute_rotation_angle_for_points_parallel_to_axis(convex_hull[configuration], convex_hull[(configuration+1) % (convex_hull.size()-1)]);
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

		#ifdef DEBUG
			printf("\tCurrente angle: %.2f\n\tArea of bounding box in current configuration: %.2f\n\t optimal configuration so far hast area: %.2f\n", current_angle, current_area, minimum_area_of_bounding_box);
		#endif
	}

	return optimal_angle;
}

int AbstractForm::check_for_optimal_legal_rotation(float plane_width, float plane_height)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int optimal_angle = -1;
	float optimal_area_of_bounding_box = -1;
	for (int angle = 0; angle < 90; ++angle)
	{
		#ifdef DEBUG
			printf("\tCheck angle %i degrees\n", angle);
		#endif

		float x_min = 0;
		float x_max = 0;
		float y_min = 0;
		float y_max = 0;
		for (int point_index = 0; point_index < convex_hull.size(); ++point_index)
		{
			float rotated_x = (points[convex_hull[point_index]].get_x() * cos(angle * PI/180)) - (points[convex_hull[point_index]].get_y() * sin(angle * PI/180));
			float rotated_y = (points[convex_hull[point_index]].get_x() * sin(angle * PI/180)) + (points[convex_hull[point_index]].get_y() * cos(angle * PI/180));
			if (point_index == 0)
			{
				x_min = rotated_x;
				x_max = rotated_x;
				y_min = rotated_y;
				y_max = rotated_y;
			}
			else
			{
				if (x_min > rotated_x)
					x_min = rotated_x;
				else if (x_max < rotated_x)
					x_max = rotated_x;
				if (y_min > rotated_y)
					y_min = rotated_y;
				else if (y_max < rotated_y)
					y_max = rotated_y;
			}
		}

		float current_dx = x_max-x_min;
		float current_dy = y_max-y_min;

		float area_of_bounding_box = current_dx * current_dy;

		if (current_dx < (plane_width+TOLERANCE) && current_dy < (plane_height+TOLERANCE))
		{
			#ifdef DEBUG
				printf("\tRotating by %i degrees is a legal rotation\n", angle);
			#endif

			if (optimal_angle < 0 || area_of_bounding_box < optimal_area_of_bounding_box)
			{
				#ifdef DEBUG
					printf("\t\tFound new optimal legal configuration with area %.2f\n", area_of_bounding_box);
				#endif

				optimal_area_of_bounding_box = area_of_bounding_box;
				optimal_angle = angle;
			}
		}
		if (current_dy < (plane_width+TOLERANCE) && current_dx < (plane_height+TOLERANCE))
		{
			#ifdef DEBUG
				printf("\tRotating by %i degrees is a legal rotation\n", angle+90);
			#endif

			if (optimal_angle < 0 || area_of_bounding_box < optimal_area_of_bounding_box)
			{
				#ifdef DEBUG
					printf("\t\tFound new optimal legal configuration with area %.2f\n", area_of_bounding_box);
				#endif

				optimal_area_of_bounding_box = area_of_bounding_box;
				optimal_angle = angle+90;
			}
		}
	}
	return optimal_angle;
}

void AbstractForm::rotate_form_by_degrees(float degrees)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("rotate form by %.2f degrees\n", degrees);
	#endif

	min_x = 0;
	float max_x = 0;
	min_y = 0;
	float max_y = 0;
	for (int point_index = 0; point_index < points.size(); ++point_index)
	{
		points[point_index].rotate(degrees);

		#ifdef DEBUG
			printf("Rotated point %i to position (%.2f/%.2f)\n",point_index, points[point_index].get_x(), points[point_index].get_y());
		#endif

		float this_x = points[point_index].get_x();
		float this_y = points[point_index].get_y();

		if (point_index == 0)
		{
			min_x = this_x;
			max_x = this_x;
			min_y = this_y;
			max_y = this_y;
		}
		else
		{
			if (this_x < min_x)
				min_x = this_x;
			else if (this_x > max_x)
				max_x = this_x;
			if (this_y < min_y)
				min_y = this_y;
			else if (this_y > max_y)
				max_y = this_y;
		}
	}
	dx = max_x-min_x;
	dy = max_y-min_y;

	#ifdef DEBUG
		printf("\tRotated form into position x_min = %.2f, dx = %.2f - y_min = %.2f, dy = %.2f\n", min_x, dx, min_y, dy);
	#endif
}

void AbstractForm::mirror()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int p=0; p<get_number_of_points(); ++p)
	{
		points[p].move_rel(-2*points[p].get_x(), 0);
	}
}

void AbstractForm::normalize_position(float plane_width, float plane_height)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	bool flip = false;

	if (dx < dy && dy < plane_width)
		flip = true;

	for (int i=0; i<points.size(); ++i)
	{
		points[i].move_rel(-min_x, -min_y);

		if (flip)
			points[i].flip();
		
		#ifdef DEBUG
			printf("\tPoint %i moved to normalized position %.2f/%.2f\n", i, points[i].get_x(), points[i].get_y());
		#endif
	}

	min_x = 0;
	min_y = 0;

	if (flip)
	{
		#ifdef DEBUG
			printf("\tForm got flipped\n");
		#endif

		float tmp = dx;
		dx = dy;
		dy = tmp;
	}
}

void AbstractForm::compute_convex_hull()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	vector<int> ordered_indices = sort_points_dim_x();

	if (points.size() == 3)
	{
		convex_hull = ordered_indices;
		convex_hull.push_back(ordered_indices[0]);
		return;
	}
	else
	{
		vector<int> convex_hull_lower = vector<int>();
		convex_hull_lower.push_back(ordered_indices[0]);
		convex_hull_lower.insert(convex_hull_lower.end(), ordered_indices.begin(), ordered_indices.end());

		#ifdef DEBUG
			printf("Init lower_hull finished\n");
			for (int i=0; i<convex_hull_lower.size(); ++i)
				printf("point at position %i: %i\n",i, convex_hull_lower[i]);
		#endif

		int i=0;
		while (i < convex_hull_lower.size()-2)
		{
			#ifdef DEBUG
				printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_lower.size());
			#endif

			int ind_p1 = convex_hull_lower[i];
			int ind_p2 = convex_hull_lower[i+1];
			int ind_p3 = convex_hull_lower[i+2];

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
			{
				// p2 is not part of convex hull
				#ifdef DEBUG
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

		#ifdef DEBUG
			printf("lower hull complete\n");
			for (int k=0; k<convex_hull_lower.size(); ++k)
				printf("\tpoint %i is %i\n", k, convex_hull_lower[k]);
		#endif

		vector<int> convex_hull_upper = ordered_indices;
		convex_hull_upper.push_back(ordered_indices[ordered_indices.size()-1]);

		#ifdef DEBUG
			printf("Init upper_hull finished\n");
			for (int i=0; i<convex_hull_upper.size(); ++i)
				printf("point at position %i: %i\n",i, convex_hull_upper[i]);
		#endif

		i = convex_hull_upper.size()-1;
		while (i >= 2)
		{
			#ifdef DEBUG
				printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_upper.size());
			#endif
			int ind_p1 = convex_hull_upper[i];
			int ind_p2 = convex_hull_upper[i-1];
			int ind_p3 = convex_hull_upper[i-2];

			#ifdef DEBUG
				printf("now check if %i is left of %i->%i\n", ind_p2, ind_p1, ind_p3);
			#endif

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
			{
				// p2 is not part of convex hull
				#ifdef DEBUG
					printf("\terase point %i from hull\n", i-1);
					printf("\tthis is: %i\n", *(convex_hull_upper.begin()+i-1));
				#endif

				convex_hull_upper.erase(convex_hull_upper.begin()+i-1);
				++i;
			}
			else
				--i;
		}

		#ifdef DEBUG
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
	}

	#ifdef DEBUG
		printf("convex hull finished\n");
		for (int i=0; i<convex_hull.size(); ++i)
			printf("\t%i\n", convex_hull[i]);
	#endif
}


int AbstractForm::get_number_of_points()
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	return points.size();
}

float AbstractForm::get_dx()
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	return dx;
}

float AbstractForm::get_dy()
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	return dy;
}

void AbstractForm::_d_print_abstract_form()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		printf("Name of form: %s\n", name.c_str());
		printf("Number of points: %i\n", number_of_points);

		for (int i=0; i<number_of_points; ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());

	#endif
}
