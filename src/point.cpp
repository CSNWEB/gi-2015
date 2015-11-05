#include "point.hpp"

void Point::rotate(float center_x, float center_y, float angle)
{
	angle *= PI/180;
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);

	float dx = x-center_x;
	float dy = y-center_y;

	x = cos_angle*dx - sin_angle*dy + center_x;
	y = sin_angle*dx - cos_angle*dy + center_y;
}