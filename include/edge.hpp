#ifndef EDGE_H
#define EDGE_H

#include <algorithm>

#include "point.hpp"

class Edge
{
private:
	Point *p1, *p2;
	
public:
	Edge(){};

	Edge(Point *p1, Point *p2);
	
	void move_rel(float dx, float dy);
	void rotate(float center_x, float center_y, float degree);

	bool check_if_crosses(Edge *other);
	
	float length(){return p1->get_distance_to(p2);};
	float get_edge_x(){return p2->get_x()-p1->get_x();};
	float get_edge_y(){return p2->get_y()-p1->get_y();};
};

#endif
