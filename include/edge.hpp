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
#include <iostream>

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
     *  Finds the point where the receiver and other intersect each other.
     *
     *  Taken from: http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
     *
     *  @param other The edge that may cross this edge.
     *
     *  @return The Point where the receiver and other intersect. NULL if they don't.
     */
    Point* intersection_with_edge(Edge *other);
    
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
