#ifndef EDGE_H
#define EDGE_H

#include <math.h>

#include "point.hpp"
#include "form.hpp"

class Edge
{
private:
	Point p1, p2;
	//Form *form;
public:
	Edge();
	
	void move_rel(float dx, float dy);
	void rotate(float center_x, float center_y, float degree);

	bool check_if_crosses(Edge *other);
	
	float length(){return p1.get_distance_to(p2);};
	float get_edge_x(){return p2.get_x()-p1.get_x();};
	float get_edge_y(){return p2.get_y()-p1.get_y();};
};

#endif
