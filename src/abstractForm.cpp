#include "abstractForm.hpp"

#ifdef DEBUG
	#define DEBUG_AF
#endif

int AbstractForm::total_number_of_abstract_forms = 0;

AbstractForm::AbstractForm(string name, vector<Point> points)
{
	#ifdef DEBUG_AF
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	this->name = name;
	this->points = vector<Point>(points);
	this->id = total_number_of_abstract_forms++;

	fits_with_optimal_rotation = false;

	number_of_points = points.size();

    calc_bounding_box();

	#ifdef DEBUG_AF
		printf("Created abstractForm with bounding box %.2f/%.2f - %.2f/%.2f\n", min_x, min_y, min_x + dx, min_y + dy);
	#endif

	convex_hull = vector<int>();

    update_values();
}

void AbstractForm::compute_size_of_area()
{
    // Calculate the size of the area (according to http://www.mathopenref.com/coordpolygonarea.html )

	#ifdef DEBUG_AF
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

float AbstractForm::find_rotation_with_minimum_bounding_box()
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float degree = PointSetAlgorithms::find_rotation_with_minimum_bounding_box(points, convex_hull);

	return degree;
}

bool AbstractForm::find_rotation_with_minimum_bounding_box_and_check_if_legal(float plane_width, float plane_height, float &degree)
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	degree = PointSetAlgorithms::find_rotation_with_minimum_bounding_box(points, convex_hull);

	float x_min, x_max, y_min, y_max;

	//vector<Point> points_tmp = vector<Point>(points.begin(), points.end());

	PointSetAlgorithms::rotate_pointset_at_point(points, 0, 0, degree, x_min, x_max, y_min,y_max);

	dx = x_max-x_min;
	dy = y_max-y_min;

	#ifdef DEBUG_AF
		printf("dim of plane: %.2f/%.2f\ndim of form: %.2f/%.2f\n", plane_width, plane_height, dx, dy);
	#endif

	if ((plane_width  - dx > GlobalParams::get_tolerance() && 
		 plane_height - dy > GlobalParams::get_tolerance()))/* || 
		(plane_height - dx > GlobalParams::get_tolerance() && 
		 plane_width  - dy > GlobalParams::get_tolerance()))*/
	{
		#ifdef DEBUG_AF
			printf("Optimal rotation is legal\n");
		#endif

		fits_with_optimal_rotation = true;
		return true;
	}
	else
	{
		#ifdef DEBUG_AF
			printf("Optimal rotation is NOT legal\n");
		#endif

		fits_with_optimal_rotation = false;
		return false;
	}
}

int AbstractForm::check_for_optimal_legal_rotation(float plane_width, float plane_height)
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int optimal_angle = -1;
	float optimal_area_of_bounding_box = -1;
	for (int angle = 0; angle < 90; ++angle)
	{
		#ifdef DEBUG_AF
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
			#ifdef DEBUG_AF
				printf("\tRotating by %i degrees is a legal rotation\n", angle);
			#endif

			if (optimal_angle < 0 || area_of_bounding_box < optimal_area_of_bounding_box)
			{
				#ifdef DEBUG_AF
					printf("\t\tFound new optimal legal configuration with area %.2f\n", area_of_bounding_box);
				#endif

				optimal_area_of_bounding_box = area_of_bounding_box;
				optimal_angle = angle;
			}
		}
		if (current_dy < (plane_width+GlobalParams::get_tolerance()) && current_dx < (plane_height+GlobalParams::get_tolerance()))
		{
			#ifdef DEBUG_AF
				printf("\tRotating by %i degrees is a legal rotation\n", angle+90);
			#endif

			if (optimal_angle < 0 || area_of_bounding_box < optimal_area_of_bounding_box)
			{
				#ifdef DEBUG_AF
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
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("rotate form by %.2f degrees\n", degrees);
	#endif

	PointSetAlgorithms::rotate_pointset_at_point(points, 0, 0, degrees, min_x, max_x, min_y, max_y);
	dx = max_x - min_x;
	dy = max_y - min_y;

	#ifdef DEBUG_AF
		printf("\tRotated form into position x_min = %.2f, dx = %.2f - y_min = %.2f, dy = %.2f\n", min_x, dx, min_y, dy);
	#endif
}

void AbstractForm::mirror()
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	PointSetAlgorithms::mirror_pointset_at_axis(points, min_y, max_y);
}

void AbstractForm::normalize_position(float plane_width, float plane_height)
{
	#ifdef DEBUG_AF
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
		
		#ifdef DEBUG_AF
			printf("\tPoint %i moved to normalized position %.2f/%.2f\n", i, points[i].get_x(), points[i].get_y());
		#endif
	}

	max_x -= min_x;
	max_y -= min_y;
	min_x = 0;
	min_y = 0;

	if (flip)
	{
		#ifdef DEBUG_AF
			printf("\tForm got flipped\n");
		#endif

		float tmp_max_x = max_x;
		max_x = max_y;
		max_y = tmp_max_x;

		dx = max_x;
		dy = max_y;

	}
}

void AbstractForm::compute_convex_hull()
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	PointSetAlgorithms::compute_convex_hull(points, convex_hull);
}

int AbstractForm::get_number_of_points()
{
	#ifdef DEBUG_AF
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
		printf("Number of points: %i\n", points.size());
	#endif

	return points.size();
}

float AbstractForm::get_dx()
{
	#ifdef DEBUG_AF
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	return dx;
}

float AbstractForm::get_dy()
{
	#ifdef DEBUG_AF
		printf("GETTER: %s\n", __PRETTY_FUNCTION__);
	#endif

	return dy;
}

void AbstractForm::_d_print_abstract_form()
{
	#ifdef DEBUG_AF
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	#ifdef DEBUG_AF
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
         first_index < points.size();
         first_index++)
    {
        for (unsigned int second_index = first_index + 1;
             second_index < points.size();
             second_index++)
        {
            Edge first_edge = Edge(&points[first_index], &points[(first_index + 1)%points.size()]);
            Edge second_edge = Edge(&points[second_index], &points[(second_index + 1)%points.size()]);
         
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
