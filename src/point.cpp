#include "point.hpp"

void Point::move_rel(float dx, float dy)
{
	x += dx;
	y += dy;
}

void Point::rotate(float center_x, float center_y, float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	angle *= PI/180;
	
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);

	float dx = x-center_x;
	float dy = y-center_y;

	x = cos_angle*dx - sin_angle*dy + center_x;
	y = sin_angle*dx - cos_angle*dy + center_y;
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