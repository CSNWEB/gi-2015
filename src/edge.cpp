#include "edge.hpp"

Edge::Edge(Point &p1, Point &p2) : point_1(p1), point_2(p2)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
}

/**
 *  Finds the point where the receiver and other intersect each other.
 *
 *  Taken from: http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
 *
 *  @param other The edge that may cross this edge.
 *
 *  @return The Point where the receiver and other intersect. NULL if they don't.
 */
bool Edge::intersection_with_edge(Edge &other, Point& intersection_point)
{
    #ifdef DEBUG
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif
    
    Point p3 = other.point_1;
    Point p4 = other.point_2;
    
    
    // Store the values for fast access and easy
    // equations-to-code conversion
    
    float x1 = point_1.get_x();
    float x2 = point_2.get_x();
    float x3 = p3.get_x();
    float x4 = p4.get_x();
    float y1 = point_1.get_y();
    float y2 = point_2.get_y();
    float y3 = p3.get_y();
    float y4 = p4.get_y();
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0)
    {
        return false;
    }
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    // Check if the x and y coordinates are within both lines
    if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
        x < std::min(x3, x4) || x > std::max(x3, x4) )
    {
        return false;
    }
    
    if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
        y < std::min(y3, y4) || y > std::max(y3, y4) )
    {
        return false;
    }
    
    // Return the point of intersection
    intersection_point = Point(x,y);
    return true;
}

bool Edge::crosses(Edge &other)
{
    Point intersection;
    bool does_intersect = intersection_with_edge(other, intersection);
    
    if (!does_intersect)
    {
        return false;
    }
    else
    {
        /**
         *  Check if none of the points of the edges is equal to the interection.
         */
        float x = intersection.get_x();
        float y = intersection.get_y();
        
        if ((fabs(point_1.get_x() - x) < GlobalParams::get_tolerance() && 
                fabs(point_1.get_y() - y) < GlobalParams::get_tolerance()) ||
            (fabs(point_2.get_x() - x) < GlobalParams::get_tolerance() &&
                fabs(point_2.get_y() - y) < GlobalParams::get_tolerance()) ||
            (fabs(other.point_1.get_x() - x) < GlobalParams::get_tolerance() &&
                fabs(other.point_1.get_y() - y) < GlobalParams::get_tolerance()) ||
            (fabs(other.point_2.get_x() - x) < GlobalParams::get_tolerance() && 
                fabs(other.point_2.get_y() - y) < GlobalParams::get_tolerance()))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void Edge::_d_print_edge_to_console()
{
	#ifdef DEBUG
		printf("Edge from point %.2f/%.2f to point %.2f/%.2f with length %.2f\n", point_1.get_x(), point_1.get_y(), point_2.get_x(), point_2.get_y(), length());
	#endif
}