#include "abstractForm.hpp"

int AbstractForm::total_number_of_abstract_forms = 0;

AbstractForm::AbstractForm(string name, vector<Point> points)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	this->name = name;
	this->points = vector<Point>(points);
	this->id = total_number_of_abstract_forms++;

	number_of_points = points.size();

    calc_bounding_box();

	#ifdef DEBUG
		printf("Created abstractForm with bounding box %.2f/%.2f - %.2f/%.2f\n", min_x, min_y, min_x + dx, min_y + dy);
	#endif

	convex_hull = vector<int>();

    update_values();
}

void AbstractForm::compute_size_of_area()
{
    // Calculate the size of the area (according to http://www.mathopenref.com/coordpolygonarea.html )

	#ifdef DEBUG
		printf("FUNCITON: %s\n", __PRETTY_FUNCTION__);
	#endif

    size_of_area = 0.0;

    if(points.size() == 0){
        return;
    }
    
    vector<Point> closed_points = points;
    closed_points.push_back(closed_points[0]);
    
    for (unsigned int index = 0; index < closed_points.size() - 1; index++)
    {
        size_of_area += ((closed_points[index].get_x() * closed_points[index + 1].get_y()) - (closed_points[index].get_y() * closed_points[index + 1].get_x()));
    }
    
    size_of_area /= 2.0;
    
    size_of_area = fabs(size_of_area);
}

/*
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


	return acos(cos_of_angle) * 180.0 / GlobalParams::pi();
}
*/


float AbstractForm::find_rotation_with_minimum_bounding_box()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return PointSetAlgorithms::find_rotation_with_minimum_bounding_box(&points, &convex_hull);
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
			float rotated_x = (points[convex_hull[point_index]].get_x() * cos(angle * GlobalParams::pi()/180)) - (points[convex_hull[point_index]].get_y() * sin(angle * GlobalParams::pi()/180));
			float rotated_y = (points[convex_hull[point_index]].get_x() * sin(angle * GlobalParams::pi()/180)) + (points[convex_hull[point_index]].get_y() * cos(angle * GlobalParams::pi()/180));
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

		if (current_dx < (plane_width+GlobalParams::get_tolerance()) && current_dy < (plane_height+GlobalParams::get_tolerance()))
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
		if (current_dy < (plane_width+GlobalParams::get_tolerance()) && current_dx < (plane_height+GlobalParams::get_tolerance()))
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

		PointSetAlgorithms::rotate_pointset_at_point(points, 0, 0, degrees, min_x, max_x, min_y, max_y);
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

	PointSetAlgorithms::mirror_pointset_at_axis(points, min_x, max_x);
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

	/*
	vector<int> ordered_indices = sort_points_dim_x();
    if(points.size() == 0){
        convex_hull.clear();
    }
    else if (points.size() == 3)
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
	*/

	PointSetAlgorithms::compute_convex_hull(points, convex_hull);
}

int AbstractForm::get_number_of_points()
{
	#ifdef DEBUG
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
		printf("Number of points: %i\n", points.size());
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

void AbstractForm::calc_bounding_box()
{
    if(points.size() == 0){
       min_x = max_x = min_y = max_y = 0;

    }else{
        min_x = points[0].get_x();
        max_x = points[0].get_x();
        min_y = points[0].get_y();
        max_y = points[0].get_y();
        for (int i=1; i<number_of_points; ++i)
        {
            if (points[i].get_x() < min_x)
                min_x = points[i].get_x();
            else if (points[i].get_x() > max_x)
                max_x = points[i].get_x();

            if (points[i].get_y() < min_y)
                min_y = points[i].get_y();
            else if (points[i].get_y() > max_y)
                max_y = points[i].get_y();
        }
    }


    dx = max_x-min_x;
    dy = max_y-min_y;
}

void AbstractForm::update_bounding_box(float x, float y)
{
    if(x > max_x){
        max_x = x;
    }
    if(x < min_x){
        min_x = x;
    }
    if(y > max_y){
        max_y = y;
    }
    if(y < min_y){
        y = min_y;
    }
    dx = max_x-min_x;
    dy = max_y-min_y;
}

void AbstractForm::update_values(){
    compute_convex_hull();
    compute_size_of_area();
    number_of_points = points.size();
}

void AbstractForm::add_point_to_form(float x, float y)
{
    Point new_point(x,y);
    points.push_back(new_point);
    update_bounding_box(x,y);
    update_values();
}

void AbstractForm::set_xy_of_point(int point, float x, float y)
{
    points[point].set_x(x);
    points[point].set_y(y);
    update_bounding_box(x,y);
    update_values();
}

void AbstractForm::erase_point_at_index(int index)
{

    points.erase(points.begin()+index);

    calc_bounding_box();

    update_values();

}


void AbstractForm::move_up_point_at_index(int index)
{
    if(index <= 0){
        return;
    }
    if(index >= points.size()){
        return;
    }
    Point h = points[index-1];
    points[index-1] = points[index];
    points[index] = h;
}

void AbstractForm::move_down_point_at_index(int index)
{
    if(index < 0){
        return;
    }
    if(index >= points.size()-1){
        return;
    }
    Point h = points[index+1];
    points[index+1] = points[index];
    points[index] = h;
}

bool AbstractForm::overlaps_itself()
{
    std::cout << "Points size = " << points.size() << std::endl;
    
    // Looping over all edges
    for (unsigned int first_index = 0;
         first_index < points.size() - 1;
         first_index++)
    {
        for (unsigned int second_index = first_index + 1;
             second_index < points.size() - 1;
             second_index++)
        {
            Edge first_edge = Edge(&points[first_index], &points[first_index + 1]);
            Edge second_edge = Edge(&points[second_index], &points[second_index + 1]);
         
            // Checking whether the edges cross
            if (first_edge.crosses(&second_edge))
            {
                return true;
            }
        }
        
        // Checking with the closing edge.
        Edge first_edge = Edge(&points[first_index], &points[first_index + 1]);
        Edge second_edge = Edge(&points[points.size() - 1], &points[0]);
    }
    
    return false;
}