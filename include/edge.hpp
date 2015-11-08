/**
 *  Class Edge
 *
 *  An Edge consists of two points. It has a length and one can get the distance
 *  it has on the x- and y-axis.
 *  It can be moved and rotated and one can check whether an edge crosses
 *  another edge.
 */
#ifndef EDGE_H
#define EDGE_H

#include <algorithm>

#include "point.hpp"

class Edge
{
private:
    
    /**
     *  The points that define the edge.
     */
	Point *p1, *p2;
	
public:
    
    /**
     *  Default constructor
     */
	Edge(){};

    /**
     *  Constructor to initialize an edge with its two points.
     */
	Edge(Point *p1, Point *p2);
	
    /**
     *  Move the edge relative to its current position by the amounts given in
     *  x- and y-direction.
     *
     *  @param dx A float defining how much the edge is moved on the x-axis.
     *  @param dy A float defining how much the edge is moved on the y-axis.
     */
	void move_rel(float dx, float dy);
    
    /**
     *  Rotates the edge around the passed center by the given degree.
     *
     *  @param center_x A float defining the position of the center on the x-axis.
     *  @param center_y A float defining the position of the center on the y-axis.
     *  @param degree   A float describing the amount by which the edge is rotated.
     */
	void rotate(float center_x, float center_y, float degree); // TODO: Maybe use Point for center?

    /**
     *  Check whether the receiver crosses the passed edge.
     *
     *  @param other The Edge that the cross-check is done against.
     *
     *  @return true if the receiver and other cross, false if not.
     */
	bool check_if_crosses(Edge *other);
	
    /**
     *  The length of the edge
     *
     *  @return A float resembling the length of the edge.
     */
	float length(){return p1->get_distance_to(p2);};
    
    /**
     *  The distance the edge covers on the x- and y-axis respectively.
     *
     *  @return A float representing the distance the edge covers on the x- and y-axis respectively.
     */
	float get_edge_x(){return p2->get_x()-p1->get_x();};
	float get_edge_y(){return p2->get_y()-p1->get_y();};
};

#endif
