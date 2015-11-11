#ifndef POINT_H
#define POINT_H

#include <math.h>

#define PI 3.1415926535

class Point
{
private:
	float x;
	float y;
	
public:
	Point(){x=0; y=0;};
	Point(float x, float y){this->x = x; this->y = y;};

	float get_x() {return x;};
	float get_y() {return y;};
	
	float get_distance_to(Point *other){return sqrt((x-other->x)*(x-other->x)+(y-other->y)*(y-other->y));};

	/**
	 *  Function to check if this point is left of line defined by p_start -> p_end
	 *
	 * @param p_start 	Pointer to point defining start of line
	 * @param p_end 	Point to point defining direction of line
	 *
	 * @retun 			 0 if this point is on line
	 *					 1 if this point is left of line
	 * 					-1 if this point is on the right of line
	 */
	int is_left_of(Point *p_start, Point *p_end);
	
	void move_rel(float dx, float dy){x += dx; y += dy;};
	void rotate(float center_x, float center_y, float angle);
};

#endif
