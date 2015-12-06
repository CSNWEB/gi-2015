#include "point.hpp"

void Point::move_rel(float dx, float dy)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	x += dx;
	y += dy;
}

void Point::rotate(float center_x, float center_y, float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
	
    float s = sin(angle * PI/180);
    float c = cos(angle * PI/180);
    
    // translate point back to origin:
    x -= center_x;
    y -= center_y;
    
    // rotate point
    float xnew = (x * c) - (y * s);
    float ynew = (x * s) + (y * c);
    
    // translate point back:
    x = xnew + center_x;
    y = ynew + center_y;
}

void Point::rotate(float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float x_new = compute_pos_after_rotation_x(angle);
	float y_new = compute_pos_after_rotation_y(angle);

	x = x_new;
	y = y_new;
}

float Point::compute_pos_after_rotation_x(float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return (x * cos(angle * PI/180.0)) - (y * sin(angle * PI/180.0));
}

float Point::compute_pos_after_rotation_y(float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return (x * sin(angle * PI/180.0)) + (y * cos(angle * PI/180.0));
}


float Point::get_distance_to(Point *other)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	return sqrt((x-other->x)*(x-other->x)+(y-other->y)*(y-other->y));
}

void Point::flip()
{
	float tmp = x;
	x = y;
	y = tmp;
}

int Point::is_left_of(Point *p_start, Point *p_end)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	/**
	 *  compute determinant of 
	 * 		1 	p_start.x 	p_start.y
	 *		1 	p_end.x 	p_end.y
	 * 		1 	x 			y
	 */
	float det = (x - p_start->get_x()) * (y - p_end->get_y()) - (y - p_start->get_y()) * (x - p_end->get_x());

	// To do: use lower bound to absolut value instead of zero

	if (det > 0)
		return -1;

	if (det < 0)
		return 1;

	return 0;
}