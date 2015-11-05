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
	
	float get_distance_to(Point other){return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));};
	
	void move_rel(float dx, float dy){x += dx; y += dy;};
	void rotate(float center_x, float center_y, float angle);
};

#endif
